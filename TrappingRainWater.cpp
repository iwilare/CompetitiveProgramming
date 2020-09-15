#include <iostream>

using namespace std;

int maximum(int N, int A[], int a, int b) {
    int m = a;
    for(int i = a + 1; i <= b; i++)
        if(A[i] > A[m])
            m = i;
    return m;
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

        int p = maximum(N, A, 0, N-1);

        int sum = 0;

        for(int i = 1, m = 0; i <= p; i++) {
            if(A[i] >= A[m])
                m = i;
            sum += A[m] - A[i];
        }

        for(int i = N-2, m = N-1; i >= p; i--) {
            if(A[i] >= A[m])
                m = i;
            sum += A[m] - A[i];
        }

        cout << sum << endl;
    }
}