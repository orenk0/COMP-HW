/*
A bipartite graph is a graph whose vertices can be divided into two disjoint sets so that every edge connects two vertices from different sets 
(i.e. there are no edges which connect vertices from the same set). These sets are usually called sides.

A graph is bipartite if and only if all its cycles have even length. However, in practice it's more convenient to use a different formulation of the definition: a graph is bipartite if and only if it is two-colorable.
Can be done using a BFS: partition the nodes according to the parity of their depths. If there is a back edge to a same depth node (i.e. odd cycle) then the graph is not barpitite.
*/

int n;
vector<vector<int>> adj;

vector<int> side(n, -1);
bool is_bipartite = true;
queue<int> q;
for (int st = 0; st < n; ++st) {
    if (side[st] == -1) {
        q.push(st);
        side[st] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u : adj[v]) {
                if (side[u] == -1) {
                    side[u] = side[v] ^ 1;
                    q.push(u);
                } else {
                    is_bipartite &= side[u] != side[v];
                }
            }
        }
    }
}

cout << (is_bipartite ? "YES" : "NO") << endl;
