/*

We want to choose some items, such that the total weight won't exceed 𝑊, and maximize the sum of the values.

N: Number of items
W: Maximum Weight
w: n weights
v: n items

*/

void solve() {
  int N, W;
  cin >> N >> W;
  vector<int> w(N), v(N);
  for (int i = 0; i < N; i++) {
    cin >> w[i] >> v[i]; 
  }
  vector<ll> dp(W + 1, 0);
  for (int i = 0; i < N; i++) {
    for (int j = W; j >= 0; j--) { 
      if (j - w[i] >= 0) {       
        dp[j] = max(dp[j], v[i] + dp[j - w[i]]); 
      }    
        }
  } 
  cout << dp[W] << endl;
}
