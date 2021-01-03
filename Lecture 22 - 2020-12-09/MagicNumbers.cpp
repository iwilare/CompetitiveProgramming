#include <bits/stdc++.h>

using namespace std;

// https://codeforces.com/problemset/problem/320/A?locale=en

/*
    magic_numbers (time complexity: O(n), space complexity: O(1))
        Simply greedily check for the longest subpattern in the
        string representation of the number. When such a pattern is
        found, it is simply skipped and the property is recursively
        checked for the remaining substring.
*/

bool magic_number(string s) {
    for(size_t i = 0; i < s.length();)
        if(s.substr(i, 3) == "144") i += 3; else
        if(s.substr(i, 2) == "14")  i += 2; else
        if(s.substr(i, 1) == "1")   i += 1; else
        return false;
    return true;
}

int main() {
    string N;
    getline(cin, N);

    cout << (magic_number(N) ? "YES" : "NO");
}
