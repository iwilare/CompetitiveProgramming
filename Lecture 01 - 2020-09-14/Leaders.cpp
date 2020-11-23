#include <bits/stdc++.h>

using namespace std;

// https://practice.geeksforgeeks.org/problems/leaders-in-an-array/0

/*
    leaders (time complexity: O(n), space complexity: O(1))
        Returns all the leaders in a given array.
        A (right) leader is an element bigger than all elements to its right.
        Scans the array from the right side and progressively accumulates
        them (right-to-left) in a vector if they are larger than the
        maximum of the current suffix. Finally, it reverses the result.
*/

template<typename T> vector<T> leaders(T arr[], int n) {
    vector<T> vec(arr, arr + n);

    vector<T> leaders;
    leaders.reserve(vec.size());

    T max = INT_MIN;

    for(auto it = vec.rbegin(); it != vec.rend(); it++)
        if(*it >= max) {
            max = *it;
            leaders.push_back(max);
        }

    reverse(leaders.begin(), leaders.end());

    return leaders;
}
