#include <bits/stdc++.h>

using namespace std;

// https://practice.geeksforgeeks.org/problems/longest-common-subsequence/0

/*
    lcs (time complexity: O(nm), space complexity: O(nm))
        Uses a simple dynamic bottom-up approach to
        memoize the lcs results in a matrix.
*/
int lcs(int x, int y, string s1, string s2) {
    int m[x + 1][y + 1];

    for(size_t i = 0; i <= x; i++)
        for(size_t j = 0; j <= y; j++)
            m[i][j] // Edge case, the substrings are empty
                    = i == 0 || j == 0 ? 0
                    // If they start with an equal character, skip it and add it to the subsequence
                    : s1[i-1] == s2[j-1] ? 1 + m[i-1][j-1]
                    // Else, non-deterministically remove a character from one of the strings
                    : max(m[i-1][j], m[i][j-1]);
    return m[x][y];
}
