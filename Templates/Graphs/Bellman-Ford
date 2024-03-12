/* (BF: single-source shortest paths with the ability to detect negative cycles)

The Bellman-Ford algorithm solves the single source shortest path problem on a weighted
(directed or not) graph in time O(nm). 

Capable of handling graphs in which some of the edge weights are negative numbers.

Capable of detecting negative cycle reachable from the source vertex.

*/

const ll INF = 1e18;
int n;
vector<array<int, 3>> edges;
vector<int> parent;
vector<ll> dist;
bool has_negative_cycle = false;
int cycle_start = -1;

void bellman_ford(int source) {
  dist = vector<ll>(n, INF);
  parent = vector<int>(n, 0);
  dist[source] = 0;
  for (int iter = 1; iter <= n; iter++) {
    has_negative_cycle = false;
    for (auto &[u, v, w]: edges) {
      if (dist[u] + w < dist[v]) {
        has_negative_cycle = true;
        dist[v] = dist[u] + w;
        parent[v] = u;
        cycle_start = v;
      }
    }
  }
}

/* SPECIAL CASE
Even if there is a negative cycle reachable from 0, for a particular v, it is still possible
that the shortest path from 0 to v is well deﬁned.

d[v] is not well deﬁned if and only if there is a negative cycle C s.t 0 → C and C → v.

To detect this, a simple Bellman-Ford is not enough. 
*/
