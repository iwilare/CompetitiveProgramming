#include <bits/stdc++.h>

using namespace std;

// https://practice.geeksforgeeks.org/problems/minimum-number-of-jumps-1587115620/1

/*
    minJumps (time complexity: O(n), space complexity: O(1))
        Implements a linear solution for this problem by progressively
        keeping track of the maximum reachable point in the array
        and the number of steps that can still be done to move forward,
        starting from the left starting point.
*/

int minJumps(int arr[], int n) {
    int max_reachable = arr[0];
    int steps         = arr[0];
    int jumps         = 0;
    // Start from the beginning up to the last element,
    // using one step each time we go forward.
    for(int i = 0; i < n - 1; i++, steps--) {
        // Update the maximum reachable place.
        max_reachable = max(max_reachable, i + arr[i]);
        // Walk forward by one.
        if(max_reachable == i) // If we already reached the limit, we can't
            return -1;         // improve it anymore so we have to give up.
        else if(steps <= 0) {
            // If we finished the steps,
            // it means we must have jumped somewhere between
            // the current place and the base.
            jumps++;
            // Thus, restore the steps so that we can reach
            // eaxctly the maximum reachable place, so that
            // at most (max - current) steps will be taken.
            steps = max_reachable - i;
        }
    }
    // If we can reach the end, one
    // last jump is sufficient reach it.
    return jumps + (n > 1 ? 1 : 0);
}
