/* Connected Components in a Graph
Initially we have an empty graph.
We have to add vertices and undirected edges, and answer queries of the form (a,b) -
"are the vertices a and b in the same connected component of the graph?"

This application is quite important, because nearly the same problem appears in
Kruskal's algorithm for finding a minimum spanning tree.
Using DSU we can get running time of 𝑂(𝑚⋅𝛼(𝑛)).
*/

/* Minimum Spanning Tree
A minimum spanning tree (MST) is a subset of the edges of a connected, edge-weighted undirected graph that connects all the vertices together, without any cycles and with the minimum possible total edge weight
We will use Kruskal’s and Prim’s algorithms to address this problem.
*/

/* Kruskal
Let's sort the edges by their weight and start greedly pick edges in weight increasing order.
Before we pick an edge let's make sure it isn't create a cycle with the edges we have already picked.
*/


ll kruskal(vector<array<int, 3>> &edges, ll n) {
  sort(edges.begin(), edges.end());
  dsu uf(n);
  ll mst_weight = 0;
  for (auto [w, x, y]: edges) {
    if (uf.find_(x) == uf.find_(y)) continue;
      mst_weight += w;   
      uf.union_(x, y);   
  }
  return mst_weight;
}




#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <set>
#include <map>
#include <queue>
#include <unordered_map>
 
 
using namespace std;
//DSU
struct dsu
{
    vector<int> parent;
    vector<int> sz;
    
    dsu(int n)
    {
        parent=vector<int>(n);
        for(int i=0;i<n;i++)parent[i]=i;
        sz=vector<int>(n,1);
    }
    
    int find_(int x)
    {
        int root=x;
        while(root!=parent[root])
            root=parent[root];
        
        //Path compression
        while(parent[x]!=root)
        {
            int p=parent[x];
            parent[x]=root;
            x=p;
        }
        return root;
    }
    bool union_(int x,int y)
    {
        int X=find_(x);
        int Y=find_(y);
        // x and y are already in the same set
        if(X==Y)
            return false;
        // x and y are not in same set, so we merge them
        if(sz[X]<sz[Y])
            swap(X, Y);
        // merge yRoot into xRoot
        parent[Y]=X;
        sz[X]+=sz[Y];
        return true;
    }
};
 
int main(){
    ios::sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
    vector<pair<int, pair<int, int>>> edges(m);
    for(int i=0;i<m;i++)
    {
        int w,x,y;
        cin>>w>>x>>y;
        edges[i]={w,{x,y}};
    }
    sort(edges.begin(), edges.end());
    dsu uf(n);
    int mst_w=0;
    for(auto e:edges)
    {
        int w=e.first;
        int x=e.second.first;
        int y=e.second.second;
        if(uf.find_(x)==uf.find_(y))
            continue;
        mst_w+=w;
        uf.union_(x,y);
    }
    cout<<mst_w;
    return 0;
}
