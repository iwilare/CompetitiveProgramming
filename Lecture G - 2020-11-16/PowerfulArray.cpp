#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <unordered_map>
#include <cmath>

using namespace std;

// http://codeforces.com/contest/86/problem/D

/*
    powerful_array (time complexity: O((n + q) sqrt n), space complexity: O(n))
        Use Mo's algorithm, as described in the lecture.
        Sort all the queries in sqrt(n) buckets, first by sorting the left ends in each
        bucket and then by sorting the right ends in increasing order in the bucket.
        Then, process each query "differentially": by considering only the difference in the
        endpoints inside the bucket, while maintaining the part of the query in the middle unchanged.
        This is done through the use of two functions Add and Remove which take care of adjusting the
        segment ends inside of the bucket.
*/

template<typename T> vector<tuple<T, size_t>> index(vector<T>& A) {
    vector<tuple<T, size_t>> indexed(A.size());
    for(size_t i = 0; i < A.size(); i++)
        indexed[i] = make_tuple(A[i], i);
    return indexed;
}

template<typename T> vector<size_t> remap(vector<T>& A) {
    auto indexed = index(A);

    sort(indexed.begin(), indexed.end());

    vector<size_t> remapped(A.size());
    for(size_t i = 0, remap = 0; i < indexed.size(); remap++) {
        auto v = get<0>(indexed[i]);
        while(i < indexed.size() && v == get<0>(indexed[i]))
            remapped[get<1>(indexed[i++])] = remap;
    }

    return remapped;
}

template<typename T, typename Q> vector<T> mo_algorithm(size_t vector_size,
                                                        vector<Q>& queries,
                                                        function<void(size_t)> const& Add,
                                                        function<void(size_t)> const& Remove,
                                                        function<T(Q)>         const& Answer) {
    size_t bucket = (size_t)sqrt(vector_size);

    auto Qi = index(queries);
    sort(Qi.begin(), Qi.end(), [&](auto ai, auto bi) {
        auto a = get<0>(ai), b = get<0>(bi);
        return make_pair(get<0>(a)/bucket, get<1>(a))
             < make_pair(get<0>(b)/bucket, get<1>(b));
    });

    size_t a = 0, b = 0;
    vector<T> answers(Qi.size());
    Add(0);
    for(auto const& qi : Qi) {
        auto q = get<0>(qi);
        while(a < get<0>(q))
            Remove(a++);
        while(a > get<0>(q))
            Add(--a);
        while(b < get<1>(q))
            Add(++b);
        while(b > get<1>(q))
            Remove(b--);
        answers[get<1>(qi)] = Answer(q);
    }
    return answers;
}

template<typename T> vector<T> powerful_array(vector<T>& A, vector<tuple<size_t, size_t>>& Q) {
    T answer{};

    // Using unordered_map for frequencies makes test #6 run out of time.
    // Using functions makes it reach 4336 ms / 4304 ms / 4430 ms, so it's a tight bound.
    auto A_remap = remap(A);
    vector<int64_t> frequencies(A_remap.size());
    frequencies.reserve(A.size());

    const auto Add = [&](size_t i) {
        // Undo previous contribution
        answer -= frequencies[A_remap[i]] * frequencies[A_remap[i]] * A[i];
        // Do current contribution
        frequencies[A_remap[i]]++;
        answer += frequencies[A_remap[i]] * frequencies[A_remap[i]] * A[i];
    };
    const auto Remove = [&](size_t i) {
        // Undo current contribution
        answer -= frequencies[A_remap[i]] * frequencies[A_remap[i]] * A[i];
        frequencies[A_remap[i]]--;
        // Redo previous contribution
        answer += frequencies[A_remap[i]] * frequencies[A_remap[i]] * A[i];
    };
    const auto Answer = [&](auto i) {
        return answer;
    };

    return mo_algorithm<T, tuple<size_t, size_t>>(A.size(), Q, Add, Remove, Answer);
}

template<typename T> vector<T> read_sequence(size_t n) {
    vector<T> input(n);
    for(size_t i = 0; i < n; i++)
        scanf("%I64d", &input[i]);
    return input;
}

template<typename L, typename R> vector<tuple<L, R>> read_sequence2(size_t n) {
    vector<tuple<L, R>> input;
    input.reserve(n);
    for(size_t i = 0; i < n; i++) {
        L a; R b;
        scanf("%I64u%I64u", &a, &b);
        input.emplace_back(a-1, b-1); // Queries start at one, apparently
    }
    return input;
}

int main() {
    size_t N, T;
    cin >> N >> T;

    auto A = read_sequence<int64_t>(N);
    auto Q = read_sequence2<size_t, size_t>(T);

    auto result = powerful_array<int64_t>(A, Q);

    for(auto const& r : result)
        printf("%I64d\n", r);
}
