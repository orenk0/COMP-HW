/*
Given a Directed Acyclic Graph with n vertices and m edges.
The task is to find the length of longest path that exist from a source vertex to destination vertex.
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
    }
    for(auto son : adj[cur]){
        if(dp[son]!=-1)
            dp[cur]=max(dp[cur],1+dp[son]);
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
    dp=vector<int>(n,-1);
    dp[target]=0;
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
 3
 */
