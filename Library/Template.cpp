#include <bits/stdc++.h>

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
    auto indexed = index(A);

    sort(indexed.begin(), indexed.end());

    vector<size_t> remapped(A.size());
    for(size_t i = 0, remap = 0; i < indexed.size(); remap++) {
        auto v = get<0>(indexed[i]);
        while(i < indexed.size() && v == get<0>(indexed[i]))
            remapped[get<1>(indexed[i++])] = remap;
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
    vector<tuple<L, R>> input(n);
    for(size_t i = 0; i < n; i++)
        cin >> get<0>(input[i]) >> get<1>(input[i]);
    return input;
}

template<typename A, typename B, typename C> vector<tuple<A, B, C>> read_sequence3(size_t n) {
    vector<tuple<A, B, C>> input(n);
    for(size_t i = 0; i < n; i++)
        cin >> get<0>(input[i]) >> get<1>(input[i]) >> get<2>(input[i]);
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
    auto A = read_sequence3<int64_t, int64_t, int64_t>(N);

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
