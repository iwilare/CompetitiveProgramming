#include <bits/stdc++.h>

using namespace std;

// https://practice.geeksforgeeks.org/problems/next-larger-element/0

/*
    next_larger_element (time complexity: O(n), space complexity: O(n))
        Uses a stack to keep track of non-contiguous decreasing sequences of elements (their indices).
        When a new element is encountered, all the elements smaller than the new one
        are removed from the stack. As a consequence, the stack will always be decreasingly ordered.
        The elements still waiting in the stack will have no next greater element.
*/
template<typename T> vector<T> nextLargerElement(T arr[], int n){
    vector<T> A(arr, arr + n);

    vector<T> nexts(A.size());
    fill(nexts.begin(), nexts.end(), -1);

    vector<T> S;
    S.reserve(A.size());

    for(int i = 0; i < A.size(); i++) {
        // Flush all the elements smaller than the new one
        while(!S.empty() && A[i] >= A[S.back()]) {
            nexts[S.back()] = A[i];
            S.pop_back();
        }

        S.push_back(i);
    }

    return nexts;
}
