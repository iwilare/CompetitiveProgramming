#include <bits/stdc++.h>

using namespace std;

// https://www.spoj.com/problems/KNAPSACK/

/*
    knapsack (time complexity: O(backpack * |items|), space complexity: O(backpack * |items|))
        Uses a simple dynamic bottom-up approach to memoize
        the sub-knapsack results in a matrix, according to the
        knapsack remaining size and the remaining items to be
        considered.
*/

template<typename T> T knapsack(int64_t backpack, vector<tuple<int64_t, T>>& items) {
    T m[backpack + 1][items.size() + 1];

    for(int64_t b = 0; b <= backpack; b++)
        for(int64_t i = 0; i <= items.size(); i++)
            m[b][i] = b == 0 || i == 0 ? 0
                    : max(m[b][i-1],   b - get<0>(items[i-1]) < 0 ? 0
                                   : m[b - get<0>(items[i-1])][i-1] + get<1>(items[i-1]));

    return m[backpack][items.size()];
}

template<typename L, typename R> vector<tuple<L, R>> read_sequence2(int64_t n) {
    vector<tuple<L, R>> input(n);
    for(size_t i = 0; i < n; i++)
        cin >> get<0>(input[i]) >> get<1>(input[i]);
    return input;
}

int main() {
    int64_t S, N;
    cin >> S >> N;

    auto items = read_sequence2<int64_t, int64_t>(N);

    cout << knapsack<int64_t>(S, items) << endl;
}
