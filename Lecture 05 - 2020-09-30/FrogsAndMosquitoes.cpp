#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// https://codeforces.com/contest/609/problem/F?locale=en

/*
    frogs_and_mosquitoes (time complexity: O((n + m) log n), space complexity: O(n + m))
        Uses a BST a sweeping line algorithm approach and a pre-processing phase
        to eliminate all frog sovrapposition, in O(n log n). Then, the fall of
        mosquitoes is simulated. The closest frog collects all possible mosquitoes,
        and after its tongue gets expanded, the invariant of the frogs being all
        non-overlapping is restored in amortized O(log n) time. The complexity described
        is essentially achieved thanks to the fact that as frogs get bigger they also
        remove other frogs in the space. For each round of non-overlapping restoring,
        the following global cases can happen:
            - no frogs are modified       (O(  log n) complexity)
            - k frogs have to be modified (O(k log n) complexity)
        In the last case, it is easy to see that (using the assumption that all frogs are
        non-overlapping) all frogs encountered except one are removed from the board,
        thus ensuring that the overall amortized cost does not exceed O(n log n).
*/

class frog {
    int64_t _a;
    int64_t _b;
    int64_t _tongue;
    int64_t _mosquitoes_eaten;
public:
    frog(int64_t a, int64_t tongue)
        : _a(a), _b(a + tongue), _tongue(tongue), _mosquitoes_eaten(0) {}
    frog() {}
    int64_t a()                const { return _a;                }
    int64_t b()                const { return _b;                }
    int64_t tongue()           const { return _tongue;           }
    int64_t mosquitoes_eaten() const { return _mosquitoes_eaten; }
    void eat(int64_t v) { _tongue += v; _b += v; _mosquitoes_eaten++; }
};

void frogs_and_mosquitoes(vector<pair<int64_t, int64_t>> const& input_frogs, vector<pair<int64_t, int64_t>> const& mosquitoes) {
    vector<frog> frogs;
    frogs.reserve(input_frogs.size());

    // Initialize global frog data
    for(auto const& frog : input_frogs)
        frogs.emplace_back(frog.first, frog.second);

    map<int64_t, frog*> pond;

    // Insert the frogs inside the pond while removing all any-tier overlapping
    vector<frog*> sorted_frogs(frogs.size());
    transform(frogs.begin(), frogs.end(), sorted_frogs.begin(), [](auto& x) { return &x; });
    sort(sorted_frogs.begin(), sorted_frogs.end(), [](auto& x, auto& y) { return x->a() < y->a(); });
    int64_t rightmost_tongue = -1;
    for(auto& frog : sorted_frogs)
        // Insert this frog only if it's not contained in the previous one
        if(frog->b() > rightmost_tongue) {
            // If the frog is disjoint from the end of the previous one, use its position;
            // otherwise, adjust it to be immediately next to the end of the previous to maintain disjointness
            pond.insert({max(rightmost_tongue + 1, frog->a()), frog});
            rightmost_tongue = frog->b();
        }

    // Utility function that realigns the current frog so that there are no
    // one-tier overlaps after it, then advances the iterator to the next useful frog
    auto adjust_overlapping_frog = [&](map<int64_t, frog*>::iterator it) {
        if(it == pond.end())
            return;
        auto rightmost_tongue = it->second->b();
        // Start checking the next frog, and continue while there is any overlap
        for(++it; it != pond.end() && it->first <= rightmost_tongue;) {
            auto frog = it->second;
            // The frog is going to be repositioned or removed either way
            it = pond.erase(it);
            // If the frog is completely contained in the ones being considered,
            if(frog->b() > rightmost_tongue) {
                // There is a partial overlap: reposition it at the end of the last tongue checked.
                // The frog by itself only keeps the b() right endpoint, which must not move for
                // this operation. The one kept in the map is the true left starting position.
                pond.insert({rightmost_tongue + 1, frog});
                rightmost_tongue = frog->b();
                // Since we are dealing with one-tier overlaps, the partially overlapping
                // segment is also the last one, so we can already quit
            }
        }
    };

    multimap<int64_t, int64_t> landed_mosquitoes;

    for(auto const& m : mosquitoes) {
        // Find the current candidate frog (the earliest frog before the placed mosquito)
        // This requires the frogs to be non-overlapping to work
        auto frog_it     = --pond.upper_bound(get<0>(m));
        auto mosquito_it = landed_mosquitoes.insert(m);
        // Increase the current candidate frog as much as possible
        while(frog_it != pond.end() // This can happen if the mosquito is before all frogs
           && mosquito_it != landed_mosquitoes.end()
           && frog_it->first <= mosquito_it->first && mosquito_it->first <= frog_it->second->b()) {
            frog_it->second->eat(mosquito_it->second);
            mosquito_it = landed_mosquitoes.erase(mosquito_it);
        }
        adjust_overlapping_frog(frog_it);
    }

    for(auto const& frog : frogs)
        cout << frog.mosquitoes_eaten() << " " << frog.tongue() << endl;
}

template<typename L, typename R> vector<pair<L, R>> read_sequence2(size_t n) {
    vector<pair<L, R>> input;
    input.reserve(n);
    for(size_t i = 0; i < n; i++) {
        L a; R b;
        cin >> a >> b;
        input.emplace_back(a, b);
    }
    return input;
}

int main() {
    size_t N, M;
    cin >> N >> M;

    auto frogs      = read_sequence2<int64_t, int64_t>(N);
    auto mosquitoes = read_sequence2<int64_t, int64_t>(M);

    frogs_and_mosquitoes(frogs, mosquitoes);
}
