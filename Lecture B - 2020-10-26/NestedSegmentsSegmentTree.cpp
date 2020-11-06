#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <functional>
#include <cmath>

#define LEFT(i)  (2 * (i) + 1)
#define RIGHT(i) (2 * (i) + 2)

struct range {
    size_t a, b;
    range(size_t a, size_t b) : a(a), b(b) {}
};

template<typename T, typename F=std::plus<T>> class segment_tree {
    std::vector<T> tree;
    void initialize(std::function<T(size_t)> f, range r, size_t i) {
        if(r.a > r.b)
            ;
        else if(r.a == r.b)
            tree[i] = f(r.a);
        else {
            size_t mid = (r.a + r.b) / 2;
            initialize(f, {r.a,     mid}, LEFT(i));
            initialize(f, {mid + 1, r.b}, RIGHT(i));
            tree[i] = F()(tree[LEFT(i)], tree[RIGHT(i)]);
        }
    }
    T get(range const& query, range r, size_t i) {
        if(query.a <= r.a && r.b <= query.b)
            return tree[i];
        else {
            size_t mid  = (r.a + r.b) / 2;
            range left  = {r.a, mid};
            range right = {mid + 1, r.b};
            if(query.a > right.b || query.b < right.a)
                return get(query, left, LEFT(i));
            else if(query.a > left.b || query.b < left.a)
                return get(query, right, RIGHT(i));
            else
                return F()(get(query, left,  LEFT(i)),
                           get(query, right, RIGHT(i)));
        }
    }
    void update(size_t target, std::function<T(T)> u, range r, size_t i) {
        if(target < r.a || r.b < target)
            ;
        else if(r.a == r.b)
            tree[i] = u(tree[i]);
        else {
            size_t mid = (r.a + r.b) / 2;
            update(target, u, {r.a,     mid}, LEFT(i));
            update(target, u, {mid + 1, r.b}, RIGHT(i));
            tree[i] = F()(tree[LEFT(i)], tree[RIGHT(i)]);
        }
    }
public:
    segment_tree(size_t n, std::function<T(size_t)> f) {
        size_t np = 1 << static_cast<size_t>(ceil(log2(n)));
        tree.resize(np-1 + np);
        initialize(f, {0, np-1}, 0);
    }
    segment_tree(size_t n)         : segment_tree(n,        [&](size_t i) { return 0;    }) {}
    segment_tree(std::vector<T> A) : segment_tree(A.size(), [&](size_t i) { return A[i]; }) {}
    size_t size() const {
        return tree.size()/2 + 1;
    }
    range root() const {
        return {0, size()-1};
    }
    T get(range const& query) {
        return get(query, root(), 0);
    }
    void update(size_t i, std::function<T(T)> u) {
        update(i, u, root(), 0);
    }
};

using namespace std;

// https://codeforces.com/problemset/problem/652/D?locale=en

/*
    nested_segments_segment_tree (time complexity: O(n log n), space complexity: O(n))
        First remap all segment indices inside the interval [1, 2N).
        Use a Segment tree to keep track of all the right ends, and set all of them to 1.
        Scan all the left segment starts according to a sweeping line algorithm: the number
        of intersecting segments is the number of right ends smaller than this segment's right end
        that are currently set to 1, i.e.: their sum. After processing this segment, set
        its right end to 0 in the Segment tree. All the segments that start before the
        current one will have been processed, so their right end will be set to zero
        and they won't be considered.
*/

vector<tuple<int64_t, int64_t>> remap(vector<tuple<int64_t, int64_t>> A) {
    vector<int64_t> points(2*A.size());

    transform(A.begin(), A.end(), points.begin(),            [](auto v) { return get<0>(v); });
    transform(A.begin(), A.end(), points.begin() + A.size(), [](auto v) { return get<1>(v); });

    sort(points.begin(), points.end());

    vector<tuple<int64_t, int64_t>> remapped;
    remapped.reserve(A.size());

    for(auto& p : A)
        remapped.emplace_back(lower_bound(points.begin(), points.end(), get<0>(p)) - points.begin(),
                              lower_bound(points.begin(), points.end(), get<1>(p)) - points.begin());

    return remapped;
}

vector<size_t> nested_segments_segment_tree(vector<tuple<int64_t, int64_t>> segments) {
    segment_tree<int64_t> ft(2*segments.size());

    segments = remap(segments);

    vector<tuple<int64_t, int64_t, size_t>> indexed_segments(segments.size());
    for(size_t i = 0; i < segments.size(); i++)
        indexed_segments[i] = make_tuple(get<0>(segments[i]), get<1>(segments[i]), i);

    sort(indexed_segments.begin(), indexed_segments.end());

    for(auto const& s : indexed_segments)
        ft.update(get<1>(s), [](auto a) { return a + 1; });

    vector<size_t> result(segments.size());

    for(auto const& s : indexed_segments) {
        ft.update(get<1>(s), [](auto a) { return a - 1; });
        result[get<2>(s)] = ft.get({0, static_cast<size_t>(get<1>(s))});
    }

    return result;
}

template<typename L, typename R> vector<tuple<L, R>> read_sequence2(size_t n) {
    vector<tuple<L, R>> input;
    input.reserve(n);
    for(size_t i = 0; i < n; i++) {
        R a; L b;
        cin >> a >> b;
        input.emplace_back(a, b);
    }
    return input;
}

int main() {
    size_t N;
    cin >> N;

    auto result = nested_segments_segment_tree(read_sequence2<int64_t, int64_t>(N));

    for(auto const& r : result)
        cout << r << endl;
}
