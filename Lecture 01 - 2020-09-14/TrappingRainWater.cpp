#include <bits/stdc++.h>

using namespace std;

// https://practice.geeksforgeeks.org/problems/trapping-rain-water/0

/*
    trapping_rain_water (time complexity: O(n), space complexity: O(1))
        Calculates the number of water accumulated in a given elevation map.
        1. First, it finds the maximum point in the entire array.
        2. Then, it calculates all the water pools on the left and right
           sides of the global maximum and sums their result.
           The array is simply scanned progressively adding the amount of
           water and updating the water level once a greater height is reached.

        Sketch of correctness proof:
            Clearly, an algorithm based on divide-et-impera that recursively
            finds the maximum of a given interval while considering the water
            in between is correct. First, it finds the global maximum, then recurses
            on the remaining left side and the right side, finding maxima and calculating
            the water in between.
            However, let us for example consider the left side: the region occupied by water
            is always going to be on the right side, towards the bigger maximum.
            Therefore, we simply need to recursively find the maxima of each
            left prefix, and consider the water pool on their right.
            We could precalculate the maximum of each prefix and suffix (respectively,
            before and after the global maxima) using O(n) time and O(n) space.
            However, we only really need the *first* maximum of each prefix at any given
            time, which we can identify as we go while summing the pool water: once
            we find a taller block we simply update the maximum.
            This finally gets us to O(1) space complexity and O(n) time complexity.
*/
int trappingWater(int arr[], int n) {
    vector<int> v(arr, arr + n);

    // Find global maximum
    auto p = max_element(v.begin(), v.end());

    int sum = 0;

    // Calculate water from the beginning to the global maximum
    int m = 0;
    for(auto it = v.begin(); it != p; ++it) {
        m = max(m, *it);
        sum += m - *it;
    }

    // Calculate water from the end to the global maximum
    m = 0;
    for(auto it = v.rbegin(); it.base() != p; ++it) {
        m = max(m, *it);
        sum += m - *it;
    }

    return sum;
}
