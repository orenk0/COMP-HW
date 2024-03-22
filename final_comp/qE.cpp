#include <bits/stdc++.h>

using namespace std;
#include <iostream>
#include <vector>
#include <unordered_set>
#include <utility>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

const ll P1 = 31, P2 = 37;
const ll M1 = 1e9 + 7, M2 = 1e9 + 9;

struct pair_hash {
    size_t operator()(const pll& p) const {
        auto hash1 = hash<ll>{}(p.first);
        auto hash2 = hash<ll>{}(p.second);
        return hash1 ^ hash2;
    }
};

void solve() {
    string s, good;
    int k;
    cin >> s >> good >> k;

    int n = s.length();
    vector<int> badPrefix(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        badPrefix[i + 1] = badPrefix[i] + (good[s[i] - 'a'] == '0');
    }

    unordered_set<pll, pair_hash> uniqueHashes;
    vector<ll> pow1(n + 1, 1), pow2(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        pow1[i] = (pow1[i - 1] * P1) % M1;
        pow2[i] = (pow2[i - 1] * P2) % M2;
    }

    for (int i = 0; i < n; ++i) {
        ll hash1 = 0, hash2 = 0;
        for (int j = i; j < n; ++j) {
            if (badPrefix[j + 1] - badPrefix[i] > k) break;
            hash1 = (hash1 + (s[j] - 'a' + 1) * pow1[j - i]) % M1;
            hash2 = (hash2 + (s[j] - 'a' + 1) * pow2[j - i]) % M2;
            if (badPrefix[j + 1] - badPrefix[i] <= k)
                uniqueHashes.insert({hash1, hash2});
        }
    }

    cout << uniqueHashes.size() << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
