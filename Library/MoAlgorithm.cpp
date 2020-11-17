#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

template<typename T> vector<T> mo_algorithm(vector<tuple<size_t, size_t>>& Q,
                                            function<void(int64_t)> const& Add,
                                            function<void(int64_t)> const& Remove,
                                            function<T()>           const& Answer) {
    size_t bucket = (size_t)sqrt(Q.size());

    auto Qi = index(Q);
    sort(Qi.begin(), Qi.end(), [&](auto ai, auto bi) {
        auto a = get<0>(ai), b = get<0>(bi);
        return get<0>(a)/bucket != get<0>(b)/bucket
             ? get<0>(a)/bucket <  get<0>(b)/bucket
             : get<1>(a) < get<1>(b);
    });

    int64_t a = 0, b = 0;
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
        answers[get<1>(qi)] = Answer();
    }
    return answers;
}

template<typename T> vector<T> exercise(vector<T>& A, vector<tuple<size_t, size_t>>& Q) {
    T answer{};

    auto A_remap = remap(A);
    vector<int64_t> frequencies(A_remap.size());
    frequencies.reserve(A.size());

    const auto Add = [&](int64_t i) {
        // Undo previous contribution
        answer -= frequencies[A_remap[i]] * frequencies[A_remap[i]] * A[i];
        // Do current contribution
        frequencies[A_remap[i]]++;
        answer += frequencies[A_remap[i]] * frequencies[A_remap[i]] * A[i];
    };
    const auto Remove = [&](int64_t i) {
        // Undo current contribution
        answer -= frequencies[A_remap[i]] * frequencies[A_remap[i]] * A[i];
        frequencies[A_remap[i]]--;
        // Redo previous contribution
        answer += frequencies[A_remap[i]] * frequencies[A_remap[i]] * A[i];
    };
    const auto Answer = [&]() {
        return answer;
    };

    return mo_algorithm<T>(Q, Add, Remove, Answer);
}
