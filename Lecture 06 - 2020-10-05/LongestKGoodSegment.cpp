#include <bits/stdc++.h>

using namespace std;

// https://codeforces.com/contest/616/problem/D?locale=en

/*
    longest_k_good_segment (time complexity: O(n), space complexity: O(k))
        Uses an unordered map (assuming constant time operations) to maintain a
        list of all the elements in the map, and associating them with their frequencies.
        Then, the array is scanned linearly while keeping two pointers; if the size of
        the map is smaller than K, the right pointer is advanced. When the map reaches
        size K, the left pointer is moved until there are no more than K different elements
        within the map. The map is updated accordingly in both cases, with the length
        of the window being tracked for the maximum.
*/

pair<int, int> longest_k_good_segment(vector<int> A, int K) {
    unordered_map<int, int> window;
    // There will always be at most K+1 elements, K+1 before shrinking it again.
    window.reserve(K + 1);

    auto left       = A.begin();
    auto right      = A.begin();
    int  max_length = 0;
    auto max_left   = A.end();
    auto max_right  = A.end();

    while(right != A.end()) {
        // Move the end of the window to the right,
        // and insert the corresponding element.
        ++window[*right];
        ++right;

        // Ensure again that the window size does not exceed K distinct elements;
        for(; window.size() > K; ++left)
            // if so, keep removing left elements until the invariant is restored.
            if(--window[*left] == 0)
                window.erase(*left);

        // Update the maximum if necessary.
        if(right - left > max_length) {
            max_length = right - left;
            max_left   = left;
            max_right  = right;
        }
    }

    // right does not include the new element, get the inclusive index with -1
    return make_pair(max_left - A.begin(), max_right - 1 - A.begin());
}

template<typename T> vector<T> fast_read_sequence(size_t n) {
    vector<T> input(n);
    for(size_t i = 0; i < n; i++)
        scanf("%d", &input[i]);
    return input;
}

int main() {
    int N, K;
    scanf("%d%d", &N, &K);

    auto result = longest_k_good_segment(fast_read_sequence<int>(N), K);

    printf("%d %d\n", result.first + 1, result.second + 1); // Result is 1-based
}
