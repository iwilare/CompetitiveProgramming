#include <bits/stdc++.h>

using namespace std;

// https://practice.geeksforgeeks.org/problems/edit-distance3702/1

/*
    editDistance (time complexity: O(n^2), space complexity: O(n^2))
        Uses a simple dynamic bottom-up approach to
        memoize the edit distance results in a matrix, according to the
        remaining string length.
*/

class Solution {
public:
	int editDistance(string s1, string s2) {
        size_t d[s1.length() + 1][s2.length() + 1];

        for(int i = 0; i <= s1.length(); i++)
            d[i][0] = i;
        for(int j = 0; j <= s2.length(); j++)
            d[0][j] = j;
        for(int i = 1; i <= s1.length(); i++)
            for(int j = 1; j <= s2.length(); j++)
                d[i][j] = s1[i-1] == s2[j-1]
                        ? d[i-1][j-1]             // The characters are equal, skip them
                        : min({1 + d[i-1][j],     // Assume a deleting or inserting operation on the left
                               1 + d[i][j-1],     // Assume a deleting or inserting operation on the right
                               1 + d[i-1][j-1]}); // Assume a substitution operation
        return d[s1.length()][s2.length()];
	}
};
