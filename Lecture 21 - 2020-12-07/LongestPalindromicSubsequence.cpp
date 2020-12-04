#include <bits/stdc++.h>

using namespace std;

// https://practice.geeksforgeeks.org/problems/longest-palindromic-subsequence/0

/*
    longest_palindromic_subsequence (time complexity: O(n^2), space complexity: O(n^2))
        Uses a simple dynamic bottom-up approach to memoize the
        result of the recurrence relation on palindromic subsequences.
        Note that if we used indices to denote beginning and end of
        the subsequence this would create a symmetric matrix, since
        the two indices are allowed to go past each other while maintaining
        the correct palindromic reference to both ends of the string.
        The representation employed here avoids filling half the matrix.
        The i index is used to keep track of the beginning of the subsequence,
        while j is used to denote its length. This simplifies how the matrix
        is filled, since the recurrence relation clearly "terminates"
        with strictly decreasing indices down to the base cases.
*/

int64_t longest_palindromic_subsequence(string s) {
    int64_t m[s.length() + 1][s.length() + 1];

    // Base cases: subsequence has length zero or one
    for(int64_t i = 0; i <= s.length(); i++)
        m[i][0] = 0,
        m[i][1] = 1;

    // Start from length 2,
    for(int64_t j = 2; j <= s.length(); j++)
        // Compute the LPS for all valid subsequences of length j
        for(int64_t i = 0; i <= s.length() - j; i++)
            m[i][j] = s[i] == s[i + (j-1)]         // If the two ends of the subsequence are equal,
                    ? 2 + m[i+1][j-2]              // Add them to the sequence and skip both
                    : max(m[i+1][j-1], m[i][j-1]); // Try deleting one either at the start or at the end

    return m[0][s.length()];
}

int main() {
    size_t T;
    cin >> T;
    for(size_t t = 0; t < T; t++) {
        string s;
        cin >> s;
        cout << longest_palindromic_subsequence(s) << endl;
    }
}
