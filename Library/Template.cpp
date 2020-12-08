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

istream& operator>>(istream& is, tuple<> &t) {
    return is;
}

template<typename T, typename... Ts> istream& operator>>(istream& is, tuple<T, Ts...>& t) {
    T t0; tuple<Ts...> ts;
    is >> t0 >> ts;
    t = tuple_cat(tuple<T>(t0), ts);
    return is;
}

template<typename T> istream& operator>>(istream& is, vector<T>& v) {
    for(size_t i = 0; i < v.size(); i++)
        is >> v[i];
    return is;
}

template<typename T> ostream& operator<<(ostream& os, vector<T>& v) {
    for(auto const& e : v)
        os << e << " ";
    os << endl;
    return os;
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

    vector<int64_t> A(N);
    vector<tuple<int64_t, int64_t>> A(N);
    vector<tuple<int64_t, int64_t, int64_t>> A(N);

    cin >> A;

    exercise<int64_t>(A);
    exercise<int64_t, int64_t>(A);
    exercise<int64_t, int64_t, int64_t>(A);

    auto result = exercise<int64_t>(A);
    auto result = exercise<int64_t, int64_t>(A);
    auto result = exercise<int64_t, int64_t, int64_t>(A);

    cout << result;

    for(auto const& r : result)
        cout << r << endl;
}
