#include <vector>

template<typename T> class fenwick_tree {
    std::vector<T> tree;
public:
    fenwick_tree(size_t n) : tree(n + 1) {}

    T sum(size_t i) {
        T sum = 0;
        for(i++; i > 0; i -= i & -i)
            sum += tree[i];
        return sum;
    }

    T range(size_t i, size_t j) {
        return sum(j) - sum(i - 1);
    }

    void add(size_t i, T v) {
        for(i++; i < tree.size(); i += i & -i)
            tree[i] += v;
    }
};
