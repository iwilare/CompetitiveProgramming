#include <bits/stdc++.h>

using namespace std;

// https://codeforces.com/problemset/problem/603/A?locale=en

/*
    alternative_thinking (time complexity: O(n), space complexity: O(1))
        We can notice that any single flip operation can
        at most increase the score by 2: namely, by creating two
        new alternating digits at the beginning and at the end of
        the flipped sequence.

        A formal proof of this might proceed by imagining all
        strings as being translatable in the following form,

            [alternating] [equal] [alternating] [equal] ...
            0101010101010 0000000 1010101010101 1111111

        where all <alternating> and <equal> sections are of maximal
        size and alternate between each other.

        The case where no flip operation can improve the score
        is the when the longest alternating subsequence is exactly the
        entire string, all bits are already alternating and there are
        no <equal> sections.

        There are also some cases where only 1 single point can be gained,
        such as the following ones:

            [alternating] [equal]
            1010101010101 1
                          ^^^^^^^
                           flip

            [alternating] [equal] [alternating]
            1010101010101 1       0101010101010
                          ^^^^^^^^^^^^^^^^^^^^^
                                 flip

        Obviously, the score cannot ever be greater than N.

        In fact, we can prove the following properties:

            1. Let the length of the longest alternating subsequence be L.
               Then, if L <= N-2 (there are at least two possibly non-consecutive
               bits that are not part of an alternating sequence) we can always
               improve the score to L+2.
               Let us consider the edge case where L == N-2, since the
               other cases can be easily generalized to this one.
               When the two remaining bits are non-consecutive, we can see this by checking
               all cases where we alternate the sequence between them, first bit
               included and last bit excluded.

                             +1 point  +1 point
                               |         |
                               v         v
                        1010101 1 0101010 0 101010
                                ^^^^^^^^^
                                   flip

               When they are consecutive, we can easily check all the cases in
               the form "ABBC", with all the bit combinations with A,B,C. In all
               cases an increase of 2 can be obtained.
            2. We can only improve by 1 iff the length of the longest
               alternating subsequence is N-1. The flipping operation simply
               takes the bit and flips the entire rest of the sequence from there on.
               We can illustrate the intuition behind this with the following picture:

                               +1 point
                                 |
                                 v
                    1010101010101 1 0101010101010
                                  ^^^^^^^^^^^^^^^
                                        flip

        This finally gives us an algorithm to calculate the score.
        First, calculate the maximal alternating subsequence, using
        a simple linear pass of the string, and call it L.
            - If L==N,   the score is L.
            - If L==N-1, the score is L+1.
            - If L<=N-2, the score is L+2.
        In other words, we can refactor this intuition to calculate
        the score as the minimum between N and L+2.
*/

size_t longest_alternating_subsequence(string s) {
    size_t size = s.length() > 0 ? 1 : 0;
    for(size_t i = 0; i < s.length() - 1; i++)
        size += s[i] != s[i+1] ? 1 : 0;
    return size;
}

size_t alternative_thinking(string s) {
    return min(s.length(), longest_alternating_subsequence(s) + 2);
}

int main() {
    size_t N;
    cin >> N;

    string A;
    cin >> A;

    cout << alternative_thinking(A) << endl;
}
