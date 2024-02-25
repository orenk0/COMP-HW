#include<bits/stdc++.h>
using namespace std;


unordered_map<string, int> id;//associate numbers to dishes.
int counter;//counts id for dishes.

using triplet = array<int, 3>;
vector<vector<int>> g;//graph of recipse
vector<vector<triplet>> gw;//graph with price & prestige
int order[10000];
int v[10000];
int p;

void dfs(int a){//for topological sorting.
   if(v[a]==2) return;
   v[a] = 1;
   for(auto i : g[a]) dfs(i);
   v[a] = 2;
   order[p] = a; p--;
}

void solve(){
   int B;
   int N;
   cin >> B >> N;
   counter = -1;//id for next dish.
   g = vector<vector<int>>(10000);//at most 1e4 dishes.
   gw = vector<vector<triplet>>(10000);//at most 1e4 dishes.
   for(int i = 0 ; i < N; i++){
      //input:
      string strong, weak, junk;
      int cost, value;
      cin >> strong >> weak >> junk >> cost >> value;
      if(id.find(strong)==id.end()) id[strong]=++counter;//give number to each dish
      if(id.find(weak)==id.end()) id[weak]=++counter;
      g[id[weak]].push_back(id[strong]);//build the graphs
      gw[id[weak]].push_back({id[strong],cost,value});
   }
   if(B==0 || N==0) {cout << 0 << endl << 0 << endl; return;}

   for(int i = 0 ; i < 10000; i++) v[i] = 0;//init
   p = counter;//init
   for(int i = 0 ; i <= counter ; i++){//topo sort.
      if(!v[i]) dfs(i);
   }

   using pairi = pair<int, int>;
   unordered_map <int, pairi> pnp;//p&p map (price and prestige)
   //chronologically update price & prestige.
   for(int i = 0 ; i <= counter ; i++) pnp[i] = pairi(0,0);
   for(int i = 0 ; i <= counter ; i++){
      for(auto trip : gw[order[i]]){//all neighbors. trip = [id, added price, added pristige]
         if(pnp[trip[0]].first == 0){//new vertex for pnp <---> has price 0.
            pnp[trip[0]] = pair(pnp[order[i]].first+trip[1],pnp[order[i]].second+trip[2]);
         }else{//has p&p already
            if(pnp[order[i]].first+trip[1]<pnp[trip[0]].first){
               //if less pricy update prestige.
               pnp[trip[0]] = pair(pnp[order[i]].first+trip[1], pnp[order[i]].second+trip[2]);
            }else if(pnp[order[i]].first+trip[1]==pnp[trip[0]].first){
               //if same price update prestige to max
               pnp[trip[0]] = pair(pnp[trip[0]].first, max(pnp[order[i]].second+trip[2], pnp[trip[0]].second));
            }
         }
      }
   }

   //now we have for each dish price and prestige.
   //do dynamic programming on budget and until index i.
   int dp[B+1][counter+1];
   for(int i = 0 ; i <= B; i++) for(int j = 0 ; j <= counter ; j++){
      dp[i][j] = 0;
   }
   for(int i = 0 ; i <= B; i++) for(int j = 0 ; j <= counter ; j++){
      int price = pnp[j].first;
      int prestige = pnp[j].second;
      if(j==0){//1 item is easy
         if(price<=i) dp[i][j]=prestige;//enough money
         //else dp[i][j]=0 but its already 0...
      }
      else if(i==0) dp[i][j] = 0;//useless but why not leave it.
      else if(i-price<0) dp[i][j] = dp[i][j-1];
      else dp[i][j] = max(dp[i][j-1], prestige+dp[i-price][j-1]);
      //cout << i << ","<< j << ": "<< dp[i][j] << endl;
   }
   cout << dp[B][counter] << endl;
   for(int i = B; i > 0; i--){
      if(dp[B][counter]>dp[i][counter]) {cout << i+1 << endl; return;}
   }
   cout << 1 << endl;
   return;
}

int main(){
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   int t = 1;
   //cin >> t;
   for(int i = 0; i < t; i++)
      solve();
}

/*
Algorithm:
create the graph of the recipes g (omit the ingredient) each recipe is create from other recipe.
Also create the same graph but save the added price and prestige for every edge.
sort topologically the graph g (we get array "order" which is the same for gw the graph with the weights).
then update chronologically (with the topo order) the price & prestige of each dish.
if you find a better price/prestige for some dish update it.
the base dishes will remain with price & prestige 0.
now that we have the correct price and prestige for each dish we use dynamic programming.
this is the famous algorithm for knapsack (01). We use recursion on the budget and the max index until which we can select dishes.
the relation is described in the code as well as the base cases.
Complexity: 
O(N) for the topo sort.
O(B*n)=O(1e4*1e4) for the dynamic programming. where n = amount of dishes. (it takes O(1) for each cell and there are B*n cells).
overall O(N+B*n)
*/
