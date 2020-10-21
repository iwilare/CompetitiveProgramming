#include <vector>
#include <iostream>

#include "InversionCount.hpp"

using namespace std;

template<typename T> vector<T> read_sequence(size_t n) {
    vector<T> input(n);
    for(size_t i = 0; i < n; i++)
        cin >> input[i];
    return input;
}

int main() {
    size_t T;
    cin >> T;

    for(size_t t = 0; t < T; t++) {
        size_t N;
        cin >> N;

        auto input = read_sequence<int64_t>(N);

        cout << inversion_count(input) << endl;
    }
}
