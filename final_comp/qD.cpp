#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using PLL = pair<long long, long long>;
ll INF = 1000000000000000000;


ll n, m;
vector<vector<pair<ll, ll>>> wg;
ll a, b, price;

vector<ll> dist;
vector<ll> dad;

//unordered_map<ll, ll> edges;


void fast_dijkstra(vector<ll>& sources) {
    dist=vector<ll>(2*n,INF);
    dad=vector<ll>(2*n, -1);
    //min-heap
    priority_queue<PLL, vector<PLL>, greater<PLL> > Q;
    for (ll s:sources) {
        Q.push(make_pair(0, s)); dist[s] = 0;
    }
    while (!Q.empty()) {
        PLL p = Q.top(); Q.pop(); ll here = p.second;
        if (dist[here] != p.first) continue;// we just left it in Q until now    instead of delete when we updated dist[here].
        for (auto it : wg[here]) {
            ll it_index=it.first;
            ll it_w=it.second;
            if (dist[here] + it_w < dist[it_index]) { 
                dist[it_index] = dist[here] + it_w;
                dad[it_index] = here;
                Q.push(make_pair(dist[it_index], it_index));
            }
      }
   }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    wg = vector<vector<pair<ll, ll>>> (2*n);
    dad = vector<ll>(2*n);
    dist = vector<ll>(2*n);

    for(ll i=0;i<m;i++)
    {
        cin >> a >> b >> price;
        wg[a-1].push_back({b-1,price});
        wg[n+(a-1)].push_back({n+(b-1),price});
        wg[a-1].push_back({n+(b-1),price/2});
    }
   
    vector <ll> source={0};
    fast_dijkstra(source);
    cout << dist[2*n-1] << endl;
    return 0;
}