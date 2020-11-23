#include <bits/stdc++.h>

using namespace std;

// https://practice.geeksforgeeks.org/problems/missing-number-in-array/0

/*
    missing_number (time complexity: O(n), space complexity: O(1))
        Given an array with all the numbers 1..N except one, returns the
        missing number. Progressively calculates the expected sum of all
        numbers [1..N] while subtracting the input numbers. This version
        is more numerically stable than simply pre-calculating the
        entire sum, as it avoids overflowing the sum.
*/

int MissingNumber(vector<int>& vec, int n) {
    int sum = vec.size() + 1;
    int i = 1;
    for(auto const& v : vec) {
        sum += i - v;
        i++;
    }
    return sum;
}
