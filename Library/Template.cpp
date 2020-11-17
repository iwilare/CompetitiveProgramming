#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

//

/*
     (time complexity: O(), space complexity: O())

*/

template<typename T> vector<tuple<T, size_t>> index(vector<T>& A) {
    vector<tuple<T, size_t>> indexed(A.size());
    for(size_t i = 0; i < A.size(); i++)
        indexed[i] = make_tuple(A[i], i);
    return indexed;
}

template<typename T> vector<size_t> remap(vector<T>& A) {
    vector<pair<T, size_t>> indexed(A.size());
    for(size_t i = 0; i < A.size(); i++)
        indexed[i] = make_pair(A[i], i);

    sort(indexed.begin(), indexed.end());

    vector<size_t> remapped(A.size());
    size_t remap = 0;
    for(size_t i = 0; i < indexed.size(); i++) {
        auto v = indexed[i].first;
        // Remap with equal rankings
        while(v == indexed[i].first)
            remapped[indexed[i++].second] = remap;
        remap++;
        i--;
    }

    return remapped;
}

template<typename T> vector<T> read_sequence(size_t n) {
    vector<T> input(n);
    for(size_t i = 0; i < n; i++)
        cin >> input[i];
    return input;
}

template<typename L, typename R> vector<tuple<L, R>> read_sequence2(size_t n) {
    vector<tuple<L, R>> input;
    input.reserve(n);
    for(size_t i = 0; i < n; i++) {
        L a; R b;
        cin >> a >> b;
        input.emplace_back(a, b);
    }
    return input;
}

template<typename A, typename B, typename C> vector<tuple<A, B, C>> read_sequence3(size_t n) {
    vector<tuple<A, B, C>> input;
    input.reserve(n);
    for(size_t i = 0; i < n; i++) {
        A a; B b; C c;
        cin >> a >> b >> c;
        input.emplace_back(a, b, c);
    }
    return input;
}

// template<typename T> vector<T> exercise(vector<T>& A, vector<tuple<size_t, size_t>>& Q) {
// }

int main() {
    size_t N;
    cin >> N;

    size_t T;
    cin >> T;

    for(size_t t = 0; t < T; t++) {
        size_t N;
        cin >> N;
    }

    auto A = read_sequence<int64_t>(N);
    auto A = read_sequence2<int64_t, int64_t>(N);
    auto A = read_sequence2<int64_t, int64_t, int64_t>(N);

    exercise<int64_t>(A);
    exercise<int64_t, int64_t>(A);
    exercise<int64_t, int64_t, int64_t>(A);

    auto result = exercise<int64_t>(A);
    auto result = exercise<int64_t, int64_t>(A);
    auto result = exercise<int64_t, int64_t, int64_t>(A);

    for(auto const& r : result)
        cout << r << " ";
    cout << endl;

    for(auto const& r : result)
        cout << r << endl;
}
