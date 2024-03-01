#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Function to solve a single test case.
void solve() {
    int n; // Size of the array.
    cin >> n;

    vector<ll> a(n); // The initial permutation array.
    vector<ll> x(n, 1); // Array to store the starting indices for the operations.

    for (int i = 0; i < n; i++) {
        cin >> a[i]; // Input each element of the permutation.
    }

    vector<pair<ll,ll>> res; // Vector to store pairs of difference and index.
    for (int i = 1; i < n; i++) {
        if (a[i] < a[i - 1]) {
            // Store the difference and the index+1 if an inversion is found.
            res.emplace_back(a[i - 1] - a[i], i + 1);
        }
    }

    // Sort the pairs in descending order of differences.
    sort(res.begin(), res.end(), greater<>());

    // Assign indices from the sorted pairs to x, decrementing the increment value.
    int increment = n - 1;
    for (auto & re : res) {
        x[increment] = re.second;
        increment--;
    }

    // Output the indices for the operations.
    for (ll index : x) {
        cout << index << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; // Number of test cases.
    cin >> T;
    // Process each test case.
    while (T--) {
        solve();
    }
    return 0;
}

/**
 * Algorithm Explanation:
 * - The goal is to minimize the number of inversions in the final array after performing n operations.
 * - Each operation allows incrementing all elements in a suffix of the array by the operation number.
 * - The solution first identifies inversions and stores their magnitude and position.
 * - These pairs are then sorted in descending order of the inversion magnitude.
 * - Starting from the largest inversion, operations are applied to increasingly smaller suffixes.
 * - This approach helps in balancing the array elements to minimize inversions.
 *
 * Time Complexity:
 * - The time complexity of the solution is O(T * N * log N), where T is the number of test cases and N is the size
 *   of the permutation array. Sorting the inversion pairs contributes to the log N factor.
 *
 * Space Complexity:
 * - The space complexity is O(N), mainly due to the storage of the array 'v' and the vector 'res' of pairs.
 */
