#include <iostream>
#include <vector>
#include <set>

using namespace std;

// https://codeforces.com/contest/1398/problem/E?locale=en

/*
    two_types_of_spells (time complexity: O(n log n), space complexity: O(n))
        Use four sets to orderly store the spell type and the fact that the
        spell is currently being doubled.
        The maximum number of possible spells is clearly O(N) at most, and
        for each operation the cost is simply O(log N).
        Some preliminary remarks:
            - Lightning spells can also be subject to being doubled themselves.
              However, at least one lightning spell (the smallest) must be non-doubled,
              since it is the one that will start the doubling chain of lightning spells
              and can't be doubled by any previous one. We will refer to it as the
              "supporting" lightning spell, since it acts a foundation for the other spells.
            - If the supporting lightning spell is removed, a new lightning spell
              needs to take its place if there are still spells being doubled.
              As long as there are other non-doubling spells and no other smaller spell exists,
              nothing needs to be done. However, if the support spell is removed and all the
              remaining lightning spells are being doubled, the smallest one of these needs to
              be removed from the doubling set in order to replace it. This also implies that
              with this approach a simpler division "doubled/nondoubled" is unfeasible, since
              it is necessary to obtain the smallest doubled lightning spell.
            - The supporting lightning spell cannot be removed from its position in order to
              double it even if it is the biggest one of the non-doubled, if no replacements
              are available.
        The algorithm works in the following way:
            1. The incoming operation is first performed on the set, by either
               eliminating or adding the spell indicated. At each step, the total output
               is incremented (or decremented) and kept track of according to the moves performed.
            2. Then, the four sets are "rebalanced" with the following three operations:
                a. correct_unsupported_lights:
                    If the supporting lightning spell has been removed in the initial step,
                    replace it with a new smaller one, taken from the doubled lightning spells.
                b. correct_double_count:
                    Correct the number of doubled spells, compared with the total number of
                    lightning spells available. This can either be a reduction, where excess spells are
                    removed from the doubling set, or an addition to the doubled spells.
                        b1. Reduction is trivial and nothing special needs to be done.
                        b2. Addition is accomplished by selecting the biggest spell of either nondoubled set.
                            - A special case ensues when the biggest spell is the supporting lightning spell.
                              In this case, we can still try to double the biggest fire one (if there is one).
                c. correct_double_maxima:
                    Ensure that no swapping of equivalent spells that would increase the output can
                    be performed between the doubled and nondoubled spells, and if so, perform it.
                    Since all transfers move at most one spell, O(1) corrections are sufficient.
                    In practice, this is simply done by checking that the greater nondoubled spell is smaller
                    than the smallest doubled spell, and swapping accordingly.
                        - In the case where both spells are lightning, nothing special happens because the
                          (possibly) support lightning spell will be exchanged with another lightning one.
                        - Special attention is required when the maximum nondoubled lightning spell is the
                          support one. In this case, no swapping can be performed.
*/

