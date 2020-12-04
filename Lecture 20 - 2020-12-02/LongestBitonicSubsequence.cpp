#include <bits/stdc++.h>

using namespace std;

// https://practice.geeksforgeeks.org/problems/longest-bitonic-subsequence0824/1

/*
    longest_bitonic_subsequence (time complexity: O(n log n), space complexity: O(n))
        Reuses the LongestIncreasingSubsequence solution to
        achieve the same complexity. For each element, both the
        longest increasing and decreasing subsequences are calculated,
        considering the prefix up to the element and the suffix after it.
        The value whose sum of the two lengths is the maximum.
*/

class Solution {
    template<typename T> vector<int> longestSubsequence(vector<T> a) {
        vector<int> result;
        map<T, int> doms;
        int m = 0;
        for(auto const v : a) {
            auto pred = doms.lower_bound(v);
            int lis = 1 + (doms.size() > 0 && pred != doms.begin() ? (--pred)->second : 0);

            for(auto ub = doms.upper_bound(v);
                ub != doms.end() && ub->second <= lis;
                ub = doms.erase(ub))
                ;

            m = max(m, lis);
            doms.insert({v, lis});
            result.push_back(m);
        }
        return result;
    }
public:
	int LongestBitonicSequence(vector<int> nums) {
	    auto a = longestSubsequence(nums);

	    reverse(nums.begin(), nums.end());
	    auto b = longestSubsequence(nums);
	    reverse(b.begin(), b.end());

	    // Zip with + and reduce with max
	    return inner_product(a.begin(), a.end(), b.begin(), 0, [](int a, int b){ return max(a, b); }, plus<int>()) - 1;
	}
};
