#include <bits/stdc++.h>

using namespace std;

// https://practice.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1

/*
    meetings_in_one_room (time complexity: O(n log n), space complexity: O(n))
        Use a similar approach to the one presented to solve
        the job sequencing problem. First, sort the meetings
        in ascending order according to their ending time.
        Then, scan the array from the beginning and greedily
        take all the possible meetings as long as they are
        non-overlapping, updating the right end as we go.
*/

int maxMeetings(int start[], int end[], int n) {
    vector<tuple<int, int, int>> meetings(n);

    for(int i = 0; i < n; i++)
        meetings[i] = make_tuple(start[i], end[i], i + 1);

    sort(meetings.begin(), meetings.end(),
         [](tuple<int, int, int>& a, tuple<int, int, int>& b) {
            return get<1>(a) != get<1>(b)
                 ? get<1>(a) <  get<1>(b)
                 : get<2>(a) <  get<2>(b); // (In a previous version,)
                                           // The problem required to pick the lowest meeting
         });

    int count = 0;
    int last_end = 0;
    for(auto const& m : meetings) {
        if(get<0>(m) > last_end) {
            last_end = get<1>(m);
            count++;
        }
    }
    return count;
}
