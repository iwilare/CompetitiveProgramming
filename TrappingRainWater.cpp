#include <iostream>

using namespace std;

int maxs(int N, int A[], int a, int b) {
    int m = a;
    for(int i=a+1; i<=b; i++)
        if(A[i] > A[m])
            m = i;
    return m;
}

int water(int N, int A[], int a, int b) {
    int sum = 0;
    int side = min(A[a], A[b]);
    for(int i=a+1; i<b; i++)
        sum += side - A[i];
    return sum;
}

int main() {
    int T;

    cin >> T;

    for(int t = 0; t < T; t++) {
        int N;
        cin >> N;

        int A[N];
        for(int i = 0; i < N; i++)
            cin >> A[i];

        int p = maxs(N, A, 0, N-1);

        int sum = 0;

        for(int i=1, mx=0; i<=p; i++) {
            if(A[i] >= A[mx]) {
                sum += water(N, A, mx, i);
                mx = i;
            }
        }

        for(int i=N-2, mx=N-1; i>=p; i--) {
            if(A[i] >= A[mx]) {
                sum += water(N, A, i, mx);
                mx = i;
            }
        }

        cout << sum << endl;
    }
}