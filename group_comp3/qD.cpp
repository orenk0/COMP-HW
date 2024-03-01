#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF_N = -1e18;

void computeLPSArray(const vector<ll>& pattern, size_t M, vector<ll>& lps) {
    ll length = 0;
    lps[0] = 0;
    int i = 1;

    while (i < M) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

ll KMPSearch(const vector<ll>& pattern, const vector<ll>& text) {
    auto M = pattern.size();
    auto N = text.size();
    vector<ll> lps(M, 0);

    computeLPSArray(pattern, M, lps);

    ll i = 0;
    ll j = 0;
    int count = 0; // Counter for the number of times the pattern is found

    while (i < N) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == M) {
            count++; // Pattern found
            j = lps[j - 1];
        } else if (i < N && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }

    return count;
}

ll solve() {
    int n;
    int m;
    cin >> n;
    cin >> m;

    vector<ll> a(n);
    vector<ll> b(m);
    ll result;
    if (n < m) {
        result = 0;
        return result;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    vector<ll> a_diff(n-1);
    vector<ll> b_diff(m-1);

    for (int i = 1; i < n; i++) {
        a_diff[i-1] = a[i] - a[i-1];
    }

    if (b.size() == 1) {
        result = a.size();
        return result;
    }

    for (int i = 1; i < m; i++) {
        b_diff[i-1] = b[i] - b[i-1];
    }
    return KMPSearch(b_diff, a_diff);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll result = solve();
    cout << result << endl;

    return 0;
}