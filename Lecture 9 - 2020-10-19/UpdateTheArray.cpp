#include <iostream>
#include <vector>

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

// https://www.spoj.com/problems/UPDATEIT/

/*
    update_array (time complexity: O(n log n), space complexity: O(n))
        Simply use a Fenwick Tree. For any update, add the value to the
        beginning of the range and subtract the same value at the end.
        This mirrors the concept of eulerian visit of the tree, where the
        value of the node is added at the beginning and removed at the
        end of the subtree visit.
*/

int main() {
    size_t T;
    cin >> T;

    for(size_t t = 0; t < T; t++) {
        size_t N, U;
        cin >> N >> U;

        fenwick_tree<int64_t> ft(N + 1);

        int64_t l, r, v;
        for(size_t i = 0; i < U; i++) {
            cin >> l >> r >> v;
            ft.add(l, v);
            ft.add(r + 1, -v);
        }

        size_t Q;
        cin >> Q;
        for(size_t i = 0; i < Q; ++i) {
            int64_t l;
            cin >> l;
            cout << ft.sum(l) << endl;
        }
    }
}
