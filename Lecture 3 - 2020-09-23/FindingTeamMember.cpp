#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// https://codeforces.com/problemset/problem/579/B

/*
    finding_team_member (time complexity: O(n log n), space complexity: O(n))
        We can sort in O(n log n) complexity all the possible couples
        according to their strength; then, we form teams starting from 
        the highest strength to the lowest, disregarding couples where
        one of the team members has already been chosen.
*/
struct team {
    int strength, i, j;
};
vector<int> finding_team_member(int N, vector<team> A) {
    vector<int> teams(2*N);

    fill(teams.begin(), teams.end(), -1); // -1 indicates "not assigned"
    
    sort(A.begin(), A.end(), [](const auto& a, const auto& b) {
        return a.strength > b.strength;
    });

    for(const auto& t : A) {
        // Person indices are numbered starting from 1
        if(teams[t.i-1] == -1 && teams[t.j-1] == -1) {
            teams[t.i-1] = t.j;
            teams[t.j-1] = t.i;
        }
    }

    return teams;
}

int main() {
    int N;
    cin >> N;

    vector<team> A;
    A.reserve((2*N)*(2*N-1)/2);
    // Input data starts from the i>2 line
    for(int i = 2; i <= 2*N; i++)
        // Collects the pairs a_i1, a_i2, ... a_i(i-1)
        for(int j = 1; j < i; j++) {
            int s;
            cin >> s;
            A.push_back({ .strength = s, .i = i, .j = j });
        }

    auto assignments = finding_team_member(N, A);

    for(auto const& v : assignments) {
        cout << v << " ";
    }

    cout << endl;
}