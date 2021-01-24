#include <bits/stdc++.h>

using namespace std;

// min_and_max (time complexity: O(q log n), space complexity: O(n))

#define LEFT(i)  (2 * (i) + 1)
#define RIGHT(i) (2 * (i) + 2)

struct range {
    size_t a, b;
    range(size_t a, size_t b) : a(a), b(b) {}
};

class segment_tree {
    std::vector<int64_t> tree;
    std::vector<int64_t> lazy;
    std::function<int64_t(int64_t, int64_t)> binary;
    size_t size_;
    void initialize(std::function<int64_t(size_t)> f, range r, size_t i) {
        if(r.a > r.b)
            ;
        else if(r.a == r.b)
            tree[i] = f(r.a);
        else {
            size_t mid = (r.a + r.b) / 2;
            initialize(f, {r.a,     mid}, LEFT(i));
            initialize(f, {mid + 1, r.b}, RIGHT(i));
            tree[i] = binary(tree[LEFT(i)], tree[RIGHT(i)]);
            lazy[i] = INT_MAX;
        }
    }
    void apply_lazy_updates(size_t i, range const& r) {
        if(lazy[i] != 0) {
            tree[i] = min(tree[i], lazy[i]);
            if(r.a != r.b) {
                lazy[LEFT(i)]  = min(lazy[i], lazy[LEFT(i)] );
                lazy[RIGHT(i)] = min(lazy[i], lazy[RIGHT(i)]);
            }
            lazy[i] = INT_MAX;
        }
    }
    int64_t get(range const& query, range r, size_t i) {
        apply_lazy_updates(i, r);

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
                return binary(get(query, left,  LEFT(i)),
                              get(query, right, RIGHT(i)));
        }
    }
    void update_range(range target, int64_t delta, range r, size_t i) {
        apply_lazy_updates(i, r);

        if(r.a > target.b || r.b < target.a)
            ;
        else if(target.a <= r.a && r.b <= target.b) {
            tree[i] = min(tree[i], delta);
            if(r.a != r.b) {
                lazy[LEFT(i)]  = min(delta, lazy[LEFT(i)] );
                lazy[RIGHT(i)] = min(delta, lazy[RIGHT(i)]);
            }
        } else {
            size_t mid = (r.a + r.b) / 2;
            update_range(target, delta, {r.a,     mid}, LEFT(i));
            update_range(target, delta, {mid + 1, r.b}, RIGHT(i));
            tree[i] = binary(tree[LEFT(i)], tree[RIGHT(i)]);
        }
    }
public:
    segment_tree(std::function<int64_t(int64_t, int64_t)> binary, size_t n, std::function<int64_t(size_t)> f) : size_(n), binary(binary) {
        size_t m = 1 << static_cast<size_t>(ceil(log2(n)));
        tree.resize(m-1 + m);
        lazy.resize(m-1 + m);
        fill(lazy.begin(), lazy.end(), INT_MAX);
        initialize(f, {0, n-1}, 0);
    }
    segment_tree(std::vector<int64_t> A, std::function<int64_t(int64_t, int64_t)> binary)
        : segment_tree(binary, A.size(), [&](size_t i) { return A[i]; }) {}
    size_t size() const {
        return size_;
    }
    range root() const {
        return {0, size_-1};
    }
    int64_t get(range const& query) {
        return get(query, root(), 0);
    }
    void update_range(range range, int64_t delta) {
        update_range(range, delta, root(), 0);
    }
    std::function<int64_t(int64_t, int64_t)> binary_operation() {
        return binary;
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
    cin >> A;

    segment_tree st(A, [](auto a, auto b) { return max(a, b); });

    for(int i=0; i<M; i++) {
        int64_t type;
        cin >> type;
        if(type == 0) {
            // Update
            int64_t i, j, T;
            cin >> i >> j >> T;
            st.update_range({i-1, j-1}, T);
        } else {
            // Max
            int64_t i, j;
            cin >> i >> j;
            cout << st.get({i-1, j-1}) << endl;
        }
    }
}
