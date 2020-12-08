#include <bits/stdc++.h>

using namespace std;

// https://www.spoj.com/problems/PT07X/

/*
    vertex_cover (time complexity: O(n), space complexity: O(n))
        Uses a dynamic top-down recursive to memoize in a vector
        the maximum vertex cover size assignable to each node, for
        each node in the tree. Each memoization entry considers
        the case where the root is covered or not, with the
        minumum of the two cases for the root being used as final result.
        The recurrence relation is as follows: if the current node is
        not covered, all children must be covered. If the current node
        is covered, the children nodes can be either covered or not; the
        minimum of these two subcases is the solution of the subproblem.
        Each node is covered only once, so the complexity is essentially
        proportional to the sum of all the node degrees.
*/

istream& operator>>(istream& is, tuple<> &t) {
    return is;
}

template<typename T, typename... Ts> istream& operator>>(istream& is, tuple<T, Ts...>& t) {
    T t0; tuple<Ts...> ts;
    is >> t0 >> ts;
    t = tuple_cat(tuple<T>(t0), ts);
    return is;
}

template<typename T> istream& operator>>(istream& is, vector<T>& v) {
    for(size_t i = 0; i < v.size(); i++)
        is >> v[i];
    return is;
}

template<typename T> ostream& operator<<(ostream& os, vector<T>& v) {
    for(auto const& e : v)
        os << e << " ";
    os << endl;
    return os;
}

size_t vertex_cover(vector<tuple<size_t, size_t>>& edges) {
    vector<vector<size_t>> tree(edges.size() + 1);
    for(auto const& e : edges) { // Create links both ways
        tree[get<0>(e)-1].push_back(get<1>(e)-1); // Indices are 1-based
        tree[get<1>(e)-1].push_back(get<0>(e)-1); // Indices are 1-based
    }

    vector<vector<size_t>> memo(edges.size() + 1, vector<size_t>(2, 0));
    function<size_t(size_t, size_t, bool)> vertex_cover_node = [&](size_t parent, size_t i, bool s) -> size_t {
        if(memo[i][s] != 0) return memo[i][s];

        size_t cover = s ? 1 : 0;

        for(auto const& e : tree[i])
            if(e != parent) // Don't go back to the parent
                cover += s ? min(vertex_cover_node(i, e, true), vertex_cover_node(i, e, false))
                            :    vertex_cover_node(i, e, true); // The root is not covered, so all the children must be

        return memo[i][s] = cover;
    };

    return min(vertex_cover_node(-1, 0, true),
               vertex_cover_node(-1, 0, false)); // The root could be both cases
}

int main() {
    size_t N;
    cin >> N;
    vector<tuple<size_t, size_t>> A(N-1);
    cin >> A;
    cout << vertex_cover(A) << endl;
}
