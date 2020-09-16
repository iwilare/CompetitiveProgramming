#include <iostream>
#include <vector>

using namespace std;

// https://practice.geeksforgeeks.org/problems/missing-number-in-array/0

/*
    missing_number (time complexity: O(n), space complexity: O(1))
        Given an array with all the numbers 1..N except one, returns the
        missing number. Progressively calculates the expected sum of all
        numbers [1..N] while subtracting the input numbers. This version
        is more numerically stable than simply pre-calculating the
        entire sum, as it avoids overflowing the sum.
*/
int missing_number(vector<int> const& vec) {
    int sum = vec.size() + 1;
    int i = 1;
    for(const auto v : vec) {
        sum += i - v;
        i++;
    }
    return sum;
}

int main() {
    int T;
    cin >> T;

    for(int t = 0; t < T; t++) {
        int N;
        cin >> N;

        vector<int> A;
        A.reserve(N);
        for(int i = 0; i < N-1; i++) {
            int x;
            cin >> x;
            A.push_back(x);
        }

        cout << missing_number(A) << endl;
    }
}