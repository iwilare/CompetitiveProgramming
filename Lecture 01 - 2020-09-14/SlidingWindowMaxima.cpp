#include <bits/stdc++.h>

using namespace std;

// https://practice.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k/0

/*
    sliding_window_maxima (time complexity: O(n), space complexity: O(k))
        Returns all the maxima in all subarrays in the form A[i..i+k-1].
        A deque is used to maintain an ordered list of the right leaders
        present in the window and achieve optimal complexity.
*/
vector<int> max_of_subarrays(int *arr, int n, int k) {
    vector<int> A(arr, arr + n);

    deque<int> Q; // A queue of indices, maintaining the highest leader at the front
    vector<int> maxima;
    maxima.reserve(A.size() - k + 1);

    for(int i = 0; i < A.size(); i++) {
        // Remove the biggest leader if it is out of the window
        if(!Q.empty() && Q.front() <= i - k)
            Q.pop_front();

        // Remove the lower leaders who are smaller than the next element
        while(!Q.empty() && A[i] >= A[Q.back()])
            Q.pop_back();

        Q.push_back(i);

         // If the window fully moved after the beginning, we can start adding maxima
        if(i >= k - 1)
            maxima.push_back(A[Q.front()]);
    }

    return maxima;
}
