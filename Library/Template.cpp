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

vector<int64_t> remap(vector<int64_t> A) {
    vector<pair<int64_t, size_t>> indexed(A.size());
    for(size_t i = 0; i < A.size(); i++)
        indexed[i] = make_pair(A[i], i);

    sort(indexed.begin(), indexed.end());

    vector<int64_t> remapped(A.size());
    for(size_t i = 0; i < indexed.size(); i++)
        remapped[indexed[i].second] = i + 1;

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
        input.emplace_back(b, a);
    }
    return input;
}

int main() {
    size_t T;
    cin >> T;

    for(size_t t = 0; t < T; t++) {
        size_t N;
        cin >> N;
    }

    size_t N;
    cin >> N;

    auto A = read_sequence<int64_t>(N);
    auto A = read_sequence2<int64_t, int64_t>(N);

    auto result = exercise<int64_t, int64_t>(A);

    for(auto const& r : result)
        cout << r << " ";
    cout << endl;

    cout << exercise(A) << endl;
}
