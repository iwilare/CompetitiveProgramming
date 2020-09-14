#include <iostream>

using namespace std;

int sweep(int N, int A[], int a, int b) {
    if(b - a <= 1)
        return 0;
    else {
        int m1 = -1, m2 = -1;

        for(int i=a; i<=b; i++) {
            if(m1 == -1 || A[i] > A[m1]) {
                m2 = m1;
                m1 = i;
            } else if(m2 == -1 || A[i] > A[m2]) {
                m2 = i;
            }
        }

        int sum = 0;
        int side = min(A[m1], A[m2]);

        int first = min(m1,m2);
        int second = max(m1,m2);

        for(int i=first+1; i<second; i++)
            sum += side - A[i];

        return sum
             + sweep(N, A, a, first)
             + sweep(N, A, second, b);
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

        cout << sweep(N, A, 0, N-1) << endl;
    }
}