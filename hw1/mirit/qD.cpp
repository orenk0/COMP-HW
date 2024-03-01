#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 1e9 + 7;


// Calculates the bitwise AND of all elements in a vector.
ll calculateBitwiseAnd(const vector<ll>& v) {
    ll result = v[0];
    for (size_t i = 1; i < v.size(); i++) {
        result &= v[i];
    }
    return result;
}

// Counts the occurrences of a specific value in the vector.
ll countOccurrences(const vector<ll>& v, ll value) {
    return count(v.begin(), v.end(), value);
}

// Calculates the factorial of a number modulo MOD.
ll factorialMod(ll n) {
    ll result = 1;
    for (ll i = 1; i <= n - 2; i++) {
        result = result * i % MOD;
    }
    return result;
}

/**
 * Solves a single test case of the problem.
 * Finds the number of good permutations for the given sequence.
 */
void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    ll bitwiseAnd = calculateBitwiseAnd(a);
    ll occurrenceCount = countOccurrences(a, bitwiseAnd);

    // Calculate the result using the formula and output it.
    ll ans = factorialMod(n) * occurrenceCount % MOD * (occurrenceCount - 1) % MOD;
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}

/**
 * Algorithm Explanation:
 * - The goal is to find the number of permutations of the sequence that are 'good'.
 * - A sequence is 'good' if the bitwise AND of all elements from the start to any point is equal
 *   to the bitwise AND of all elements from that point to the end.
 * - First, the bitwise AND of all elements is calculated.
 * - Then, count how many times this bitwise AND value occurs in the sequence.
 * - The number of good permutations is then calculated using the formula:
 *   factorial(n-2) * count * (count - 1) % MOD.
 *
 * Time Complexity:
 * - O(n) for each test case, due to iterating over the sequence to calculate bitwise AND and count occurrences.
 *
 * Space Complexity:
 * - O(n) for storing the sequence in a vector.
 */
