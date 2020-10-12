#include <iostream>
#include <vector>

using namespace std;

// https://codeforces.com/problemset/problem/313/B?locale=en

/*
    ilya_and_queries (time complexity: O(n), space complexity: O(n))
        Simply precomputes a vector indicating 1 iff S[i]==S[i+1]
        and then precomputes the prefix sum on this array to answer
        any query in O(1), by subtracting the sums at the two indices.
*/

void ilya_and_queries(string s, vector<pair<int64_t, int64_t>> queries) {
    vector<int64_t> sums(s.length());

    sums[0] = 0;
    for(size_t i = 1; i < s.length(); i++)
        sums[i] = sums[i-1] + (s[i-1] == s[i] ? 1 : 0);

    for(const auto& q : queries)
        cout << sums[q.second-1] - sums[q.first-1] << endl;
}

template<typename L, typename R> vector<pair<L, R>> read_sequence2(size_t n) {
    vector<pair<L, R>> input;
    input.reserve(n);
    for(size_t i = 0; i < n; i++) {
        L a; R b;
        cin >> a >> b;
        input.emplace_back(a, b);
    }
    return input;
}

int main() {
    string S;
    cin >> S;

    size_t M;
    cin >> M;

    auto queries = read_sequence2<int64_t, int64_t>(M);

    ilya_and_queries(S, queries);
}
