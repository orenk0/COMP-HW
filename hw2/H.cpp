//#include <bits/stdc++.h>
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
 * 1) We first initialize an adjacency list based on the input
 * 2) After initializing auxiliary lists, we calculate for each node how many nodes
 * are in its subtree (beginning from root node (node 1)).
 * 3) We then run dfs once from the root in order to in order to calculate the total sum
 * of distances from the original root node.
 * 4) We proceed to store the updated total value as the first place of the answer array.
 * 5) In the final run, we compute the total sum of distances from each node firstly based
 * on the initial total and then from subsequent parent's total.
 * 6) Once the total for a parent has been calculated, the total of its child would be updated
 * using the logic that the child is 1 step closer to all the child's children, but 1 step further
 * from all the rest of the nodes.
 * 7) We then print out the final answer.
 */

/*
 * Time Complexity: O(N)
 * Explanation: We traverse through the tree thrice, each time costing O(N) time.
 * First time in nodeCounter, then in dfs, and lastly in finalRun.
 * In every node we visit, O(1) work is being done.
 * All in all: O(N)
 *
 *
 * Space Complexity: O(N)
 * All of the none single-valued variables are O(N) in size, including the adjacency list,
 * the list that stores the number of nodes in each subtree (each node), and the final answer.
 * All in all: O(N)
 */


int nodeCounter (long long i, long long parent, vector<vector<long long>> &adjacent, vector<long long>& subtree_nodes){ // sums number of
    // nodes under each node, starting from root(node 1)
    for (auto k:adjacent[i]) {
        if (k != parent){
            subtree_nodes[i] += nodeCounter(k, i, adjacent, subtree_nodes); // updates node count
            // of root of subtree for all subtrees
        }
    }
    return subtree_nodes[i] + 1; // includes the parent node
}

void dfs(long long node, long long parent, vector<vector<long long>> &adjacent, long long& total, long long distance){
    total += distance; // we update the total in order to calculate final answer for root node
    for (auto k:adjacent[node]) {
        if (k != parent){
            dfs(k, node, adjacent, total, distance+1); // every dfs entry means we are
            // getting 1 step further away
        }
    }
}

void finalRun(vector<vector<long long>> &adjacent, vector<long long>& subtree_nodes, vector<long long>& ans,
              long long i, long long parent, long long T){
    int nodes_under = 0; // for a node:
    if (parent != -1){ // if not parent:
        for (auto k:adjacent[i]) { // for all adjacent nodes:
            if (k != parent){ // if not parent:
                nodes_under += subtree_nodes[k] +1; // update number of nodes underneath said node
            }
        }
        ans[i] = ans[parent] - 2*nodes_under - 2 + T; // update final answer according to logic stated at top
    }
    for (auto m:adjacent[i]) {
        if (m != parent){
            finalRun(adjacent, subtree_nodes, ans, m, i, T); // we make sure to get to all nodes
        }
    }
}


void solve(int T, vector<vector<long long>> &adjacent) { // See algo description for explanation of each function
    vector<long long> subtree_nodes(T, 0), ans(T, 0);
    long long total = 0;
    nodeCounter(0, -1, adjacent, subtree_nodes);
    dfs(0, -1, adjacent, total, 0);
    ans[0] = total;
    finalRun(adjacent, subtree_nodes, ans, 0, -1, T);
    for (int i = 0; i < T; i++) {
        cout << ans[i] << " ";
    }
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    int i = 0;
    vector<vector<long long>> adjacent(T); // adjacency vector
    while (i<T-1) {
        int a,b;
        cin >> a >> b;
        adjacent[a-1].push_back(b-1); // offset of 1 bc zero-based
        adjacent[b-1].push_back(a-1);
        i++;
    }
    solve(T, adjacent);
    return 0;
}
