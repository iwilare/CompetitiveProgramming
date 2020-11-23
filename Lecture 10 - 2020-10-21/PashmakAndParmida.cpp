#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

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

    void add(size_t i, T v) {
        for(i++; i < tree.size(); i += i & -i)
            tree[i] += v;
    }
};

using namespace std;

// https://codeforces.com/problemset/problem/459/D

/*
    pashmak_and_parmida (time complexity: O(n log n), space complexity: O(n))
        Starting from right to left, use a Fenwick tree to progressively calculate f(j, n, a[j])
        for all possible j in the suffix. The value f(0, i, a[i]) is calculated by precomputing
        the total frequencies and then subtracting as we go towards the left.
        The Fenwick tree uses the "index by the frequency; add one; sum from 0 to i" tecnique,
        similar as Inversion count, and is used to calculate the number of all suffix frequencies
        that are smaller than the current prefix one. Since we do not remove the previous frequencies,
        as we go, the frequency is calculated over all possible suffixes.
*/

// size_t does not work on CodeForces, uint64_t apparently does;
// Running time extremely close to the limit: 2776, 2698, 2682 ms
uint64_t pashmak_and_parmida(vector<int64_t> const& A) {
    // Populate all the suffix frequencies (we will later start from the end to the beginning)
    unordered_map<int64_t, uint64_t> totalPrefixFrequencies;
    for(auto it = A.begin(); it != A.end(); ++it)
        totalPrefixFrequencies[*it]++;

    fenwick_tree<uint64_t> countIndexedByFrequencies(A.size());
    unordered_map<int64_t, uint64_t> suffixFrequencies;

    uint64_t count = 0;
    for(auto it = A.rbegin(); it != A.rend(); ++it) {
        // Add all the number of frequencies that are smaller than the current one;
        // the prefix frequency of the next left element is removed for the next iteration.
        // It is a preincrement because it is a strict < bound, so the current element doesn't count.
        count += countIndexedByFrequencies.sum(--totalPrefixFrequencies[*it]);

        // Shift the suffix frequency of the current element one position to the left;
        // We don't need to remove the previous frequency because j need not be adjacent to i, and
        // in this way we effectively sum up over all the possible previous suffixes, not just the current one.
        countIndexedByFrequencies.add(++suffixFrequencies[*it], 1);
    }

    return count;
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

    cout << pashmak_and_parmida(A) << endl;
}
