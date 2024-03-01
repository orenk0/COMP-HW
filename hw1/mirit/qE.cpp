#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/**
 * Represents a range with a left and right boundary and an index.
 * The custom comparator sorts primarily by left boundary and then by right boundary in descending order.
 */
class Range {
public:
    int left, right, index;

    Range(int l, int r, int idx) : left(l), right(r), index(idx) {}

    bool operator<(const Range& other) const {
        if (left == other.left)
            return right > other.right;
        return left < other.left;
    }
};

/**
 * Determines for each range if some other range contains it.
 * Returns a vector of booleans indicating if each range is contained in another.
 */
vector<bool> checkContained(const vector<Range>& ranges) {
    int n = static_cast<int>(ranges.size());
    vector<bool> contained(n, false);
    int maxEnd = 0;

    // Iterate through the ranges to find if a range is contained within another.
    for (int i = 0; i < n; i++) {
        if (ranges[i].right <= maxEnd)
            contained[ranges[i].index] = true;
        maxEnd = max(maxEnd, ranges[i].right);
    }

    return contained;
}

/**
 * Determines for each range if it contains some other range.
 * Returns a vector of booleans indicating if each range contains another range.
 */
vector<bool> checkContains(const vector<Range>& ranges) {
    int n = ranges.size();
    vector<bool> contains(n, false);
    int minEnd = INT_MAX;

    // Iterate through the ranges in reverse to find if a range contains another.
    for (int i = n - 1; i >= 0; i--) {
        if (ranges[i].right >= minEnd)
            contains[ranges[i].index] = true;
        minEnd = min(minEnd, ranges[i].right);
    }

    return contains;
}

/**
 * Solves the one given test case.
 * Reads the input ranges, sorts them, and checks for each range if it contains or is contained by another range.
 */
void solve() {
    int n;
    cin >> n;
    vector<Range> ranges;

    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        ranges.emplace_back(l, r, i);
    }

    // Sort the ranges based on their left and right boundaries.
    sort(ranges.begin(), ranges.end());

    // Check for each range if it contains or is contained by another range.
    vector<bool> contains = checkContains(ranges);
    vector<bool> contained = checkContained(ranges);

    // Print the results for each range.
    for (bool contain : contains)
        cout << contain << " ";
    cout << endl;

    for (bool contain : contained)
        cout << contain << " ";
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}

/**
 * Algorithm Explanation:
 * - The task is to determine, for each range, if it contains some other range and if it is contained within another range.
 * - The ranges are sorted by their left boundaries and, for equal left boundaries, by right boundaries in descending order.
 * - The checkContained function iterates through the sorted ranges to find if any range is contained within another.
 * - The checkContains function iterates in reverse to find if any range contains another.
 *
 * Time Complexity:
 * - O(n log n) for sorting the ranges, where n is the number of ranges.
 * - O(n) for each pass through the ranges (checkContained and checkContains).
 *
 * Space Complexity:
 * - O(n) for storing the ranges and the results.
 */
