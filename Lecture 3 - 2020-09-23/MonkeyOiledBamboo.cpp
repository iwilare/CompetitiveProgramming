#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=3183

/*
    monkey_oiled_bamboo (time complexity: O(n), space complexity: O(1))
        First, linearly scan the array to find the maximum difference, which
        is clearly a lower bound for the minimum. Then, start simulating the
        ascent. When the maximum is encountered, decrease the amount of strength,
        and continue until either you get to the end or a bigger gap is found.
        If a bigger gap is found, it is sufficient to increase the maximum strength
        by one in order to compensate for it (since it already started from the maximum,
        and therefore there cannot be other bigger gaps)
*/
int monkey_oiled_bamboo(vector<int> const& A) {
    int max_diff = INT_MIN;
    for(int i = 0; i < A.size(); i++) {
        auto diff = A[i] - (i == 0 ? 0 : A[i-1]);
        if(diff > max_diff)
            max_diff = diff;
    }

    int necessary = max_diff;
    for(int i = 0; i < A.size(); i++) {
        auto diff = A[i] - (i == 0 ? 0 : A[i-1]);
        if(diff == max_diff)
            max_diff--;
        else if(diff > max_diff)
            return necessary + 1;
    }
    return necessary;
}

int main() {
    int T;
    cin >> T;

    for(int t = 0; t < T; t++) {
        int N;
        cin >> N;

        vector<int> A;
        A.reserve(N);
        for(int i = 0; i < N; i++) {
            int x;
            cin >> x;
            A.push_back(x);
        }

        cout << "Case " << t + 1 << ": " << monkey_oiled_bamboo(A) << endl;
    }
}