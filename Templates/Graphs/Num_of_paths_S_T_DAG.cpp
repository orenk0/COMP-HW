/*
We used DFS (without doing topological sort) because we know that when we leave a vertex in dfs,
all the reachable vertex from it already have been visited.
Here we will use the same DFS role.
*/

#include <iostream>
#include <vector>
 
using namespace std;
 
//acyclic directed graph
vector<vector<int>> adj;
vector<bool> vis;
vector<int> dp;
 
void dfs(int cur) {
    vis[cur]=true;
    for(auto son : adj[cur]){
        if (vis[son]) continue;
        dfs(son);
        //why "dp[cur]+=dp[son];" wont work here
        //(inside the loop)?
    }
    for(auto son : adj[cur]){
        dp[cur]+=dp[son];
    }
}
 
 
int main() {
    ios_base::sync_with_stdio(false);
    int n,m,target,source;
   
    cin>>n>>m;
    adj=vector<vector<int>> (n);
    for(int  i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
    }
    cin>>source>>target;
    vis=vector<bool>(n,false);
    dp=vector<int>(n,0);
    dp[target]=1;
    dfs(source);
    cout<<dp[source];
}
/*
 input:
 4 6
 0 1
 0 1
 0 2
 1 2
 1 3
 3 2
 0 2
 output:
 5
 */
