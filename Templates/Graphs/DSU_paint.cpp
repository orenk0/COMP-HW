/* Compress jumps along a segment / Painting subarrays offline
One common application of the DSU is the following: There is a set of vertices, and each vertex has an outgoing edge to another vertex.
With DSU you can find the end point, to which we get after following all edges from a given starting point, in almost constant time.
A good example of this application is the problem of painting subarrays. 
We have a segment of length L, each element initially has the color 0. 
We have to repaint the subarray [l,r] with the color c for each query (l,r,c). 
At the end we want to find the final color of each cell. We assume that we know all the queries in advance, i.e. the task is offline.
For the solution we can make a DSU, which for each cell stores a link to the next unpainted cell.
Thus initially each cell points to itself. 
After painting one requested repaint of a segment, all cells from that segment will point to the cell after the segment.
Now to solve this problem, we consider the queries in the reverse order: from last to first. 
This way when we execute a query, we only have to paint exactly the unpainted cells in the subarray [l,r]. 
All other cells already contain their final color. 
To quickly iterate over all unpainted cells, we use the DSU. 
We find the left-most unpainted cell inside of a segment, repaint it, and with the pointer we move to the next empty cell to the right.
*/

/* Store additional information for each set
Here we can use the DSU with path compression, but we cannot use union by rank / size (because it is important who becomes the leader after the merge).
Therefore the complexity will be O(logn) per union.
There is one optimization: We can use union by rank, if we store the next unpainted cell in an additional array end[].
Then we can merge two sets into one ranked according to their heuristics, and we obtain the solution in 𝑂(𝛼(𝑛)).

*/

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
    vector<int> end;
    
    dsu(int n)
    {
        parent=vector<int>(n);
        end=vector<int>(n);
        for(int i=0;i<n;i++)
        {
            parent[i]=i;
            end[i]=i;
        }
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
        end[X]=max(end[X],end[Y]);
        return true;
    }
};
 
int main(){
    ios::sync_with_stdio(0);
    int n,q;
    cin>>n>>q;
    dsu uf(n+1);
    vector<int> answer(n,0);
    vector<pair<int, pair<int, int>>> queries(q);
    for(int i=0;i<q;i++)
    {
        cin>>queries[i].first>>queries[i].second.first>>queries[i].second.second;
    }
    
    reverse(queries.begin(), queries.end());
    
    for(int i=0;i<q;i++)
    {
        int l = queries[i].second.first;
        int r = queries[i].second.second;
        int c = queries[i].first;
        for (int v = uf.end[uf.find_(l)]; v <= r; v = uf.end[uf.find_(v)]) {
            answer[v] = c;
            uf.union_(v, v+1);
        }
    }
    for(int i=0;i<n;i++)
    {
        cout<<answer[i]<<" ";
    }
    
        
    return 0;
}
/*
 input:
 10
 5
 1 0 9
 2 8 9
 3 6 8
 4 0 6
 5 6 8
 output:
 4 4 4 4 4 4 5 5 5 2
 */
