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

int sweepLeft(int N, int A[], int right) {
    if(right <= 1)
        return 0;
    else {
        int m = maxs(N, A, 0, right-1);
        return sweepLeft(N, A, m)
             + calculate(N, A, m, right);
    }
}

int sweepRight(int N, int A[], int left) {
    if(left >= N-2)
        return 0;
    else {
        int m = maxs(N, A, left+1, N-1);
        return sweepRight(N, A, m)
             + calculate(N, A, left, m);
    }
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

        int m = maxs(N, A, 0, N-1);
        cout << sweepLeft(N, A, m) + sweepRight(N, A, m) << endl;
    }
}