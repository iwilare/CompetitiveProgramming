#include <bits/stdc++.h>

using namespace std;

// https://codeforces.com/contest/596/problem/B

/*
    wilbur_and_array (time complexity: O(n), space complexity: O(1))
        Use a greedy approach that simply progressvely
        adjusts prefixes of the target array up to the end.
        This approach exploits the property that all operations
        only operate on suffixes of the array; so no operation will be
        able to adjust the elements before it, thus the need to start
        adjusting the beginning of the array. The algorithm here simply
        scans the array linearly while keeping track of the cumulative
        value (delta) of the operations so far performed, and the total
        number of such operations.
*/

int64_t wilbur_and_array(vector<int64_t>& A) {
    int64_t operations = 0;
    int64_t delta = 0; // Keep track of the value of all elements after this point
    for(auto const& v : A) {
        operations += abs(v - delta); // Both kinds of operations count
        delta += v - delta;           // Move delta to v
    }
    return operations;
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

int main() {
    size_t N;
    cin >> N;
    vector<int64_t> A(N);
    cin >> A;
    cout << wilbur_and_array(A) << endl;
}
