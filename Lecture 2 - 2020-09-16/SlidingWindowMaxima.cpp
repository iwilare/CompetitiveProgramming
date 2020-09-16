#include <iostream>
#include <vector>
#include <deque>

using namespace std;

// https://practice.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k/0

/*
    sliding_window_maxima (time complexity: O(n), space complexity: O(k))
        Returns all the maxima in all subarrays in the form A[i..i+k-1].
        A deque is used to maintain an ordered list of the right leaders
        present in the window and achieve optimal complexity.
*/
template<typename T> vector<T> sliding_window_maxima(vector<T> const& A, int k) {
    deque<T> Q; // A queue of indices, maintaining the highest leader at the front
    vector<T> maxima;
    maxima.reserve(A.size() - k + 1);

    for(int i = 0; i < A.size(); i++) {
        // Remove the biggest leaders who are out of the window
        while(!Q.empty() && Q.front() <= i - k)
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

int main() {
    int T;
    cin >> T;

    for(int t = 0; t < T; t++) {
        int N;
        cin >> N;

        int K;
        cin >> K;

        vector<int> A;
        A.reserve(N);
        for(int i = 0; i < N; i++) {
            int x;
            cin >> x;
            A.push_back(x);
        }

        vector<int> result = sliding_window_maxima(A, K);

        for(auto const& v : result)
            cout << v << " ";

        cout << endl;
    }
}