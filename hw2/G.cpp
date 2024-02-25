#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
typedef long long ll;

const int MOD = 1e9 + 7;
const ll INF = 1e18;

/*
 * Algorithm Explanation:
 * 1) First, we make an adjacency list for all cities.
 * 2) Then, for each city we store 4 variables (info[city][i] for 0<=i<=3)
 * i=0 -> initial number of citizens in city
 * i=1 -> maximum number of citizens in any leaf reachable from current city
 * i=2 -> total number of citizens in all cities reachable from current city
 * i=3 -> total number of final cities (leaves) reachable from current city
 * 3) We run dfs on the root node (city where bandit is situated)
 * 4) During the dfs run, we update from the leaves up: info[city][i] for 1<=i<=3
 * using all current data we've acquired.
 * 5) We return info[0][1], which represents the highest amount of citizens of any
 * final city reachable from the first city after the bandit's chase.
 */

/*
 * Time Complexity O(N):
 * dfs takes O(N) time, and for each node we visit we take actions that are all O(1).
 * All in all: O(N)
 */


/*
 * Space Complexity O(N):
 * We use 2 vectors of vectors.
 * Each takes O(N) space, as arr essentially contains all pairs of nodes (O(N)),
 * while info contains 4 parameters for each city (O(N)).
 * All in all: O(N)
 */


void dfs(vector<vector<long long>>& arr, vector<vector<long long>>& info, long long k){ // dfs run
    long long average_citizens;
    double average;
    for (long long p: arr[k]) { // runs dfs on every node using adjacency list
        dfs(arr, info, p); // continues dfs
        info[k][1] = max(info[k][1], info[p][1]); // updates max val to include subtrees
        info[k][2] += info[p][2]; // updates total amount of citizens to include subtrees
        info[k][3] += info[p][3]; // updates total amount of leaves reachable to include subtrees
    }
    info[k][2] += info[k][0]; // total amount of citizens includes initial amount for current city
    if (info[k][3] != 0){ // city not leaf
        average = (double)info[k][2] / (double)info[k][3]; // ceil'ed average amount of citizens in each leaf
        // if distributed equally
        average_citizens = ceil(average);
        info[k][1] = max(average_citizens, info[k][1]);
    }
    else{ // if leaf
        info[k][1] = info[k][0];
        info[k][3] = 1; // marks the city as leaf
    }
}



void solve(vector<vector<long long>>& arr, vector<vector<long long>>& info) {
    dfs(arr, info, 0); // runs dfs from root
    cout << info[0][1] << endl; // returns required answer
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<vector<long long>> arr(N); // adjacency list
    vector<vector<long long>> info(N); // list of info on each city
    long long a;
    long long i = 0;
    while (i<N-1) { // initializes adjacency list with offset since 0-based
        cin >> a;
        arr[a-1].push_back(i+1);
        i++;
    }
    i = 0;
    while (i < N){ // initializes info list
        cin >> a;
        info[i].push_back(a);
        info[i].push_back(0);
        info[i].push_back(0);
        info[i].push_back(0);
        i++;
    }
    solve(arr, info);
    return 0;
}