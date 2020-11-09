#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <functional>
#include <cmath>
#include <sstream>
#include <cstring>

#define LEFT(i)  (2 * (i) + 1)
#define RIGHT(i) (2 * (i) + 2)

struct range {
    size_t a, b;
    range(size_t a, size_t b) : a(a), b(b) {}
};

template<typename T> class segment_tree {
    std::vector<T> tree;
    std::vector<T> lazy;
    std::function<T(T, T)> binary;
    size_t size_;
    void initialize(std::function<T(size_t)> f, range r, size_t i) {
        if(r.a > r.b)
            ;
        else if(r.a == r.b)
            tree[i] = f(r.a);
        else {
            size_t mid = (r.a + r.b) / 2;
            initialize(f, {r.a,     mid}, LEFT(i));
            initialize(f, {mid + 1, r.b}, RIGHT(i));
            tree[i] = binary(tree[LEFT(i)], tree[RIGHT(i)]);
            lazy[i] = 0;
        }
    }
    void apply_lazy_updates(size_t i, range const& r) {
        if(lazy[i] != 0) {
            tree[i] += lazy[i]; // Valid since: min(x + A) = x + min(A)
            if(r.a != r.b) {
                lazy[LEFT(i)]  += lazy[i];
                lazy[RIGHT(i)] += lazy[i];
            }
            lazy[i] = 0;
        }
    }
    T get(range const& query, range r, size_t i) {
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
    void update(size_t target, std::function<T(T)> u, range r, size_t i) {
        apply_lazy_updates(i, r);

        if(target < r.a || r.b < target)
            ;
        else if(r.a == r.b)
            tree[i] = u(tree[i]);
        else {
            size_t mid = (r.a + r.b) / 2;
            update(target, u, {r.a,     mid}, LEFT(i));
            update(target, u, {mid + 1, r.b}, RIGHT(i));
            tree[i] = binary(tree[LEFT(i)], tree[RIGHT(i)]);
        }
    }
    void update_range(range target, T delta, range r, size_t i) {
        apply_lazy_updates(i, r);

        if(r.a > target.b || r.b < target.a)
            ;
        else if(target.a <= r.a && r.b <= target.b) {
            tree[i] += delta; // Valid since: min(x + A) = x + min(A)
            if(r.a != r.b) {
                lazy[LEFT(i)]  += delta;
                lazy[RIGHT(i)] += delta;
            }
        } else {
            size_t mid = (r.a + r.b) / 2;
            update_range(target, delta, {r.a,     mid}, LEFT(i));
            update_range(target, delta, {mid + 1, r.b}, RIGHT(i));
            tree[i] = binary(tree[LEFT(i)], tree[RIGHT(i)]);
        }
    }
public:
    segment_tree(std::function<T(T, T)> binary, size_t n, std::function<T(size_t)> f) : size_(n), binary(binary) {
        size_t m = 1 << static_cast<size_t>(ceil(log2(n)));
        tree.resize(m-1 + m);
        lazy.resize(m-1 + m);
        initialize(f, {0, n-1}, 0);
    }
    segment_tree(size_t n, std::function<T(T, T)> binary)
        : segment_tree(binary, n, [&](size_t i) { return 0; }) {}
    segment_tree(std::vector<T> A, std::function<T(T, T)> binary)
        : segment_tree(binary, A.size(), [&](size_t i) { return A[i]; }) {}
    size_t size() const {
        return size_;
    }
    range root() const {
        return {0, size_-1};
    }
    T get(range const& query) {
        return get(query, root(), 0);
    }
    void update(size_t i, std::function<T(T)> u) {
        update(i, u, root(), 0);
    }
    void update_range(range range, T delta) {
        update_range(range, delta, root(), 0);
    }
    std::function<T(T, T)> binary_operation() {
        return binary;
    }
};
