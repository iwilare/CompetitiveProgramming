#include <bits/stdc++.h>

using namespace std;

// https://practice.geeksforgeeks.org/problems/longest-common-subsequence/0

/*
    lcs (time complexity: O(n^2), space complexity: O(n^2))
        Uses a simple dynamic recursive top-down approach to
        memoize the lcs results in a matrix.
*/
int lcs(int x, int y, string s1, string s2) {
    vector<vector<int>> memo(x + 1, vector<int>(y + 1, -1));

    function<int(int,int)> lcs_ = [&](int x, int y) {
        if(memo[x][y] != -1)
            return memo[x][y];
        else {
            int return_;
            if(x == 0 || y == 0)
                return_ = 0;
            else if(s1[x-1] == s2[y-1])
                return_ = 1 + lcs_(x-1, y-1);
            else
                return_ = max(lcs_(x-1, y), lcs_(x, y-1));
            return (memo[x][y] = return_);
        }
    };

    return lcs_(x, y);
}