void realign(set<int64_t>& fire, set<int64_t>& light, set<int64_t>& fireD, set<int64_t>& lightD, uint64_t& output) {
    // Transfer elements from sets while updating the output
    auto transfer = [&output](set<int64_t>& a, int64_t v, set<int64_t>& b, bool increase) {
        a.erase(v), b.insert(v);
        output += increase ? v : -v;
    };
    auto lightnings = [&light, &lightD]()  { return light.size() + lightD.size(); };
    auto doubled    = [&fireD, &lightD]()  { return fireD.size() + lightD.size(); };
    // Can the supporting lightning spell can be replaced with another one in the undoubled set?
    auto can_move_lights = [&light, &doubled]() { return light.size() >= 2; };
    auto correct_unsupported_lights = [&light, &lightD, &doubled, &transfer]() {
        // If there are elements being doubled but no support lightning spell,
        if(doubled() >= 1 && light.size() == 0 && lightD.size() > 0)
            // take the smallest from the doubled ones
            transfer(lightD, *lightD.begin(), light, false);
    };
    auto correct_double_count = [&fire, &light, &fireD, &lightD, &can_move_lights, &transfer, &doubled, &lightnings]() {
        // We can add spells to be doubled
        if(doubled() < lightnings()) {
            // If the greatest lightning spell can be moved and is greater than the fire one, double it
            if(light.size() > 0 && can_move_lights() && (fire.size() == 0 || *light.rbegin() > *fire.rbegin()))
                transfer(light, *light.rbegin(), lightD, true);
            else if(fire.size() > 0)
                // If there are elements, double the fire one
                transfer(fire, *fire.rbegin(), fireD, true);
            else
                ; // Either no elements to add or the lightning one can't be moved
        } else if(doubled() > lightnings()) {
            // Simply remove the smallest doubled spell
            if(lightD.size() > 0 && (fireD.size() == 0 || *lightD.begin() < *fireD.begin()))
                transfer(lightD, *lightD.begin(), light, false);
            else
                transfer(fireD, *fireD.begin(), fire, false);
        }
    };
    auto correct_double_maxima = [&fire, &light, &fireD, &lightD, &can_move_lights, &transfer]() {
        // If there are enough elements for a swap,
        if(fire.size() + light.size() > 0 && fireD.size() + lightD.size() > 0) {
            // Check that we can swap a fire spell
            if(fire.size() > 0)
                // Swap it with the maximum fire one if necessary
                if(fireD.size() > 0 && *fire.rbegin() > *fireD.begin()) {
                    transfer(fire, *fire.rbegin(), fireD, true);
                    transfer(fireD, *fireD.begin(), fire, false);
                } else if(lightD.size() > 0 && *fire.rbegin() > *lightD.begin()) {
                    transfer(fire, *fire.rbegin(), fireD, true);
                    transfer(lightD, *lightD.begin(), light, false);
                } else
                    ; // There were either no spells in the doubled set or no doubled spells that could be swapped
            // Similar as before: check that we can swap a light spell
            if(light.size() > 0)
                if(lightD.size() > 0 && *light.rbegin() > *lightD.begin()) {
                    transfer(light, *light.rbegin(), lightD, true);
                    transfer(lightD, *lightD.begin(), light, false);
                } else // If the target spell is a fire one and we can move the lights available
                       if(fireD.size() > 0 && can_move_lights() && *light.rbegin() > *fireD.begin()) {
                    transfer(light, *light.rbegin(), lightD, true);
                    transfer(fireD, *fireD.begin(), fire, false);
                } else
                    ;
        }
    };

    correct_unsupported_lights();
    correct_double_maxima(); // The lightning maxima could have been moved, perform a minor correction

    correct_double_count();
    correct_double_maxima(); // Perform the main maxima correction operation
}

void two_types_of_spells(vector<pair<int64_t, bool>> changes) {
    set<int64_t> fire, light, fireD, lightD;

    uint64_t output = 0;

    for(auto c : changes) {
        auto value = c.first;
        auto is_lightning = c.second;
        if(value < 0) {
            value = -value;
            if(fireD.find(value) != fireD.end() || lightD.find(value) != lightD.end() ) {
                output -= 2*value;
                (is_lightning ? lightD : fireD).erase(value);
            } else {
                output -= value;
                (is_lightning ? light : fire).erase(value);
            }
        } else {
            output += value;
            (is_lightning ? light : fire).insert(value);
        }

        // Perform the set correction
        realign(fire, light, fireD, lightD, output);

        cout << output << endl;
    }
}

template<typename L, typename R> vector<pair<L, R>> read_sequence2(size_t n) {
    vector<pair<L, R>> input;
    input.reserve(n);
    for(size_t i = 0; i < n; i++) {
        R a; L b;
        cin >> a >> b;
        input.emplace_back(b, a);
    }
    return input;
}

int main() {
    size_t N;
    cin >> N;

    two_types_of_spells(read_sequence2<int64_t, bool>(N));
}
