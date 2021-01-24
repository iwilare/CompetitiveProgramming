#include <bits/stdc++.h>

using namespace std;

// https://codeforces.com/problemset/problem/611/C

/*
    grid_and_domino (time complexity: O(wh + q), space complexity: O(wh))
*/

struct query {
    int64_t r1, c1, r2, c2;
};

void grid_and_domino(vector<vector<bool>> const& M, int64_t h, int64_t w, vector<query> const& Q) {
    vector<vector<int64_t>> rows(h,     vector<int64_t>(w + 1, 0));
    vector<vector<int64_t>> cols(h + 1, vector<int64_t>(w,     0));
    vector<vector<int64_t>> sums(h + 1, vector<int64_t>(w + 1, 0));

    for(int64_t i = 1; i < h; i++)
        for(int64_t j = 1; j <= w; j++)
            rows[i][j] = rows[i][j-1] + (M[i][j] && M[i+1][j]);

    for(int64_t i = 1; i <= h; i++)
        for(int64_t j = 1; j < w; j++)
            cols[i][j] = cols[i-1][j] + (M[i][j] && M[i][j+1]);

    for(int64_t i = 1; i <= h; i++)
        for(int64_t j = 1; j <= w; j++)
            sums[i][j] = + sums[i][j-1]
                         + sums[i-1][j]
                         - sums[i-1][j-1]
                         + (M[i][j] ? M[i][j-1] + M[i-1][j] : 0);

    for(auto const& q : Q)
        cout << + sums[q.r2  ][q.c2  ]
                - sums[q.r1-1][q.c2  ]
                - sums[q.r2  ][q.c1-1]
                + sums[q.r1-1][q.c1-1]

                - (cols[q.r2  ][q.c1-1] - cols[q.r1-1][q.c1-1])
                - (rows[q.r1-1][q.c2  ] - rows[q.r1-1][q.c1-1]) << endl;
}

int main() {
    int64_t h, w;
    cin >> h >> w;

    vector<vector<bool>> M(h + 2, vector<bool>(w + 2, false));

    for(int64_t i = 1; i <= h; i++) {
        string s;
        getline(cin >> ws, s);
        for(int64_t j = 0; j < w; j++)
            M[i][j + 1] = s[j] == '.';
    }

    int64_t Q;
    cin >> Q;

    vector<query> Qs(Q);
    for(auto& q : Qs)
        cin >> q.r1 >> q.c1 >> q.r2 >> q.c2;

    grid_and_domino(M, h, w, Qs);
}
