#include <bits/stdc++.h>

using namespace std;

// https://practice.geeksforgeeks.org/problems/edit-distance3702/1

/*
    editDistance (time complexity: O(n^2), space complexity: O(n^2))
        Uses a simple dynamic recursive top-down approach to
        memoize the edit distance results in a matrix, according to the
        remaining string length.
*/

class Solution {
public:
	int editDistance(string s1, string s2) {
        vector<vector<size_t>> memo(s1.length() + 1, vector<size_t>(s2.length() + 1, -1));

        function<size_t(size_t,size_t)> editDistance_ = [&](size_t i, size_t j) {
            if(memo[i][j] != -1)
                return memo[i][j];
            else {
                size_t return_;
                if(i == 0)
                    return_ = j;
                else if(j == 0)
                    return_ = i;
                else if(s1[i-1] == s2[j-1])
                    return_ = editDistance_(i-1, j-1); // The characters are equal, skip them
                else
                    return_ = min(1 + editDistance_(i-1, j),     // Assume a deleting or inserting operation on the left
                              min(1 + editDistance_(i,   j-1),   // Assume a deleting or inserting operation on the right
                                  1 + editDistance_(i-1, j-1))); // Assume a substitution operation
                return (memo[i][j] = return_);
            }
        };

        return editDistance_(s1.length(), s2.length());
	}
};
