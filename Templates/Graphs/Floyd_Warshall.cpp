/* FW - Solves the all-pairs shortest path problem in a weighted (directed or not) graph in 𝑂(𝑛^3) time where 𝑛 is the number of vertices in the graph.
Main idea (dynamic programming):

Dp[k][i][j] is the shortest dist from i to j using vertices only from the set {1,2,3..,k} as intermediate points along the way. Two possibilities -
(1) a path that does not go through vertex k (only uses vertices in the set {1,2,..k-1})
(2) a path that does go through k
			Dp[k][i][j] = min ( Dp[k-1][i][j] , dp[k-1][i][k] + dp[k-1][k][j])
*/

const int INF = 1000000000;
int n;vector<vector<int>> d;


//Init:
//d[i][i] = 0
//if there's an edge (i, j) with weight w, then d[i][j] = w, else d[i][j] = INF.

void floyd_warshall() {
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (d[i][k] < INF && d[k][j] < INF) {
          d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
      }
    }
  }
}


