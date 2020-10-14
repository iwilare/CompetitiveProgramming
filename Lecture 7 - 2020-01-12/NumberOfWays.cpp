#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// https://codeforces.com/problemset/problem/466/C

/*
    number_of_ways (time complexity: O(n), space complexity: O(n))
        Calculates all the prefix and suffix sums; then counts for each position
        the number of suffixes to the right that sum up to S/3, where S is the
        total sum of the array. Finally, scans the array looking for left prefixes where
        the sum is again S/3. If one is found such that the remaining part of the array
        also sums up to S*2/3, then we add the number of possible S/3 suffixes previously
        calculated.
*/

int64_t number_of_ways(vector<int64_t> A) {
    int64_t sum = 0;
    for(auto const& v : A)
        sum += v;

    if(sum % 3 != 0)
        return 0;
    else {
        int64_t target = sum / 3;

        // Calculate all the prefix sums
        vector<int64_t> prefix(A.size());
        prefix[0] = A[0];
        for(int64_t i = 1; i < A.size(); i++)
            prefix[i] = A[i] + prefix[i-1];

        // Calculate all the suffix sums
        vector<int64_t> suffix(A.size());
        suffix[A.size()-1] = A[A.size()-1];
        for(int64_t i = A.size()-2; i >= 0; i--)
            suffix[i] = A[i] + suffix[i+1];

        // Sum up from right the number of suffixes whose sum is target
        vector<int64_t> totalTargetSuffixes(A.size());
        totalTargetSuffixes[A.size()-1] = 0;
        for(int64_t i = A.size()-2; i >= 0; i--)
            totalTargetSuffixes[i] = (suffix[i+1] == target ? 1 : 0) + totalTargetSuffixes[i+1];

        // Finally, count the total number of ways by scanning all the left prefixes
        // and adding the number of possible right partitions
        int64_t count = 0;
        for(int64_t i = 0; i < A.size()-2; i++)
            if(prefix[i] == target && suffix[i+1] == 2*target)
                count += totalTargetSuffixes[i+1];
        return count;
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

    cout << number_of_ways(read_sequence<int64_t>(N)) << endl;
}
