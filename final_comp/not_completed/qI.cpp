#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;


struct Edge {
    int city1, city2, original_weight;
    ll adjusted_weight;
};

struct DSU {
    vector<int> parent;
    DSU(int n) : parent(n + 1, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int findParent(int x) {
        return parent[x] == x ? x : parent[x] = findParent(parent[x]);
    }
    void unionVertices(int x, int y) {
        parent[findParent(x)] = findParent(y);
    }
};

vector<Edge> edges;
bool includes_edge_with_at_least_k__original_weight = false;

ll kruskal(int n, int k, bool check_for_k) {
    DSU dsu(n);
    ll total_weight = 0;
    includes_edge_with_at_least_k__original_weight = false;

    for (const auto& edge : edges) {
        if (dsu.findParent(edge.city1) != dsu.findParent(edge.city2)) {
            dsu.unionVertices(edge.city1, edge.city2);
            total_weight += edge.adjusted_weight;
            if (check_for_k && edge.original_weight >= k) {
                includes_edge_with_at_least_k__original_weight = true;
            }
        }
    }

    return total_weight;
}

int main() {
    int t;
    cin >> t;
    vector<ll> results;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        cout << "N: " << n << " M: " << m << " K: " << k << endl;
        edges.clear();
        for (int i = 0; i < m; ++i) {
            int city1, city2, weight;
            cin >> city1 >> city2 >> weight;
            int adjusted_weight = weight >=k ? (weight - k) : 0;
            cout << "City1: " << city1 << " City2: " << city2 << " Weight: " << weight << " Adjusted weight: " << adjusted_weight << endl;
            edges.push_back({city1, city2, weight, adjusted_weight});
        }

        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.adjusted_weight < b.adjusted_weight;
        });

        ll total_weight = kruskal(n, k, true);
        cout << "Flag after first kruskal: " << includes_edge_with_at_least_k__original_weight << endl;

        if (!includes_edge_with_at_least_k__original_weight) {
            int max_weight_below_k = 0;
            for (auto& edge : edges) {
                if (edge.original_weight < k) {
                    max_weight_below_k = max(max_weight_below_k, edge.original_weight);
                }
            }
            for (auto& edge : edges) {
                if (edge.original_weight == max_weight_below_k) {
                    edge.adjusted_weight = k - edge.original_weight;
                } else if (edge.original_weight < k) {
                    edge.adjusted_weight = 0;
                } else {
                    edge.adjusted_weight = INF;
                }
                cout << "City1: " << edge.city1 << " City2: " << edge.city2 << " Weight: " << edge.original_weight << " New adjusted weight: " << edge.adjusted_weight << endl;
            }

            sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
                return a.adjusted_weight < b.adjusted_weight;
            });
            int total_weight_second = kruskal(n, k, false);
            if (total_weight > total_weight_second) {
                total_weight = total_weight_second;
            }
        }

        results.push_back(total_weight);  // Store the result for this test case
    }

    // Print all results
    for (auto result : results) {
        cout << result << endl;
    }

    return 0;
}
