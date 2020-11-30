#include <bits/stdc++.h>

using namespace std;

// https://practice.geeksforgeeks.org/problems/minimum-number-of-jumps-1587115620/1

/*
    minJumps (time complexity: O(n^2), space complexity: O(n))
        Uses a simple dynamic recursive top-down approach to
        memoize the minimum number of jumps for each position
        in a vector. It uses a greedy strategy to search for the
        optimal jump size, starting from the maximum possible jump.
*/

int minJumps(int a[], int n){
    vector<size_t> memo(n, INT_MAX);

    for(int64_t i = n-1; i >= 0; i--)
        for(int64_t j = a[i]; j >= 1; j--)
            if(i + j >= n-1) {
                memo[i] = 1;
                break;
            } else
                memo[i] = min(memo[i], 1 + memo[i + j]);

    return memo[0] == INT_MAX ? -1 : memo[0];
}
