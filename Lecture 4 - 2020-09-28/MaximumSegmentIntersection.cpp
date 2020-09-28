#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    maximum_segment_intersection (time complexity: O(n log n), space complexity: O(n))
        First, identify all segment start and end points by sorting all of them
        according to their position. Linearly scan these points by summing one
        to the number of current intersections when any segment opens and
        subtracting one when a point indicates the end of a segment, while
        keeping track of the current maximum.
*/
int maximum_segment_intersection(vector<pair<int64_t, int64_t>> const& segments) {
    vector<pair<int, int64_t>> points;
    points.reserve(2*segments.size());

    for(const auto& s : segments) {
        points.emplace_back(+1, s.first);
        points.emplace_back(-1, s.second);
    }

    sort(points.begin(), points.end(), 
         [](const auto& a, const auto& b) { return a.second < b.second; });

    int intersections = 0, max_intersections = 0, max_i = -1;
    for(const auto& p : points) {
        intersections += p.first;
        if(intersections > max_intersections) {
            max_intersections = intersections;
            max_i             = p.second;  
        }
    }

    return max_i;
}

int main() {
    int T;
    cin >> T;

    for(int t = 0; t < T; t++) {
        int N;
        cin >> N;

        vector<pair<int64_t, int64_t>> A;
        A.reserve(N);
        for(int i = 0; i < N; i++) {
            int64_t start, end;
            cin >> start >> end;
            A.emplace_back(start, end);
        }

        cout << maximum_segment_intersection(A) << endl;
    }
}