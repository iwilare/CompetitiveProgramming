#include <bits/stdc++.h>

using namespace std;

/*
    segments (time complexity: O((n + m) log n), space complexity: O(n))
*/

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

void segments(vector<tuple<int64_t, int64_t>> A, vector<tuple<int64_t, int64_t, int64_t>> Q) {
    vector<int64_t> v(A.size());
    for(int i=0; i<A.size(); i++) {
        v[get<0>(A[i])] += 1;
        if(get<1>(A[i]) + 1 < A.size())
            v[get<1>(A[i]) + 1] -= 1;
    }

    vector<int64_t> s(A.size());
    partial_sum(v.begin(), v.end(), s.begin());

    unordered_map<int64_t, set<int64_t>> results;

    for(int i=0; i<A.size(); i++)
        results[s[i]].insert(i);

    for(int i=0; i<Q.size(); i++) {
        auto q = Q[i];
        auto r = results[get<2>(q)];
        auto lb = r.lower_bound(get<0>(q));
        cout << (lb != r.end() && get<0>(q) <= *lb && *lb <= get<1>(q) ? 1 : 0) << endl;
    }
}

int main() {
    size_t N, M;
    cin >> N >> M;

    vector<tuple<int64_t, int64_t>> A(N);
    vector<tuple<int64_t, int64_t, int64_t>> Q(M);

    cin >> A;
    cin >> Q;

    segments(A, Q);
}
