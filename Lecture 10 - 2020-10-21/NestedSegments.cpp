#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

template<typename T> class fenwick_tree {
    std::vector<T> tree;
public:
    fenwick_tree(size_t n) : tree(n+1) {}

    T sum(int64_t i) {
        T sum = 0;
        for(i++; i > 0; i -= i & -i)
            sum += tree[i];
        return sum;
    }

    void add(int64_t i, T v) {
        for(i++; i < tree.size(); i += i & -i)
            tree[i] += v;
    }
};

using namespace std;

// https://codeforces.com/problemset/problem/652/D?locale=en

/*
    nested_segments (time complexity: O(n log n), space complexity: O(n))
        First remap all segment indices inside the interval [1, 2N).
        Use a Fenwick tree to keep track of all the right ends, and set all of them to 1.
        Scan all the left segment starts according to a sweeping line algorithm: the number
        of intersecting segments is the number of right ends smaller than this segment's right end
        that are currently set to 1, i.e.: their sum. After processing this segment, set
        its right end to 0 in the Fenwick tree. All the segments that start before the
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

vector<size_t> nested_segments(vector<tuple<int64_t, int64_t>> segments) {
    fenwick_tree<int64_t> ft(2*segments.size());

    segments = remap(segments);

    vector<tuple<int64_t, int64_t, size_t>> indexed_segments(segments.size());
    for(size_t i = 0; i < segments.size(); i++)
        indexed_segments[i] = make_tuple(get<0>(segments[i]), get<1>(segments[i]), i);

    sort(indexed_segments.begin(), indexed_segments.end());

    for(auto const& s : indexed_segments)
        ft.add(get<1>(s), 1);

    vector<size_t> result(segments.size());

    for(auto const& s : indexed_segments) {
        ft.add(get<1>(s), -1);
        result[get<2>(s)] = ft.sum(get<1>(s));
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

    auto result = nested_segments(read_sequence2<int64_t, int64_t>(N));

    for(auto const& r : result)
        cout << r << endl;
}
