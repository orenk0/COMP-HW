#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Define a constant representing a very small number for initialization purposes.
const ll INF_N = -1e18;

// Function to calculate the maximum difference for each element with its adjacent elements.
// Time Complexity: O(N), where N is the number of elements in the array.
// Each element is accessed once to calculate the differences.
vector<ll> getMaxDiffsArr(vector<ll>& a, int n) {
    vector<ll> max_diffs(n); // Stores the maximum difference for each element.
    for (int i = 0; i < n; i++) {
        ll prev_diff = (i == 0) ? INF_N : abs(a[i] - a[i - 1]);
        ll next_diff = (i == (n - 1)) ? INF_N : abs(a[i] - a[i + 1]);
        max_diffs[i] = max(prev_diff, next_diff);
    }
    return max_diffs;
}

// Function to solve a single test case.
// Time Complexity: O(N), due to the getMaxDiffsArr function call.
void solve() {
    int n;
    cin >> n;

    vector<ll> a(n); // The array of elements.
    ll result; // Variable to store the final result.

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (n == 2) {
        result = abs(a[0] - a[1]);
    } else {
        vector<ll> max_diffs = getMaxDiffsArr(a, n);
        result = *min_element(max_diffs.begin(), max_diffs.end());
    }
    cout << result << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    // Overall Time Complexity: O(T * N), where T is the number of test cases.
    while (T--) {
        solve(); // Solve each test case.
    }

    // Space Complexity: O(N), where N is the size of the array.
    // This is due to the additional vector 'max_diffs' in the getMaxDiffsArr function.
    return 0;
}

/**
 * Algorithm Explanation:
 * - The goal is to find the optimal score in a game where Alice tries to minimize the absolute difference
 *   between her chosen element and Bob's adjacent choice, while Bob aims to maximize it.
 * - For each element in the array, we calculate the maximum absolute difference with its adjacent elements.
 * - If the array has only two elements, the result is the absolute difference between them.
 * - For larger arrays, the optimal score is the minimum of the maximum differences calculated for each element.
 *   This represents the best Alice can do to minimize the score, considering Bob's optimal play.
 */
