#include <iostream>
#include <vector>
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
template<typename T> vector<T> leaders(vector<T> const& vec) {
    vector<T> leaders;
    leaders.reserve(vec.size());

    int max = INT_MIN;

    for(auto it = vec.rbegin(); it != vec.rend(); it++)
        if(*it >= max) {
            max = *it;
            leaders.push_back(max);
        }

    reverse(leaders.begin(), leaders.end());

    return leaders;
}

int main() {
    int T;
    cin >> T;

    for(int t = 0; t < T; t++) {
        int N;
        cin >> N;

        vector<int> A;
        A.reserve(N);
        for(int i = 0; i < N; i++) {
            int x;
            cin >> x;
            A.push_back(x);
        }

        vector<int> result = leaders(A);

        for(const auto v : result)
            cout << v << " ";
        cout << endl;
    }
}