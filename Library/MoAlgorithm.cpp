#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

template<typename T> vector<tuple<T, size_t>> index(vector<T>& A) {
    vector<tuple<T, size_t>> indexed(A.size());
    for(size_t i = 0; i < A.size(); i++)
        indexed[i] = make_tuple(A[i], i);
    return indexed;
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

/*
vector<size_t> exercise(vector<size_t>& A,
                        vector<tuple<size_t, size_t>>& Q) {
    const auto Add = [&](size_t i) {
        color_frequencies[tree[i]]++;
        bigger_than_i[color_frequencies[tree[i]]]++;
    };
    const auto Remove = [&](size_t i) {
        bigger_than_i[color_frequencies[tree[i]]]--;
        color_frequencies[tree[i]]--;
    };
    const auto Answer = [&](auto q) {
        return get<2>(q) >= colors.size() ? 0 : bigger_than_i[get<2>(q)];
    };

    return mo_algorithm<size_t, tuple<size_t, size_t>>(A.size(), Q, Add, Remove, Answer);
}
*/
