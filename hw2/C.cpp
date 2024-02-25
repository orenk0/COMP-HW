#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<vector<int>> G;
vector<int> vis;

//bfs like in class. but when it reaches finish it stops and return the distance.
int bfs(int start, int finish) {
    for(int x : G[start])
       vis[x]=true;
    vector<int> cur_level=G[start];
    int dist=0;
    while (!cur_level.empty()) {
      vector<int> next_level;
      for(int f : cur_level) {
         for(int s : G[f]) {
            if (vis[s]) continue;
            vis[s]=true;
            next_level.push_back(s);
         }
      }
      dist++;
      if(find(cur_level.begin(), cur_level.end(), finish) != cur_level.end()){
         return dist;//if finish is in this level return dist.
      }
      cur_level = next_level;
      
    }
    return -1;
}


void solve(){
      //get all the inputs:
		int n, m;
      cin >> n >> m;
      vector<int> C(n);
      for(int i = 0 ; i < n; i++){
         cin >> C[i];
      }
      //build the graph g from the question:
      g=vector<vector<int>>(n);
      for(int j = 0 ; j < m ; j++){
         int x, y;
         cin >> x >> y;
         g[x-1].push_back(y-1);//starting from 0 not 1
         g[y-1].push_back(x-1);
      }
      //build the graph of pairs of pointers G.
      G=vector<vector<int>>(n*n);
      for(int i = 0; i < n; i++){
         for(int j = 0; j < n ; j++){
            for(int a : g[i]){
               for(int b : g[j]){
                  if(C[a]!=C[b] && C[i]!=C[j]){//can move only if the colors are different
                     G[n*i+j].push_back(n*a+b);
                  }
               }
            }
         }
      }
      vis=vector<int>(n*n);//for the bfs on the n^2 vertecies of G
      cout << bfs(n-1,n*(n-1)) << endl;//bfs just for dist
}

int main(){
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   int t;
   cin >> t;
   for(int i = 0; i < t; i++)
      solve();
}
/*Algorithm:
build the graph g from the question.
then buld a new graph G in which every vertex represents a pair of vertecies in g.
put edges between vertecies iff one can move from one position to another legally (colors remain different).
represent each pair of vertices in g as n*i+j (this is a bijection).
finally using BFS find the distance between the the pair representing (0,n) and (n,0).
Complexity:
O(n^2+m^2)=O(n^2) since in G there are at most m^2 edges and n^2 vertices. the building of it takes O(n^2) also because
we iterate over all pairs of vertices and check stuff in O(1) time.
*/