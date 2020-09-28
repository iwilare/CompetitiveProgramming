#include <iostream>
#include <vector>

using namespace std;

template<typename T> size_t merge(vector<T>& A, size_t low, size_t mid, size_t high) {
    vector<T> temp(high - low);

    size_t inversions = 0;
    size_t i = low, j = mid, k = 0;

    while(i < mid && j < high)
        if(A[i] < A[j]) {
            temp[k++] = A[i++];
        } else {
            temp[k++] = A[j++];
            inversions += mid - i;
        }

    while(i < mid)
        temp[k++] = A[i++];

    while(j < high)
        temp[k++] = A[j++];

    copy(temp.begin(), temp.end(), A.begin() + low);

    return inversions;
}

template<typename T> size_t merge_sort(vector<T>& A, size_t low, size_t high) {
    size_t count = 0;
    if(high - low > 1) {
        size_t mid = low + (high - low)/2;
        count += merge_sort(A, low, mid);
        count += merge_sort(A, mid, high);
        count += merge(A, low, mid, high);
    }
    return count;
}

template<typename T> size_t inversion_count(vector<T>& A) {
    return merge_sort(A, 0, A.size());
}

template<typename T> vector<T> read_sequence(size_t n) {
    vector<T> input(n);
    for(size_t i = 0; i < n; i++)
        cin >> input[i];
    return input;
}

int main() {
    size_t T;
    cin >> T;

    for(int t = 0; t < T; t++) {
        size_t N;
        cin >> N;

        auto input = read_sequence<int64_t>(N);

        cout << inversion_count(input) << endl;
    }
}