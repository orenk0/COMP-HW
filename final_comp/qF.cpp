#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;
typedef long long ll;
ll arr[MAXN], total_sum = 0;
int n, q;

ll positive_part(ll number) {
    return max(0LL, number);
}

ll compute_min(ll x, ll y, int idx) {
    ll option1 = positive_part(x - arr[idx]) + positive_part(y + arr[idx] - total_sum);
    ll option2 = positive_part(x - arr[idx - 1]) + positive_part(y + arr[idx - 1] - total_sum);
    return min(option1, option2);
}

void solve() {
    cin >> q;
    while (q--) {
        ll x, y;
        cin >> x >> y;
        int idx = lower_bound(arr + 1, arr + n, x) - arr;
        cout << compute_min(x, y, idx) << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        total_sum += arr[i];
    }

    sort(arr, arr + n);
    solve();

    return 0;
}