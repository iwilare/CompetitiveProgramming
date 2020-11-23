#include <bits/stdc++.h>

using namespace std;

// https://www.spoj.com/problems/KNAPSACK/

/*
    knapsack (time complexity: O(n^2), space complexity: O(n^2))
        Uses a simple dynamic recursive top-down approach to
        memoize the knapsack results in a matrix, according to the
        knapsack remaining size and the remaining items to be
        considered.
*/

template<typename T> T knapsack(int64_t backpack, vector<tuple<int64_t, T>>& items) {
    vector<vector<T>> memo(backpack + 1, vector<T>(items.size() + 1, -1));

    function<T(int64_t,int64_t)> knapsack_ = [&](int64_t backpack, int64_t items_size) {
        if(memo[backpack][items_size] != -1)
            return memo[backpack][items_size];
        else {
            int return_;
            if(items_size == 0)
                return_ = 0;
            else {
                auto remaining = backpack - get<0>(items[items_size-1]);
                auto value = get<1>(items[items_size-1]);
                return_ = max(remaining < 0 ? 0
                             : knapsack_(remaining, items_size-1) + value,
                               knapsack_(backpack,  items_size-1));
            }
            return (memo[backpack][items_size] = return_);
        }
    };

    return knapsack_(backpack, items.size());
}

template<typename L, typename R> vector<tuple<L, R>> read_sequence2(int64_t n) {
    vector<tuple<L, R>> input;
    input.reserve(n);
    for(int64_t i = 0; i < n; i++) {
        L a; R b;
        cin >> a >> b;
        input.emplace_back(a, b);
    }
    return input;
}

int main() {
    int64_t S, N;
    cin >> S >> N;

    auto items = read_sequence2<int64_t, int64_t>(N);

    cout << knapsack<int64_t>(S, items) << endl;
}
