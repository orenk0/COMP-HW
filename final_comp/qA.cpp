#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;
vector<int> tree[MAXN];
int subtree_size[MAXN];

void dfs(int node, int parent) {
    subtree_size[node] = 1;
    for(auto& child : tree[node]) {
        if(child != parent) {
            dfs(child, node);
            subtree_size[node] += subtree_size[child];
        }
    }
}

int find_centroid(int node, int parent, int total_nodes) {
    for(auto& child : tree[node]) {
        if(child != parent) {
            if(subtree_size[child] > total_nodes / 2) {
                return find_centroid(child, node, total_nodes);
            }
        }
    }
    return node;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    for(int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(1, -1);
    int centroid = find_centroid(1, -1, n);
    cout << centroid << endl;

    return 0;
}