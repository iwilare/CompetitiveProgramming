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

using namespace std;

// https://codeforces.com/problemset/problem/52/C

/*
    circular_rmq (space complexity: O(n), time complexity: O(n log n))
        Simply reuse a segment tree with range updates and lazy propagation.
        Circular queries are trivially decomposed into two standard queries
        where the indices i, j are such that i <= j.
*/

template<typename T> T circular_get(segment_tree<T>& st, size_t i, size_t j) {
    if(i <= j)
        return st.get({i, j});
    else
        return st.binary_operation()(st.get({i, st.size()-1}), st.get({0, j}));
}
template<typename T> void circular_range_update(segment_tree<T>& st, size_t i, size_t j, int64_t delta) {
    if(i <= j)
        st.update_range({i, j}, delta);
    else {
        st.update_range({i, st.size()-1}, delta);
        st.update_range({0, j}, delta);
    }
}

template<typename T> vector<T> read_sequence(size_t n) {
    vector<T> input(n);
    for(size_t i = 0; i < n; i++)
        cin >> input[i];
    return input;
}

int main() {
	size_t N;
	cin >> N;

    auto minimum = [](auto a, auto b) { return min(a, b); };
	segment_tree<int64_t> st(read_sequence<int64_t>(N), minimum);

	size_t K;
	cin >> K;

	char line[32];
	cin.getline(line, 32); // Skip newline from previous line
	for(int i = 0; i < K; i++) {
		cin.getline(line, 32);
		int64_t start = atoi(strtok(line, " "));
		int64_t end = atoi(strtok(NULL, " "));
		char* delta = strtok(NULL, " ");
		if(delta == NULL)
			cout << circular_get(st, start, end) << endl;
		else
			circular_range_update(st, start, end, atoi(delta));
	}

    return 0;
}
