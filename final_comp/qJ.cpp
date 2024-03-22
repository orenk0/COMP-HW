#include <bits/stdc++.h>
using namespace std;

const int MAX_VERTICES = 2e5 + 5;

vector<int> tree[MAX_VERTICES];
int n, k, c;
typedef long long ll;
ll max_profit;

int dfs(int curr_node, int parent_node, int depth) {
    int max_depth_child1 = 0, max_depth_child2 = 0;
    for (int child : tree[curr_node]) {
        if (child == parent_node) continue;
        int child_depth = dfs(child, curr_node, depth + 1) + 1;
        if (child_depth > max_depth_child1) {
            max_depth_child2 = max_depth_child1;
            max_depth_child1 = child_depth;
        } else {
            max_depth_child2 = max(max_depth_child2, child_depth);
        }
    }
    max_profit = max(max_profit, 1LL * max_depth_child1 * k + max(0LL, 1LL * max_depth_child2 * (k - c) - 1LL * depth * c));
    return max_depth_child1;
}

void solve() {
    cin >> n >> k >> c;
    max_profit = 0;
    for (int i = 1; i <= n; i++) tree[i].clear();
    for (int i = 0, u, v; i < n - 1; i++) {
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dfs(1, -1, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    vector<ll> results;
    while (T--) {
        solve();
        results.push_back(max_profit);
    }

    for (const auto& res : results) {
        cout << res << endl;
    }

    return 0;
}