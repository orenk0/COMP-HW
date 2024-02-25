#include<bits/stdc++.h>
using namespace std;

using ll = long long;

vector<vector<int>> g(100000);//pairs
vector<vector<int>> G(100000);//triplets

unordered_map<ll, int> m;//pairs map for id
unordered_map<ll, int> M;//triplets map for id
int counter2 = -1;//pairs
int counter3 = -1;//triplets

int flag;
vector<int> v;
void dfs(int a, int p){//used for the floor graph to find cycles
   if(v[a]==1) flag = 1; //there is a cycle
   if(v[a]) return;
   v[a] = 1;
   for(auto i : g[a]) if(i!=p) dfs(i, a);//dont go back to the parent (this will be a false cycle)
   v[a] = 2;
}
void dfsTrue(int a, int p){//used for the true graph to find cycles
   if(v[a]==1) flag = 1;//there is a cycle
   if(v[a]) return;
   v[a] = 1;
   for(auto i : G[a]) if(i!=p) dfsTrue(i, a);//dont go back to the parent (this will be a false cycle)
   v[a] = 2;
}

void solve(){
   int K;
   cin >> K;
   for(int i = 0 ; i < K ; i++){
      ll x, y, z, X, Y, Z;
      cin >> x >> y >> z >> X >> Y >> Z;
      //give id to new vertices:
      if(m.find(1000*x+y)==m.end()) m[1000*x+y] = ++counter2;//new id if unfound
      if(m.find(1000*X+Y)==m.end()) m[1000*X+Y] = ++counter2;//new id if unfound
      if(M.find(1000000*x+1000*y+z)==M.end()) M[1000000*x+1000*y+z] = ++counter3;//new id if unfound
      if(M.find(1000000*X+1000*Y+Z)==M.end()) M[1000000*X+1000*Y+Z] = ++counter3;//new id if unfound
      //build the floor and the normal graphs.
      if(x!=X||y!=Y) {g[m[1000*x+y]].push_back(m[1000*X+Y]); g[m[1000*X+Y]].push_back(m[1000*x+y]);}
      G[M[1000000*x+1000*y+z]].push_back(M[1000000*X+1000*Y+Z]); G[M[1000000*X+1000*Y+Z]].push_back(M[1000000*x+1000*y+z]);
   }
   //check for cycles using the flag in topo sort:

   flag = 0;
   v = vector<int>(counter3+7);//visits for topo sort
   for(int i = 0 ; i <= counter3 ; i++) v[i] = 0;
   for(int i = 0 ; i <= counter3 ; i++) if(!v[i]) dfsTrue(i, -1);// topo sort without order
   if(flag == 1) cout << "True closed chains" << endl;
   else cout << "No true closed chains" << endl;

   flag = 0;
   v = vector<int>(counter2+7);//visits for topo sort
   for(int i = 0 ; i <= counter2 ; i++) v[i] = 0;
   for(int i = 0 ; i <= counter2 ; i++) if(!v[i]) dfs(i, -1);//topo sort without order
   if(flag == 1) cout << "Floor closed chains" << endl;
   else cout << "No floor closed chains" << endl;


}

int main(){
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   int t=1;
   //cin >> t;
   for(int i = 0; i < t; i++)
      solve();
}
/*Algorithm: 
We build 2 undirected graphs 1 for the floor and 1 for the 3d space.
each different wool ball will be hashed to a small unique id we give it.
for the floor we associate each vertex with each projection.
that way the input of the needles builds 2 graphs. (1 just ignores the z coordinate).
also if there is a vertical (x,y constants) edge we are omiting it from the floor graph.
now we just check for cycles using the flag from topological sorting (and avoiding going back to the parent).
time complexity:
O(K) for the building from the inputs (at most 2K vertices) and for the topo sort.
Space complexity:
O(K) thanks to the fact that the max id is the number of vertices. So each graph doesn't use more than this much space.
*/