#include <bits/stdc++.h>

using namespace std;

// https://practice.geeksforgeeks.org/problems/longest-increasing-subsequence-1587115620/1

/*
    longest_increasing_subsequence (time complexity: O(n log n), space complexity: O(n))
        Exploits the concept of dominant elements and a BST to keep
        track of them and achieve a better complexity than the O(n^2) time
        and O(n) space of a dynamic programming approach.
        An element A[i] dominates A[j] iff A[i] < A[j] and LIS[i] >= LIS[j].
        First, we calculate the LIS of the new element, by "concatenating" it
        to the subsequence of the dominating element immediately before this one.
        Thus, its LIS will be the LIS of the preceding element in the map plus one.
        Then, we remove all the elements that the current one dominates.
        The inner for loop can iterate at most O(n) overall because no element
        can be removed twice.
*/

int longestSubsequence(int n, int a[]) {
    size_t m = 0;
    map<int, size_t> doms;
    for(int i = 0; i < n; i++) {
        // Update LIS
        auto pred = doms.lower_bound(a[i]);
        size_t lis = 1 + (doms.size() > 0 && pred != doms.begin() ? (--pred)->second : 0);

        // Remove dominated elements
        for(auto ub = doms.upper_bound(a[i]);
            ub != doms.end() && ub->second <= lis;
            ub = doms.erase(ub))
            ;

        // Insert the element and update the max
        m = max(m, lis);
        doms.insert({a[i], lis});
    }
    return m;
}
