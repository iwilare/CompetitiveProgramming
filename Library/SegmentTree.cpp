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
