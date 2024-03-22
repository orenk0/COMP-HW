#include <bits/stdc++.h>
using namespace std;

vector<int> computeLPS(const string& str) {
    int n = str.size();
    vector<int> lps(n, 0);
    int len = 0, i = 1;
    while (i < n) {
        if (str[i] == str[len]) {
            lps[i++] = ++len;
        } else if (len) {
            len = lps[len - 1];
        } else {
            lps[i++] = 0;
        }
    }
    return lps;
}

void printBorders(const string& str) {
    vector<int> lps = computeLPS(str);
    int i = lps.back();
    vector<int> borders;
    while (i) {
        borders.push_back(i);
        i = lps[i - 1];
    }
    reverse(borders.begin(), borders.end());
    for (int border : borders) {
        cout << border << " ";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string str;
    cin >> str;
    printBorders(str);
    cout << endl;

    return 0;
}
