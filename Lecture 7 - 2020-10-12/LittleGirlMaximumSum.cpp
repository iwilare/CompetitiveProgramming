#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// https://codeforces.com/problemset/problem/276/C?locale=en

/*
    little_girl_maximum_sum (time complexity: O(n log n), space complexity: O(n))
        First, calculate the times each point in the vector is within a segment.
        This is done in O(n) time through the use of prefix sums, and is the
        main objective of the algorithm.
        Then, the original array is ordered and permuted so the greatest elements
        go to the most frequently touched positions.
        Finally, the queries are each answered in O(1) by again employing prefix sums,
        now calculated on the optimal permutation.
*/

/*
    calculate_frequencies (time complexity: O(n), space complexity: O(n))
        Calculate frequencies using an approach similar to an eulerian visit,
        by adding to the points where a segment starts, subtracting 1 where a segment
        ends and then taking all the prefix sums.
        (this approach could have also been used in the "maximum segment intersection"
        problem, but in this case we actually need to visit all the elements
        and indices of the original array, whereas it was not necessary in the MSI problem.)
*/
vector<int64_t> calculate_frequencies(vector<uint64_t> A, vector<pair<int64_t, int64_t>> queries) {
    vector<int64_t> partial_sum_frequencies(A.size());
    vector<int64_t> frequencies(A.size());

    for(auto const& q : queries) {
        partial_sum_frequencies[q.first-1] += 1; // Start of a segment
        if(q.second-1 + 1 < A.size())
            partial_sum_frequencies[q.second-1 + 1] -= 1; // End of a segment
    }

    frequencies[0] = partial_sum_frequencies[0];
    for(size_t i = 1; i < A.size(); i++)
        frequencies[i] = frequencies[i-1] + partial_sum_frequencies[i];

    return frequencies;
}

int64_t little_girl_maximum_sum(vector<uint64_t> A, vector<pair<int64_t, int64_t>> queries) {
    vector<int64_t> frequencies = calculate_frequencies(A, queries);

    // Create the permutation

    vector<pair<uint64_t, size_t>> indexed_frequencies(A.size());
    vector<uint64_t> permutation(A.size());

    for(size_t i = 0; i < A.size(); i++)
        indexed_frequencies[i] = make_pair(frequencies[i], i);

    sort(indexed_frequencies.begin(), indexed_frequencies.end()); // Defaults to sorting on .first
    sort(A.begin(), A.end());

    for(size_t i = 0; i < A.size(); i++)
        permutation[indexed_frequencies[i].second] = A[i];

    // Finally run the simulation on the permutation

    vector<uint64_t> partial_sums(A.size());

    partial_sums[0] = permutation[0];
    for(size_t i = 1; i < A.size(); i++)
        partial_sums[i] = partial_sums[i-1] + permutation[i];

    // Calculate the sum

    uint64_t sum = 0;
    for(auto const& q : queries)
        sum += partial_sums[q.second-1] - (q.first-1 - 1 >= 0 ? partial_sums[q.first-1 - 1] : 0);

    return sum;
}

template<typename T> vector<T> read_sequence(size_t n) {
    vector<T> input(n);
    for(size_t i = 0; i < n; i++)
        cin >> input[i];
    return input;
}

template<typename L, typename R> vector<pair<L, R>> read_sequence2(size_t n) {
    vector<pair<L, R>> input;
    input.reserve(n);
    for(size_t i = 0; i < n; i++) {
        L a; R b;
        cin >> a >> b;
        input.emplace_back(a, b);
    }
    return input;
}

int main() {
    size_t N, Q;
    cin >> N >> Q;

    auto A = read_sequence<uint64_t>(N);
    auto queries = read_sequence2<int64_t, int64_t>(Q);

    cout << little_girl_maximum_sum(A, queries) << endl;
}
