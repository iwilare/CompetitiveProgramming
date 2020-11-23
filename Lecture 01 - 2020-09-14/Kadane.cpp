#include <bits/stdc++.h>

using namespace std;

// https://practice.geeksforgeeks.org/problems/kadanes-algorithm/0

/*
    kadane (time complexity: O(n), space complexity: O(1))
        Finds the subarray with the maximum sum and returns its sum.
        Exploits the following properties:
            1. the maximum sum subarray cannot begin with a
               negative number (otherwise it could be removed
               to obtain a better solution);
            2. the sum of each prefix in the maximum sum subarray
               must be positive (otherwise we could remove the
               prefix to obtain a better solution);
*/
int maxSubarraySum(int arr[], int n) {
    vector<int> vec(arr, arr + n);

    int max_sum = INT_MIN, sum = 0;

    for(const auto& v : vec) {
        sum     = max(v, sum + v);
        max_sum = max(max_sum, sum);
    }

    return max_sum;
}
