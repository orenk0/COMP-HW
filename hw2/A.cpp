#include <stdio.h>
#include <iostream>
#include <tuple>
#include <set>
#include <vector>
using namespace std;

/*
 * Algorithm Explanation:
 * 1) First, we make an adjacency list (that includes the other node of the edge, as well as the weight of
 * the edge) to represent the graph as well as initialize a set of xor values we will attempt to find later.
 * 2) We then run a dfs from a in order to see what xor values are attainable from a (not including ones that
 * go through b).
 * 3) Having gathered the relevant good xor values, we then run a similar dfs from b, where in each step we
 * compare the xor we have and see if it appears in the list of good xors. If so, we return YES because
 * using teleport we can achieve the required, otherwise if we haven't found any matching xors during the
 * whole length of the run we return NO.
 */

/*
 * Time Complexity: O(N)
 * We traverse the graph using dfs runs which take O(N) each, while in step of the run we do O(1) work.
 * All in all: O(N).
 */


/*
 * Space Complexity: O(N)
 * Since the graph is a tree, we have N nodes and N-1 edges (which together take O(N) space).
 * The adjacency list takes O(N) space to store the edges and the weights, while the good xors set
 * is bound by N.
 * The rest of the variables take O(1) space.
 * All in all: O(N).
 */



void xors_from_a(vector<tuple<long long, long long>> neighbors[],
                          set<long long>& good_xor_vals, long long current_node,
                          long long parent, long long curr_xor_val, long long b) { // dfs run from a that stores
    // all reachable xor values
    if (current_node == b){
        return;
    }
    else{
        good_xor_vals.insert(curr_xor_val); // adds current xor to list of reachable xor values
        for (auto edge : neighbors[current_node]) {
            long long next = get<0>(edge);
            long long weight = get<1>(edge);
            if (next != parent){
                xors_from_a(neighbors, good_xor_vals, next,
                                     current_node, curr_xor_val ^ weight, b); // continues dfs run
                                     // with updated xor val and parent
            }
        }
    }
}

long long xors_from_b(vector<tuple<long long, long long>> neighbors[],
                              set<long long>& good_xor_vals, long long current_node,
                         long long parent, long long curr_xor_val, long long b) { // dfs run from b
    if (current_node != b){
        if (good_xor_vals.count(curr_xor_val) > 0){ // checks if current xor value is reachable from a
            return 1;
        }
    }
    for (auto edge : neighbors[current_node]) {
        long long next = get<0>(edge);
        long long weight = get<1>(edge);
        if (next != parent) {
            if (xors_from_b(neighbors, good_xor_vals, next, current_node,
                                    weight ^ curr_xor_val, b) == 1) { // continues dfs run while updating
                // relevant parameters
                return 1; // if found valid xor value, return 1 in call stack
            }
        }
    }
    return 0; // no appropriate xor values have been found in whole dfs run
}


void solve(long long a, long long b,
           vector<tuple<long long, long long>> neighbors[]) {
    set<long long> good_xor_vals; // initializes set
    xors_from_a(neighbors, good_xor_vals, a,
                         -1, 0, b); // runs dfs from a
    if (xors_from_b(neighbors, good_xor_vals, b,
                            -1, 0, b) == 1){ // runs dfs from b
        cout << "YES" << endl; // appropriate xor was found from second dfs
    }
    else{
        cout << "NO" << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    long long T = 1;
    cin >> T;
    while (T--) {
        long long n, a, b;
        cin >> n >> a >> b;
        vector<tuple<long long, long long>> neighbors[n]; // initializes adjacency list
        for (long long i = 0; i < n - 1; i++) {
            long long node1, node2, weight;
            cin >> node1 >> node2 >> weight;
            tuple<long long, long long> tup1(node2-1, weight); // tuple includes other node and weight
            neighbors[node1-1].push_back(tup1); // adds tuple to adjacency list
            tuple<long long, long long> tup2(node1-1, weight);
            neighbors[node2-1].push_back(tup2);
        }
        solve(a-1, b-1, neighbors);
    }
    return 0;
}

