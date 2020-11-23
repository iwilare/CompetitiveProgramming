#include <bits/stdc++.h>

using namespace std;

// https://practice.geeksforgeeks.org/problems/subset-sum-problem2014/1

/*
    equalPartition (time complexity: O(n * sum), space complexity: O(n * sum))
        First, calculates the total sum, and divides it by two.
        Then, it uses a simple dynamic recursive bottom-up approach to
        search for a subset that sums up to half the total sum.
        The size of the matrix is proportional to the number of the elements
        and the numerical value of (half) the sum of all the elements.
*/

class Solution {
public:
    bool equalPartition(int N, int arr[]) {
        int total = accumulate(arr, arr + N, 0);
        int target = total / 2;

        bool m[N + 1][target + 1];

        for(size_t i = 0; i <= N; i++)
            m[i][0] = true;
        for(size_t j = 1; j <= target; j++)
            m[0][j] = false;
        for(size_t i = 1; i <= N; i++)
            for(size_t j = 1; j <= target; j++)
                m[i][j] = m[i-1][j] || j - arr[i-1] >= 0 && m[i-1][j - arr[i-1]];

        return total % 2 != 0 ? false : m[N][target];
    }
};
