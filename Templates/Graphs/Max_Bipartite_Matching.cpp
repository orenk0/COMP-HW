/*
A matching in a Bipartite Graph is a set of the edges chosen in such a way that no two edges share an endpoint.
A maximum matching is a matching of maximum size (maximum number of edges). 
In a maximum matching, if any edge is added to it, it is no longer a matching.
There can be more than one maximum matchings for a given Bipartite Graph.
*/

/*
Hopcroft–Karp Algorithm - Runs in 𝑂(𝑚√𝑛  ) time.
Hungarian Maximum Matching Algorithm -  Runs in 𝑂(𝑚𝑛) - often much faster in practice. 
*/

// Hungarian Maximum Matching Algorithm:


// This code performs maximum bipartite matching.
//
// Running time: O(|E| |V|) -- often much faster in practice
//
// INPUT: w[i][j] = edge between row node i and column node j
// OUTPUT: mr[i] = assignment for row node i, -1 if unassigned
// mc[j] = assignment for column node j, -1 if unassigned
// function returns number of matches made
#include <vector>
using namespace std;
typedef vector<int> VI;
typedef vector<VI> VVI;
bool FindMatch(int i, const VVI &w, VI &mr, VI &mc, VI &seen) {
    for (int j = 0; j < w[i].size(); j++) {
        if (w[i][j] && !seen[j]) {
            seen[j] = true;
            if (mc[j] < 0 || FindMatch(mc[j], w, mr, mc, seen)) {
                mr[i] = j;
                mc[j] = i;
                return true;
            }
        }
    }
    return false;
}
int BipartiteMatching(const VVI &w, VI &mr, VI &mc) {
    mr = VI(w.size(), -1);
    mc = VI(w[0].size(), -1);
    int ct = 0;
    for (int i = 0; i < w.size(); i++) {
        VI seen(w[0].size());
        if (FindMatch(i, w, mr, mc, seen)) ct++;
    }
    return ct;
}
