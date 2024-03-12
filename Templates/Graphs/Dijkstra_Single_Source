/* Dijkstra - The Dijkstra algorithm solves the single source shortest paths problem in a weighted (directed or not) graph in time O(Elog(V)).

Edge weights are non negative numbers.

Main idea (invariant):

When a vertex V has the smallest distance among all vertices in the set, it will never get a shorter path. 
"Proof”: the distances of the set became only bigger and bigger since there are no negative edges.

 
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
 
typedef long long ll;
using namespace std;
const int INF=100000000;
int n,m;
vector<vector<pair<int, int>>> wg;
vector<int> dist;
 
void dijkstra(int source)
{
    dist=vector<int>(n,INF);
    dist[source]=0;
    set<pair<int, int>> pq;
    pq.insert({dist[source],source});
    while (!pq.empty()) {
        pair<int, int> cur=*pq.begin();
        pq.erase(pq.begin());
        int cur_index=cur.second;
        int cur_dist=cur.first;
        dist[cur_index]=cur_dist;//this is the point we sure it wont get shorter.
        for(auto next: wg[cur_index])
        {
            int next_index=next.first;
            int next_dist=next.second;
            if(cur_dist+next_dist<dist[next_index])
            {
                pair<int, int> next_w_i={dist[next_index],next_index
                };
                if(pq.find(next_w_i)!=pq.end())
                {
                    pq.erase(next_w_i);
                }
                //update path len
                next_w_i.first=cur_dist+next_dist;
                pq.insert(next_w_i);
                //update dist so we will be able to find it next time in pq.
                dist[next_w_i.second]=next_w_i.first;
            }
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin>>n>>m;
    wg=vector<vector<pair<int, int>>> (n);
    
    for(int i=0;i<m;i++)
    {
        int x,y,w;
        cin>>x>>y>>w;
        wg[x].push_back({y,w});
    }
    int source=0;
    dijkstra(source);
    for(int i=0;i<n;i++)
    {
        cout<<"The dist to vertex: "<<i<<" is ";
        if(dist[i]!=INF)
            cout<<dist[i];
        else
            cout<<"INF";
        cout<<endl;
    }
}
/*
 input:
 6 6
 0 1 5
 0 3 6
 1 2 2
 1 4 1
 3 2 0
 3 4 1
 
 output:
 The dist to vertex: 0 is 0
 The dist to vertex: 1 is 5
 The dist to vertex: 2 is 6
 The dist to vertex: 3 is 6
 The dist to vertex: 4 is 6
 The dist to vertex: 5 is INF
 
 */

