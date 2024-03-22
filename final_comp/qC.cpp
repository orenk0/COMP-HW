#include<bits/stdc++.h>
using namespace std;

const int MAXN = 200010;
int bitCounts[MAXN][32];

bool check(int l, int mid, int k) {
    int num = 0;
    for (int i = 0; i <= 31; ++i) {
        if (bitCounts[mid][i] - bitCounts[l - 1][i] == mid - l + 1) {
            num |= 1 << i;
        }
    }
    return num >= k;
}

string solve() {
    int n, q, x, l, k;
    cin >> n;
    // Resetting the precomputed bitCounts array
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < 32; ++j) {
            bitCounts[i][j] = 0;
        }
    }
    for (int i = 1; i <= n; ++i) {
        cin >> x;
        for (int j = 0; j < 32; ++j) {
            bitCounts[i][j] = bitCounts[i - 1][j] + ((x >> j) & 1);
        }
    }

    cin >> q;
    string result;
    while (q--) {
        cin >> l >> k;
        int L = l, R = n, answer = -1;
        while (L <= R) {
            int mid = (L + R) / 2;
            if (check(l, mid, k)) {
                answer = mid; // Update answer and try to find larger r
                L = mid + 1;
            } else {
                R = mid - 1;
            }
        }
        result += to_string((answer < l ? -1 : answer)) + " ";
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    vector<string> results(T);

    for (int i = 0; i < T; ++i) {
        results[i] = solve();
    }

    for (const auto& res : results) {
        cout << res << endl;
    }

    return 0;
}
