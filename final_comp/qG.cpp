#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 998244353;
ll dp[103][103];

ll FastExpo(ll base, ll exponent) {
    ll result = 1;
    while (exponent > 0) {
        if (exponent & 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exponent >>= 1;
    }
    return result;
}

ll ComputePaths(ll point1, ll point2, ll maxPos1, ll maxPos2, ll stepSize1, ll stepSize2) {
    if (point1 >= maxPos1) {
        return 1;
    }
    if (point2 >= maxPos2) {
        return 0;
    }
    if (dp[point1][point2] != -1) {
        return dp[point1][point2];
    }

    ll paths = 0;
    for (ll i = 1; i <= stepSize1; ++i) {
        for (ll j = 1; j <= stepSize2; ++j) {
            paths = (paths + ComputePaths(point1 + i, point2 + j, maxPos1, maxPos2, stepSize1, stepSize2)) % MOD;
        }
    }

    ll inv = FastExpo(stepSize1 * stepSize2, MOD - 2);
    dp[point1][point2] = (paths * inv) % MOD;
    return dp[point1][point2];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n, a, b, p, q;
    cin >> n >> a >> b >> p >> q;
    memset(dp, -1, sizeof(dp));
    cout << ComputePaths(a, b, n, n, p, q) << endl;

    return 0;
}