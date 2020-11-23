#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <unordered_map>
#include <cmath>

using namespace std;

// https://codeforces.com/contest/375/problem/D

/*
    tree_and_queries (time complexity: O((n + q) sqrt n), space complexity: O(n))
        Uses a pre-order visit of the tree to transform queries on the tree
        into queries on a flattened representation of the tree, and then
        answers them using Mo's algorithm and a prefix sum vector to calculate the frequencies.
        The queries handled by Mo's algorithm are such that all the nodes in a subtree
        are contiguous segments in the whole array, which can be obtained by a trivial pre-order DFS.
        Then, all vertices are assigned their corresponding segments in the array,
        which are used to appropriately reword the subtree queries into segment queries.
        Fenwick trees are not necessary in this specific problem to count the number
        of colors that appear more than X times, since it is a special case where all
        continuous increments are just by +1 and -1 that can be solved with simple vectors.
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

vector<vector<size_t>> tree_sparse_matrix(vector<tuple<size_t, size_t>>& edges) {
    vector<vector<size_t>> tree(edges.size()+1);

    sort(edges.begin(), edges.end());

    for(auto const& e : edges)
        tree[get<0>(e)].push_back(get<1>(e));

    return tree;
}

template<typename T> tuple<vector<T>, vector<tuple<size_t, size_t>>> flatten(vector<vector<size_t>>& tree, vector<T>& colors) {
    vector<T> flattened;
    flattened.reserve(tree.size());
    vector<tuple<size_t, size_t>> vertex_intervals(tree.size());

    vector<bool> visited(tree.size(), false);

    function<void(size_t)> traverse = [&](size_t i) {
        size_t start = flattened.size();

        if(visited[i])
            return;

        visited[i] = true;

        flattened.push_back(colors[i]);
        for(auto const& next : tree[i])
            traverse(next);

        size_t end = flattened.size()-1; // End is included
        vertex_intervals[i] = make_tuple(start, end);
    };

    traverse(0);

    return make_tuple(flattened, vertex_intervals);
}

vector<size_t> tree_and_queries(vector<size_t>& unremapped_colors,
                                vector<tuple<size_t, size_t>>& edges,
                                vector<tuple<size_t, size_t>>& queries) {
    vector<size_t> colors = remap(unremapped_colors); // Apparently colors aren't remapped

    vector<vector<size_t>> sparse_tree = tree_sparse_matrix(edges);

    auto f = flatten(sparse_tree, colors);
    vector<size_t> tree                            = get<0>(f);
    vector<tuple<size_t, size_t>> vertex_intervals = get<1>(f);

    vector<size_t> color_frequencies(colors.size());
    vector<size_t> bigger_than_i(colors.size());

    bigger_than_i[0] = colors.size(); // All frequencies start from zero

    const auto Add = [&](size_t i) {
        // We don't remove the lower bigger_than_i count because if A >= B then A+1 >= B still holds
        // In a sense, the frequencies "leave a trail" along their ascents to higher counts.
        color_frequencies[tree[i]]++;
        bigger_than_i[color_frequencies[tree[i]]]++;
    };
    const auto Remove = [&](size_t i) {
        bigger_than_i[color_frequencies[tree[i]]]--;
        color_frequencies[tree[i]]--;
        // We don't need to increase the current bigger_than_i because it already has our trail
    };
    const auto Answer = [&](auto q) {
        return get<2>(q) >= colors.size() ? 0 : bigger_than_i[get<2>(q)];
    };

    vector<tuple<size_t, size_t, size_t>> tree_interval_queries;
    tree_interval_queries.reserve(queries.size());
    for(auto const& q : queries)
        tree_interval_queries.emplace_back(get<0>(vertex_intervals[get<0>(q)]),
                                           get<1>(vertex_intervals[get<0>(q)]),
                                           get<1>(q));

    return mo_algorithm<size_t, tuple<size_t, size_t, size_t>>(tree.size(), tree_interval_queries, Add, Remove, Answer);
}

template<typename T> vector<T> read_sequence(size_t n) {
    vector<T> input(n);
    for(size_t i = 0; i < n; i++)
        scanf("%zu", &input[i]); // Time limit exceeds on test 21 with cin/cout
    return input;
}

template<typename L, typename R> vector<tuple<L, R>> read_sequence_edges(size_t n) {
    vector<tuple<L, R>> input;
    input.reserve(n);
    for(size_t i = 0; i < n; i++) {
        L a; R b;
        scanf("%zu%zu", &a, &b);
        // Both indices start at 1, so subtract one.
        // Since they are undirected edges, add both of them to the tree
        // and later ensure that the BFS doesn't recurse back
        input.emplace_back(a-1, b-1);
        input.emplace_back(b-1, a-1);
    }
    return input;
}

template<typename L, typename R> vector<tuple<L, R>> read_sequence_queries(size_t n) {
    vector<tuple<L, R>> input;
    input.reserve(n);
    for(size_t i = 0; i < n; i++) {
        L a; R b;
        scanf("%zu%zu", &a, &b);
        input.emplace_back(a-1, b); // First: an index; second: a value
    }
    return input;
}

int main() {
    size_t N, M;
    cin >> N >> M;

    auto A = read_sequence<size_t>(N);
    auto E = read_sequence_edges<size_t, size_t>(N-1);
    auto Q = read_sequence_queries<size_t, size_t>(M);

    auto result = tree_and_queries(A, E, Q);

    for(auto const& r : result)
        printf("%zu\n", r);
}
