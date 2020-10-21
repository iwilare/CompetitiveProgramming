#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

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

size_t inversion_count(vector<int64_t>& A) {
    vector<pair<int64_t, size_t>> indexed(A.size());
    for(size_t i = 0; i < A.size(); i++)
        indexed[i] = make_pair(A[i], i);

    sort(indexed.begin(), indexed.end());

    vector<int64_t> remap(A.size());
    for(size_t i = 0; i < indexed.size(); i++)
        remap[indexed[i].second] = i + 1;

    fenwick_tree<int64_t> ft(A.size());

    uint64_t count = 0;
    for(auto it = remap.rbegin(); it != remap.rend(); ++it) {
        ft.add(*it, 1);
        count += ft.sum(*it-1);
    }

    return count;
}
