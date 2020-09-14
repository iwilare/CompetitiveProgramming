#include <iostream>

using namespace std;

int maxs(int N, int A[], int a, int b) {
    int m = a;
    for(int i=a+1; i<=b; i++)
        if(A[i] > A[m])
            m = i;
    return m;
}

int calculate(int N, int A[], int a, int b) {
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

        int mi[N];

        int p = maxs(N, A, 0, N-1);

        mi[0] = 0;
        for(int i=1; i<p; i++)
            mi[i] = A[i] >= A[mi[i-1]] ? i : mi[i-1];

        mi[N-1] = N-1;
        for(int i=N-2; i>p; i--)
            mi[i] = A[i] >= A[mi[i+1]] ? i : mi[i+1];

        int sum = 0;

        for(int i = p; i > 1; i = mi[i-1])
            sum += calculate(N, A, mi[i-1], i);

        for(int i = p; i < N-1; i = mi[i+1])
            sum += calculate(N, A, i, mi[i+1]);

        cout << sum << endl;
    }
}