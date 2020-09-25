#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// http://codeforces.com/problemset/problem/37/A

/*
    towers (time complexity: O(n log n), space complexity: O(1))
        We can sort in O(n log n) complexity and then linearly 
        traverse the array to count the number of distinct towers
        and the maximum height, and then immediately print them.
*/
template<typename T> void towers(vector<T> A) {
    sort(A.begin(), A.end());

    int towers = 0, bar = 0, height = 0, maxHeight = 1;
    for(const auto& v : A) {
        if(v == bar) {
            height++;
            maxHeight = max(height, maxHeight);
        } else {
            bar = v; 
            height = 1; 
            towers++;
        }
    }    
    
    cout << maxHeight << " " << towers << endl;
}

int main() {
    int N;
    cin >> N;

    vector<int> A;
    A.reserve(N);
    for(int i = 0; i < N; i++) {
        int x;
        cin >> x;
        A.push_back(x);
    }

    towers(A);
}