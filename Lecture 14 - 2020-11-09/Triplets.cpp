#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <set>

#include <vector>

template<typename T> class fenwick_tree {
    std::vector<T> tree;
public:
    fenwick_tree(size_t n) : tree(n + 1) {}

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

vector<int64_t> remap(vector<int64_t> A) {
    vector<pair<int64_t, size_t>> indexed(A.size());
    for(size_t i = 0; i < A.size(); i++)
        indexed[i] = make_pair(A[i], i);

    sort(indexed.begin(), indexed.end());

    vector<int64_t> remapped(A.size());
    int64_t index = 0;
    for(size_t i = 0; i < indexed.size(); i++) {
        auto v = indexed[i].first;
        while(v == indexed[i].first) // Remap with equal rankings
            remapped[indexed[i++].second] = index;
        index++;
        i--;
    }

    return remapped;
}

/*
    triplets (time complexity: O(n log n), space complexity: O(n))
        Use two Fenwick trees, one to count the number of elements in the prefix
        and one to count the number of elements in the suffix larger and smaller than
        the current value. Then, scan linearly the array and multiply these two
        numbers to obtain all possibilities.
*/

size_t triplets(vector<int64_t> R) {
    auto A = remap(R);
    fenwick_tree<int64_t> before(A.size());
    fenwick_tree<int64_t> after(A.size());

    before.add(A[0], 1);
    for(size_t i = 2; i < A.size(); i++)
        after.add(A[i], 1);

    size_t sum = 0;
    for(size_t i = 1; i < A.size() - 1; i++) {
        sum += before.sum(A[i]-1) * (after.sum(A.size()-1) - after.sum(A[i]));
        before.add(A[i], 1);
        after.add(A[i+1], -1);
    }
    return sum;
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

    auto A = read_sequence<int64_t>(N);

    cout << triplets(A) << endl;
}
