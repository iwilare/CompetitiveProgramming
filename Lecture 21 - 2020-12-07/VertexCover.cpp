#include <bits/stdc++.h>

using namespace std;

// https://www.spoj.com/problems/PT07X/

/*
    vertex_cover (time complexity: O(n), space complexity: O(n))
        Uses a dynamic top-down recursive approach to memoize in a vector
        the maximum vertex cover size assignable to each node, for
        each node in the tree. Each memoization entry considers
        the case where the root is covered or not, with the
        minumum of the two cases for the root being used as final result.
        The recurrence relation is as follows: if the current node is
        not covered, all children must be covered. If the current node
        is covered, the children nodes can be either covered or not; the
        minimum of these two subcases is the solution of the subproblem.
        Each node is covered only once, so the complexity is essentially
        proportional to the sum of all the node degrees, i.e.: the number of nodes.
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

    // i is the index of the node being considered, s iff we choose to cover it.
    function<size_t(size_t, size_t, bool)> vertex_cover_node = [&](size_t parent, size_t i, bool s) -> size_t {
        if(memo[i][s] != 0) return memo[i][s];

		// The total number of covered nodes of the current
		// solution starts from counting the parent.
        size_t cover = s ? 1 : 0;

        for(auto const& e : tree[i])
            // Ensure we are not going back to the parent.
            if(e != parent)
                // If the root is covered, the children can be both covered or not;
                // pick the best option of the two.
                cover += s ? min(vertex_cover_node(i, e, true), vertex_cover_node(i, e, false))
                           :     vertex_cover_node(i, e, true);
                           // But if the root is not covered, all the children must be forcefully covered.

        return memo[i][s] = cover;
    };

    // The root could be both cases, so check them both.
    return min(vertex_cover_node(-1, 0, true),
               vertex_cover_node(-1, 0, false));
}

int main() {
    size_t N;
    cin >> N;
    vector<tuple<size_t, size_t>> A(N-1);
    cin >> A;
    cout << vertex_cover(A) << endl;
}
