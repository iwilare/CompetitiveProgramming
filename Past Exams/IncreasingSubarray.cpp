#include <bits/stdc++.h>

using namespace std;

// increasing_subarray (time complexity: O(n), space complexity: O(n))

int64_t increasing_subarray(vector<int64_t> const& A) {
    vector<int64_t> L(A.size());
    vector<int64_t> R(A.size());

    for(int64_t i = 0; i < A.size(); i++)
        L[i] = i-1 >= 0 && A[i-1] < A[i] ? L[i-1] + 1 : 1;

    for(int64_t i = A.size()-1; i >= 0; i--)
        R[i] = i+1 < A.size() && A[i] < A[i+1] ? R[i+1] + 1 : 1;

    int64_t m = 0;
    for(int64_t i = 0; i < A.size(); i++)
        m = max({m,
                 L[i] + 1,
                 R[i] + 1,
                 0 <= i-1 && i+1 < A.size() && A[i-1] + 1 < A[i+1]
                    ? L[i-1] + R[i+1] + 1 : 0});

    return m;
}

template<typename T> istream& operator>>(istream& is, vector<T>& v) {
    for(size_t i = 0; i < v.size(); i++)
        is >> v[i];
    return is;
}

int main() {
    size_t N;
    cin >> N;

    vector<int64_t> A(N);
    cin >> A;

    cout << increasing_subarray(A) << endl;
}
