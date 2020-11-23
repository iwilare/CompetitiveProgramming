#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <set>

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <functional>
#include <cmath>

#include <vector>

template<typename T> class fenwick_tree {
    std::vector<T> tree;
public:
    fenwick_tree(size_t n) : tree(n + 1) {}

    T sum(size_t i) {
        T sum = 0;
        for(i++; i > 0; i -= i & -i)
            sum += tree[i];
        return sum;
    }

    T range(size_t i, size_t j) {
        return sum(j) - sum(i - 1);
    }

    void add(size_t i, T v) {
        for(i++; i < tree.size(); i += i & -i)
            tree[i] += v;
    }
};

using namespace std;

template<typename T> vector<tuple<T, size_t>> index(vector<T>& A) {
    vector<tuple<T, size_t>> indexed(A.size());
    for(size_t i = 0; i < A.size(); i++)
        indexed[i] = make_tuple(A[i], i);
    return indexed;
}

/*
    smaller_values (time complexity: O((m + n) log n), space complexity: O(n))
        Sort the array and the queries according to the X value.
        Then, progressively build a Fenwick tree: for each query,
        add 1 to all the positions which have a value smaller than
        the current X. When we go to the next query, add to the Fenwick tree
        all the elements while they are smaller than the query, and so on.
        Finally, reorder the answers according to the original order.
        Since we visit all the elements of the vector at most once, the
        time requirements are satisfied.
*/
template<typename T> vector<T> smaller_values(vector<T>& A, vector<tuple<T, T, T>>& Q) {
    auto Ais = index(A);
    sort(Ais.begin(), Ais.end()); // Sort by first of tuple (A[i])

    auto Qis = index(Q);
    sort(Qis.begin(), Qis.end()); // Sort by first of first of tuple (X)

    fenwick_tree<T> ft(A.size());
    vector<T> answers(Qis.size());

    size_t sa = 0;
    for(auto const& q : Qis) {
        auto query = get<0>(q);
        auto queryIndex = get<1>(q);
        for(; get<0>(Ais[sa]) <= get<0>(query); sa++)
            ft.add(get<1>(Ais[sa]), 1);
        answers[queryIndex] = ft.range(get<1>(query), get<2>(query));
    }

    return answers;
}

template<typename T> vector<T> read_sequence(size_t n) {
    vector<T> input(n);
    for(size_t i = 0; i < n; i++)
        cin >> input[i];
    return input;
}

template<typename L, typename R, typename B> vector<tuple<L, R, B>> read_sequence3(size_t n) {
    vector<tuple<L, R, B>> input;
    input.reserve(n);
    for(size_t i = 0; i < n; i++) {
        L a; R b; B c;
        cin >> a >> b >> c;
        input.emplace_back(c, a, b); // Put the value in front of easier sorting later
    }
    return input;
}

int main() {
    size_t N, K;
    cin >> N >> K;

    auto A = read_sequence<int64_t>(N);
    auto Q = read_sequence3<int64_t, int64_t, int64_t>(K);

    auto result = smaller_values<int64_t>(A, Q);

    for(auto const& r : result)
        cout << r << endl;
    cout << endl;
}
