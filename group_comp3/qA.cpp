#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return (a / gcd(a, b)) * b;
}

ll count_divisibles(ll n, ll m, ll x) {
    return (x / n) + (x / m) - (2 * (x / lcm(n, m)));
}

void solve() {
    ll n;
    ll m;
    ll k;

    cin >> n;
    cin >> m;
    cin >> k;

    ll left = 1, right = max(n, m) * k;
    ll ans = 0;

    while (left <= right) {
        ll mid = left + (right - left) / 2;
        if (count_divisibles(n, m, mid) < k) {
            left = mid + 1;
        } else {
            ans = mid;
            right = mid - 1;
        }
    }

    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}