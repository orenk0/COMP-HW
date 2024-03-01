#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> initGraph(int n) {
    vector<vector<int>> g = vector<vector<int>> (n);
    for(int i=0; i<(n-1); i++) {
        int x,y;
        cin >> x >> y;
        x--;
        y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    return g;
}

double alteredDfs(vector<vector<int>>& g, vector<bool>& visited, int curr) {
    double expectedLength = 0.0;
    double unvisitedCount = 0.0;
    visited[curr] = true;
    for (int neighbour : g[curr]) {
        if (!visited[neighbour]) {
            unvisitedCount++;
        }
    }
    if (unvisitedCount == 0.0) {
        return 0.0;
    }
    for (int neighbour : g[curr]) {
        if(visited[neighbour]) continue;
        expectedLength += (1.0 + alteredDfs(g, visited, neighbour)) / unvisitedCount;
    }
    return expectedLength;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> g = initGraph(n);
    vector<bool> visited = vector<bool>(n,false);
    cout << fixed << setprecision(15) << alteredDfs(g, visited, 0) << endl;

    return 0;
}