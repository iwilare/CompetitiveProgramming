#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <set>

using namespace std;

//

/*
     (time complexity: O(), space complexity: O())

*/

template<typename T> void sort(vector<T> &A) {
    sort(A.begin(), A.end());
}

template<typename T> vector<tuple<T, size_t>> index(vector<T>& A) {
    vector<tuple<T, size_t>> indexed(A.size());
    for(size_t i = 0; i < A.size(); i++)
        indexed[i] = make_tuple(A[i], i);
    return indexed;
}

vector<int64_t> remap_different_ranking(vector<int64_t> A) {
    vector<pair<int64_t, size_t>> indexed(A.size());
    for(size_t i = 0; i < A.size(); i++)
        indexed[i] = make_pair(A[i], i);

    sort(indexed.begin(), indexed.end());

    vector<int64_t> remapped(A.size());
    for(size_t i = 0; i < indexed.size(); i++)
        remapped[indexed[i].second] = i + 1;

    return remapped;
}

vector<int64_t> remap(vector<int64_t> A) {
    vector<pair<int64_t, size_t>> indexed(A.size());
    for(size_t i = 0; i < A.size(); i++)
        indexed[i] = make_pair(A[i], i);

    sort(indexed.begin(), indexed.end());

    vector<int64_t> remapped(A.size());
    int64_t index = 0;
    for(size_t i = 0; i < indexed.size(); i++) {
        auto v = indexed[i].first;
        while(v == indexed[i].first) // Remap with equal rankings
            remapped[indexed[i++].second] = index;
        index++;
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
        R a; L b;
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

    auto result = exercise<int64_t>(A);
    auto result = exercise<int64_t, int64_t>(A);
    auto result = exercise<int64_t, int64_t, int64_t>(A);

    for(auto const& r : result)
        cout << r << " ";
    cout << endl;

    exercise<int64_t>(A);
    exercise<int64_t, int64_t>(A);
    exercise<int64_t, int64_t, int64_t>(A);
}
