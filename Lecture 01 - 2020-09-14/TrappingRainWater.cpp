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
            finds maxima while considering the water in between is correct.
            Considering for example the left side, the region occupied by water
            is always going to be on the right side, towards the bigger maximum.
            Therefore, we simply need to recursively find the maxima of each
            left prefix, and consider the water pool on the right.
            We could precalculate the maximum of each prefix and suffix (respectively,
            before and after the global maxima) using O(n) time and O(n) space.
            However, we only really need the first maximum of each prefix, which we can
            identify as we go while summing the pool water: once we find a taller block
            we simply update the maximum.
            This finally gets us to O(1) space complexity and O(n) time complexity.
*/
int trappingWater(int arr[], int n) {
    vector<int> v(arr, arr + n);
    // Find global maximum
    auto p = max_element(v.begin(), v.end()) - v.begin();

    int sum = 0;

    // Calculate water from the beginning to the global maximum
    for(int i = 1, m = 0; i <= p; i++) {
        if(v[i] >= v[m])
            m = i;
        sum += v[m] - v[i];
    }

    // Calculate water from the end to the global maximum
    for(int i = v.size()-2, m = v.size()-1; i >= p; i--) {
        if(v[i] >= v[m])
            m = i;
        sum += v[m] - v[i];
    }

    return sum;
}
