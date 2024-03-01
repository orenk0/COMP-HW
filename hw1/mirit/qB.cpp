#include <bits/stdc++.h>
using namespace std;

// Function to solve a single test case.
void solve() {
    int n; // Number of elements in the array.
    cin >> n;

    vector<int> a(n); // Array of integers.
    double sum = 0; // Sum of all elements in the array.
    int max_elem = INT_MIN; // Variable to store the maximum element in the array.

    for (int i = 0; i < n; i++) {
        cin >> a[i]; // Input each element of the array.
        sum += a[i]; // Calculate the sum of the elements.
        max_elem = max(a[i], max_elem); // Find the maximum element.
    }
    // Calculate the average of the subsequence containing only the maximum element.
    double f_a = max_elem;
    // Calculate the average of the subsequence containing all elements except the maximum one.
    double f_b = (sum - max_elem) / (n - 1);

    // Output the maximum possible value of f(a) + f(b).
    cout << fixed << setprecision(9) << (f_a + f_b) << endl;
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
 * - The goal is to split an array into two non-empty subsequences such that the sum of their averages is maximized.
 * - The optimal strategy is to put the maximum element in one subsequence (f(a)) and the rest in the other (f(b)).
 * - This is because a single maximum element as a subsequence yields the maximum value itself as the average,
 *   and the average of the remaining elements is maximized when they are all together.
 *
 * Time Complexity:
 * - The overall time complexity of the solution is O(T * N), where T is the number of test cases and N is the number
 *   of elements in each test case. This is because the solution iterates through each element of the array for every test case.
 *
 * Space Complexity:
 * - The space complexity is O(N), due to the storage of the array 'a' of size N.
 */
