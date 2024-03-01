#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 998244353;

/**
 * Reads and stores the front and back numbers of each card.
 * Returns a vector of pairs, where each pair contains the front and back numbers of a card.
 */
vector<pair<int, int>> readCards(int n) {
    vector<pair<int, int>> cards(n);
    for (int i = 0; i < n; ++i) {
        cin >> cards[i].first >> cards[i].second;
    }
    return cards;
}

/**
 * Initializes the dynamic programming table with base conditions.
 * Returns a 2D vector representing the DP table.
 */
vector<vector<long long>> initializeDP(int n) {
    vector<vector<long long>> dp(n, vector<long long>(2, 0));
    dp[0][0] = dp[0][1] = 1;  // Base conditions: the first card can be either not flipped or flipped.
    return dp;
}

// Updates the DP table based on the card numbers and their adjacency.
void updateDP(vector<vector<long long>>& dp, const vector<pair<int, int>>& cards, int n) {
    for (int i = 1; i < n; ++i) {
        // Update DP values based on the state of the previous card and the current card's numbers.
        if (cards[i].first != cards[i - 1].first) {
            dp[i][0] += dp[i - 1][0];
        }
        if (cards[i].first != cards[i - 1].second) {
            dp[i][0] += dp[i - 1][1];
        }
        if (cards[i].second != cards[i - 1].first) {
            dp[i][1] += dp[i - 1][0];
        }
        if (cards[i].second != cards[i - 1].second) {
            dp[i][1] += dp[i - 1][1];
        }
        dp[i][0] %= MOD;
        dp[i][1] %= MOD;
    }
}

/**
 * Calculates the total number of valid flip combinations.
 * Returns the total number of valid flip combinations modulo MOD.
 */
ll calculateResult(const vector<vector<long long>>& dp, int n) {
    return (dp[n - 1][0] + dp[n - 1][1]) % MOD;
}

/**
 * Solves the Flip Cards problem for a single set of card data.
 */
void solve() {
    int n;
    cin >> n;

    vector<pair<int, int>> cards = readCards(n);
    vector<vector<long long>> dp = initializeDP(n);
    updateDP(dp, cards, n);
    cout << calculateResult(dp, n) << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}

/**
 * Algorithm Explanation:
 * - The task is to find the number of ways to flip cards such that adjacent cards show different numbers.
 * - The readCards function reads the front and back numbers of each card.
 * - The initializeDP function sets up the base conditions for dynamic programming.
 * - The updateDP function computes the DP values based on the state of adjacent cards.
 * - The calculateResult function calculates the total number of valid combinations.
 *
 * Time Complexity:
 * - O(n) for iterating through the cards to update the DP table.
 *
 * Space Complexity:
 * - O(n) for storing the card data and the DP table.
 */
