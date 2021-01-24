#include <bits/stdc++.h>

#define LEFT(i)   (2 * (i) + 1)
#define RIGHT(i)  (2 * (i) + 2)

using namespace std;

/*
    array_copy (Access complexity: O(log n),
                Copy   complexity: O(log n),
                space complexity: O(n))
*/

struct query {
    size_t x, y, k;
};

struct range {
    size_t a, b;
    range(size_t a, size_t b) : a(a), b(b) {}
};

struct segment_tree {
    vector<int64_t> tree;
    size_t size_;

    segment_tree(size_t n) : size_(n) {
        size_t m = size_t(1) << static_cast<size_t>(ceil(log2(n)));
        tree.resize(m-1 + m, 0);
        initialize({0, n-1}, 0);
    }
    size_t size() const {
        return size_;
    }
    range root() const {
        return range(0, size());
    }
    void initialize(range r, size_t pos) {
        if(r.a < r.b) {
            size_t mid = (r.a + r.b) / 2;
            initialize({r.a,     mid}, LEFT(pos));
            initialize({mid + 1, r.b}, RIGHT(pos));
        }
    }
    int64_t get(size_t i) {
        return get(i, range(0, size()-1), 0);
    }
    int64_t get(size_t target, range r, size_t i) {
        if(r.a == r.b)
            return tree[i];
        else {
            size_t mid  = (r.a + r.b) / 2;
            range left  = {r.a, mid};
            range right = {mid + 1, r.b};

            size_t m = tree[i];

            if(target > mid)
                return max(tree[i], get(target, right, RIGHT(i)));
            else
                return max(tree[i], get(target, left, LEFT(i)));
        }
    }
    void update_range(range target, size_t delta) {
        update_range(target, delta, root(), 0);
    }
    void update_range(range target, size_t delta, range r, size_t i) {
        if(r.a > target.b || r.b < target.a)
            ;
        else if(target.a <= r.a && r.b <= target.b)
            tree[i] = delta;
        else if(r.a != r.b) {
            size_t mid = (r.a + r.b) / 2;
            update_range(target, delta, {r.a,     mid}, LEFT(i));
            update_range(target, delta, {mid + 1, r.b}, RIGHT(i));
        }
    }
};

istream& operator>>(istream& is, tuple<> &t) {
    return is;
}

template<typename T, typename... Ts> istream& operator>>(istream& is, tuple<T, Ts...>& t) {
    T t0; tuple<Ts...> ts;
    is >> t0 >> ts;
    t = tuple_cat(tuple<T>(t0), ts);
    return is;
}

template<typename T> istream& operator>>(istream& is, vector<T>& v) {
    for(size_t i = 0; i < v.size(); i++)
        is >> v[i];
    return is;
}

template<typename T> ostream& operator<<(ostream& os, vector<T> v) {
    for(auto const& e : v)
        os << e << " ";
    os << endl;
    return os;
}

int main() {
    size_t N, M;
    cin >> N >> M;

    vector<int64_t> A(N);
    vector<int64_t> B(N);

    cin >> A >> B;

    segment_tree st(N);

    vector<query> Q;
    Q.reserve(M);

    for(int64_t i = 0; i < M; i++) {
        size_t type;
        cin >> type;

        if(type == 1) {
            size_t x, y, k;
            cin >> x >> y >> k;
            query q = {.x = x, .y = y, .k = k};
            Q.push_back(q);
            st.update_range({q.y, q.y + q.k}, Q.size());
        } else {
            size_t i;
            cin >> i;
            size_t id = st.get(i);
            if(id == 0) {
                cout << B[i] << endl;
            } else {
                auto q = Q[id - 1];
                cout << A[i - q.y + q.x] << endl;
            }
        }
    }
}
