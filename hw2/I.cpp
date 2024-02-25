#include<bits/stdc++.h>
using namespace std;

using ll = long long;
ll MOD = 2147483647;


void solve(){
   //inputting:
   int n;
   cin >> n;
   vector<int> a(n+1);
   for(int i = 0 ; i <= n ; i++){
      cin >> a[i];
   }
   //init dp
   int dp[n+1][n+2];
   for(int i = 0 ; i <= n; i++) for(int j = 0 ; j <= n+1; j++) dp[i][j] = 0;
   for(int j = 0 ; j <= n; j++) dp[1][j] = (j==a[0]);//base case
   for(int i = 2 ; i <= n ; i++){
      //create accumulate array to calc sums in O(1).
      ll acc[n+2];
      for(int tmp = 0 ; tmp <= n ; tmp++) acc[tmp] = 0;
      ll sum = 0;
      for(int j = 1; j <= n+1 ; j++){
         sum += dp[i-1][j];
         sum %= MOD;
         acc[j] = sum;
      }
      //next row in dp
      for(int j = 1 ; j <= n+1 ; j++){
         if(j==a[i-1]){
            if(a[i-1]<a[i]){//right sign
               dp[i][j] = acc[n+1]-acc[j];//as in description
            }else{//left sign
               dp[i][j] = acc[j];//as in description.
            }
         }else{
            if( (0<(a[i-1]-j)) == (0<(a[i]-j)) ) dp[i][j] = dp[i-1][j];//as in description. else 0 (already).
         }
         dp[i][j] = ((dp[i][j]%MOD)+MOD)%MOD;
      }
   }
   ll sum = 0;
   for(int j = 1; j <= n+1 ; j++){
      sum += dp[n][j];
      sum %= MOD;
   }
   cout << sum << endl;
}

int main(){
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   int t=1;
   //cin >> t;
   for(int i = 0; i < t; i++)
      solve();
}

//Algorithm:
//define:
//dp[i][j] := # of solution with the last sign's base at j up until ith sign.  

//dp[i][j] = if(a[i-1]==j) sum{k} dp[i-1][k]. sum for k iff sign(a[i]-a[i-1]) == -sign(a[i-1]-k).
// this is sum dp[i-1][k] for all k in [1,a[i-1]] if a[i] < a[i-1]
// else this is sum dp[i-1][k] for all k in [a[i-1],n].
//note that it doesn't matter if we include or exclude dp[i-1][k] for k=a[i-1] because it's 0.

//else it's dp[i-1][j] if the the signs are in the same direction and otherwise 0.
//dp[1][j] = (j==a[0])

//use accumulated array to calculate sums efficiently in O(1).
//everytime we calculate a new row take its mod as in the question.

//complexity:
//O(n^2)
// to calculate each row we calculate the accumulated array in O(n).
// then we calculate each entry in O(1).
// so every row takes O(n) time.
//there are overall O(n) rows hence O(n^2) total time.