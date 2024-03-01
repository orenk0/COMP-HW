#include <bits/stdc++.h>
using namespace std;

void tarjan(int u, vector<vector<int>>& g, vector<int>& d, vector<int>& low, vector<bool>& stacked, stack<int>& s, int& ticks, int& current_scc, vector<int>& scc) {
    d[u] = low[u] = ticks++;
    s.push(u);
    stacked[u] = true;
    for (int v : g[u]) {
        if (d[v] == -1) {
            tarjan(v, g, d, low, stacked, s, ticks, current_scc, scc);
            low[u] = min(low[u], low[v]);
        } else if (stacked[v]) {
            low[u] = min(low[u], d[v]);
        }
    }
    if (d[u] == low[u]) {
        int v;
        do {
            v = s.top();
            s.pop();
            stacked[v] = false;
            scc[v] = current_scc;
        } while (u != v);
        current_scc++;
    }
}


vector<vector<int>> initGraph(int n, int m) {
    vector<vector<int>> g = vector<vector<int>> (n);
    for(int i=0; i<m; i++) {
        int city_a, city_b;
        cin >> city_a >> city_b;
        city_a--;
        city_b--;
        g[city_a].push_back(city_b);
    }
    return g;
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int m;
    int capital;
    cin >> n;
    cin >> m;
    cin >> capital;
    capital--;
    vector<vector<int>> g = initGraph(n, m);
    vector<int> d(n, -1), low(n), scc(n);
    vector<bool> stacked(n, false);
    stack<int> s;
    int ticks = 0, current_scc = 0;


    for (int i = 0; i < n; ++i) {
        if (d[i] == -1) {
            tarjan(i, g, d, low, stacked, s, ticks, current_scc, scc);
        }
    }

    return 0;
}