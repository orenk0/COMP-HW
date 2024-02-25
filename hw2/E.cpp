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
void dfs(int a, int p){
   if(v[a]==1) flag = 1; 
   if(v[a]) return;
   v[a] = 1;
   for(auto i : g[a]) if(i!=p) dfs(i, a);
   v[a] = 2;
}
void dfsTrue(int a, int p){
   if(v[a]==1) flag = 1; 
   if(v[a]) return;
   v[a] = 1;
   for(auto i : G[a]) if(i!=p) dfsTrue(i, a);
   v[a] = 2;
}

void solve(){
   int K;
   cin >> K;
   for(int i = 0 ; i < K ; i++){
      ll x, y, z, X, Y, Z;
      cin >> x >> y >> z >> X >> Y >> Z;
      //give id to new vertices:
      if(m.find(1000*x+y)==m.end()) m[1000*x+y] = ++counter2;
      if(m.find(1000*X+Y)==m.end()) m[1000*X+Y] = ++counter2;
      if(M.find(1000000*x+1000*y+z)==M.end()) M[1000000*x+1000*y+z] = ++counter3;
      if(M.find(1000000*X+1000*Y+Z)==M.end()) M[1000000*X+1000*Y+Z] = ++counter3;
      //build the floor and the normal graphs.
      if(x!=X||y!=Y) {g[m[1000*x+y]].push_back(m[1000*X+Y]); g[m[1000*X+Y]].push_back(m[1000*x+y]);}
      G[M[1000000*x+1000*y+z]].push_back(M[1000000*X+1000*Y+Z]); G[M[1000000*X+1000*Y+Z]].push_back(M[1000000*x+1000*y+z]);
   }
   //for(int a = 0 ; a <= counter2 ; a++) for(auto i : g[a]) cout << a << "-->" << i << endl;
   //check for cycles using the flag in topo sort:

   flag = 0;
   v = vector<int>(counter3+7);
   for(int i = 0 ; i <= counter3 ; i++) v[i] = 0;
   for(int i = 0 ; i <= counter3 ; i++) if(!v[i]) dfsTrue(i, -1);
   if(flag == 1) cout << "True closed chains" << endl;
   else cout << "No true closed chains" << endl;

   flag = 0;
   v = vector<int>(counter2+7);
   for(int i = 0 ; i <= counter2 ; i++) v[i] = 0;
   for(int i = 0 ; i <= counter2 ; i++) if(!v[i]) dfs(i, -1);
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
//Algorithm: need to be completed.