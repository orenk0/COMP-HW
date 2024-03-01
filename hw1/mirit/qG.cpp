#include <bits/stdc++.h>
using namespace std;

/**
 * Determines the maximum value of k for which Alice can win.
 * It iterates backwards from the highest possible k and checks if Alice can win.
 * Returns the maximum value of k such that Alice can win the game.
 */
int calculateMaxK(const vector<int>& a, int n) {
    // Start from the maximum possible value of k and decrement.
    for (int k = (n + 1) / 2; k > 0; --k) {
        bool valid = true; // Flag to check if Alice can win with the current k.

        // Check if Alice can remove an element less than or equal to k - i + 1 for each stage i.
        for (int i = 0; i < k && valid; ++i) {
            if (a[i + k - 1] > i + 1) {
                valid = false; // Alice can't remove a suitable element.
            }
        }

        if (valid) {
            return k; // Found the maximum k for which Alice can win.
        }
    }
    return 0; // If no suitable k is found, Alice can't win.
}

/**
 * Solves a single instance of the Number Game problem.
 * Reads the array, sorts it, and then calculates the maximum k for Alice to win.
 */
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);

    // Read the array elements.
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end()); // Sort the array to simplify finding the maximum k.

    // Output the maximum k for which Alice can win.
    cout << calculateMaxK(a, n) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve(); // Solve each test case.
    }
    return 0;
}

/**
 * Algorithm Explanation:
 * - The task is to find the maximum value of k such that Alice can win the game against Bob.
 * - Each test case is solved independently in the solve function.
 * - The array is first read and sorted to make it easier to determine the maximum k.
 * - The calculateMaxK function checks, for each potential k, if Alice can successfully remove an element in each stage.
 * - The process involves iterating over the array and checking the conditions for Alice's victory.
 * - Time Complexity: O(n^2), primarily due to the nested loop in calculateMaxK.
 * - Space Complexity: O(n), used for storing the array.
 */
