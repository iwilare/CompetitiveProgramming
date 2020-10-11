#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// https://codeforces.com/contest/616/problem/D?locale=en

/*
    longest_k_good_segment (time complexity: O(n log k), space complexity: O(k))
        Uses two ordered maps to bidirectionally associate values with the
        the last index encountered. When a new value out of the current K-window
        is found, the element with the minimum last index is removed. Otherwise,
        the index of the corresponding element is updated to the current position.
*/

pair<size_t, size_t> longest_k_good_segment(vector<int64_t> A, int64_t K) {
    map<int64_t, size_t> lastAppearance;
    map<size_t, int64_t> appearanceElem;

    size_t maxStart = 0, maxEnd = 0, maxLength = 0;
    size_t start = 0;
    for(size_t i = 0; i < A.size(); i++) {
        if(lastAppearance.size() == K && lastAppearance.find(A[i]) == lastAppearance.end()) {
            auto minLast = *appearanceElem.begin();
            start = minLast.first + 1;
            appearanceElem.erase(minLast.first);
            lastAppearance.erase(minLast.second);
        }

        if(lastAppearance.find(A[i]) != lastAppearance.end())
            appearanceElem.erase(lastAppearance[A[i]]);
        lastAppearance[A[i]] = i;
        appearanceElem[i] = A[i];

        if(i - start + 1 > maxLength) {
            maxStart = start;
            maxEnd = i;
            maxLength = i - start + 1;
        }
    }

    return make_pair(maxStart + 1, maxEnd + 1); // Result is 1-based
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

    auto result = longest_k_good_segment(fast_read_sequence<int64_t>(N), K);

    printf("%d %d\n", result.first, result.second);
}
