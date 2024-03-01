#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

size_t gcd(size_t a, size_t b) {
    return b == 0 ? a : gcd(b, a % b);
}

vector<int> computePrefix(const string& s) {
    auto n = s.length();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}


string findShortestRepetitiveSubstring(const string& s) {
    vector<int> pi = computePrefix(s);
    auto n = s.length();
    auto len = n - pi[n - 1];

    if (n % len == 0) {
        return s.substr(0, len);
    } else {
        return s;
    }
}

ll countDivisors(size_t n) {
    ll count = 0;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            if (i == n / i) {
                count += 1;
            } else {
                count += 2;
            }
        }
    }
    return count;
}

void solve() {
    string a;
    string b;

    cin >> a;
    cin >> b;

    string prefix_a = findShortestRepetitiveSubstring(a);
    string prefix_b = findShortestRepetitiveSubstring(b);

    if (prefix_a != prefix_b) {
        cout << 0 << endl;
    }
    else {
        auto l_a = a.length() / prefix_a.length();
        auto l_b = b.length() / prefix_b.length();
        auto gcd_ = gcd(l_a, l_b);
        cout << countDivisors(gcd_) << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}