#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef pair<ll, ll> pll;
typedef vector<pll> vpll;
/**
 * Used in a stack to handle different types of queries:
 * - As a `pll` for city pair data in 'P' queries.
 * - As an `ll` for identifying roads in 'D' queries.
 */
typedef variant<pll, ll> stackvar;

// A structure to represent a region, which is a connected component in the graph.
struct Region {
    ll parent;      // The representative (leader) of the component.
    ll size;        // Number of cities in this region.
    ll population;  // Total population of this region.
};
typedef vector<Region> vr;

// Data structure to hold queries and the status of roads.
struct QueriesData {
    set<ll> unusableRoads;         // Set of roads that have become unusable.
    stack<stackvar> queriesStack;  // Stack to hold queries for processing in reverse order.
}; 
typedef QueriesData qd;

// Function to read the initial population of each city.
vll readPopulations(ll totalCities) {
    vll initialPop(totalCities + 1);  // Create a vector for populations, 1-indexed.
    for (ll city = 1; city <= totalCities; city++) {
        cin >> initialPop[city];
    }
    return initialPop;
}

// Function to read the list of roads between cities.
vpll readRoads(ll totalRoads) {   
    vpll initialRoads;
    for (ll i = 0; i < totalRoads; i++) {
        ll city1, city2;
        cin >> city1 >> city2;
        initialRoads.push_back({city1, city2});
    }
    return initialRoads;
}

// Function to read queries and modify initial populations or mark roads as unusable.
qd readQueries(ll totalQueries, vll& initialPop) {
    stack<stackvar> queriesStack;
    set<ll> unusableRoads;
    for (ll i = 0; i < totalQueries; i++) {
        char queryType;
        cin >> queryType;
        if (queryType == 'D') {  // Road destruction query.
            ll unusableRoad;
            cin >> unusableRoad;
            queriesStack.push(unusableRoad);
            unusableRoads.insert(unusableRoad);
        } else if (queryType == 'P') {  // Population update query.
            ll city, newPop;
            cin >> city >> newPop;
            queriesStack.push(pll{city, initialPop[city]});
            initialPop[city] = newPop;  // Directly update the population.
        }
    }
    qd queriesData = {unusableRoads, queriesStack};
    return queriesData;
}

// Initialize regions with each city as its own region.
vr initRegions(ll totalCities, const vll& initialPop) {
    vr regions(totalCities + 1);
    for (ll city = 1; city <= totalCities; city++) {
        regions[city] = {city, 1, initialPop[city]};
    }
    return regions;
}

// Find the root of the region to which a city belongs, with path compression.
ll findRegionParent(vr& regions, ll city) {
    if (regions[city].parent != city) {
        regions[city].parent = findRegionParent(regions, regions[city].parent);
    }
    return regions[city].parent;
}

// Merge two regions into one.
void mergeRegions(vr& regions, vll& currPop, pll road) {
    ll city1 = road.first;
    ll city2 = road.second;
    ll region1 = findRegionParent(regions, city1);
    ll region2 = findRegionParent(regions, city2);

    if (region1 != region2) {
        if (regions[region1].size < regions[region2].size)
            swap(region1, region2);

        regions[region2].parent = region1;
        currPop[region1] += currPop[region2];
        regions[region1].size += regions[region2].size;
    }
}

void solve() {
    ll totalCities, totalRoads, totalQueries;
    cin >> totalCities >> totalRoads >> totalQueries;

    vll initialPop = readPopulations(totalCities);
    vpll initialRoads = readRoads(totalRoads);
    qd queriesData = readQueries(totalQueries, initialPop);

    vll currPop(initialPop);  // Current population, initially same as initial population.

    vr regions = initRegions(totalCities, initialPop);

    set<ll> unusableRoads = queriesData.unusableRoads;
    for (ll roadNum = 1; roadNum <= totalRoads; roadNum++) {
        if (unusableRoads.find(roadNum) == unusableRoads.end()) {  // Merge regions if road is still usable.
            pll road = initialRoads[roadNum - 1];
            mergeRegions(regions, currPop, road);
        }
    }

    priority_queue<pll> cityPopMaxPQ;  // Max-heap to find the most populated region.
    for (ll city = 1; city <= totalCities; city++) {
        if (findRegionParent(regions, city) == city) {  // Consider only region roots.
            cityPopMaxPQ.push({currPop[city], city});
        }
    }

    vll mostPopRegions;
    mostPopRegions.push_back(cityPopMaxPQ.top().first);  // Record the max population region after initial setup.

// Initialize a local stack from the collected query data.
stack<stackvar> queriesStack = queriesData.queriesStack;

while (!queriesStack.empty()) {
    stackvar top = queriesStack.top();

    // Determine if the top query is a 'D' type (road destruction).
    if (auto unusableRoadPointer = get_if<ll>(&top)) {
        ll unusableRoad = *unusableRoadPointer;
        pll road = initialRoads[unusableRoad - 1]; // Convert 1-based index to 0-based.
        
        // Merge regions based on the currently usable road.
        mergeRegions(regions, currPop, road);
        cityPopMaxPQ.push({currPop[findRegionParent(regions, road.first)], findRegionParent(regions, road.first)});
    }
    // Check if the query is a 'P' type (population update).
    else if (auto cityNewPopPointer = get_if<pll>(&top)) {
        pll cityNewPop = *cityNewPopPointer;
        ll city = cityNewPop.first;
        ll newPop = cityNewPop.second;

        // Update the population of the city's region and correct the total population.
        currPop[findRegionParent(regions, city)] += newPop - initialPop[city];
        cityPopMaxPQ.push({currPop[findRegionParent(regions, city)], findRegionParent(regions, city)});
        initialPop[city] = newPop;
    }

    // Maintain the priority queue to ensure it only contains valid maximum values.
    while (!cityPopMaxPQ.empty() && currPop[findRegionParent(regions, cityPopMaxPQ.top().second)] != cityPopMaxPQ.top().first) {
        cityPopMaxPQ.pop(); // Remove invalid entries from the priority queue.
    }

    // Record the largest population region after processing the current query.
    mostPopRegions.push_back(cityPopMaxPQ.top().first);

    // Remove the processed query from the stack.
    queriesStack.pop();
}

    // Remove the last element from the vector (which is the initial setup population value)
    mostPopRegions.pop_back();

    // Reverse the modified vector (to match the original order of queries)
    reverse(mostPopRegions.begin(), mostPopRegions.end());

    for (ll pop : mostPopRegions) {
        cout << pop << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}


/**
 * Algorithm Explanation:
 * - The algorithm addresses two types of queries within a dynamic network of cities connected by bidirectional roads:
 *   - 'D' (road destruction) queries: Roads are marked as unusable, which may merge regions if alternate paths exist.
 *   - 'P' (population updates) queries: Updates the population of individual cities and adjusts the total for the region.
 * - A Union-Find structure is utilized to manage connected components ("Regions"), where each region tracks the total population.
 * - A max-heap is maintained to efficiently identify and report the most populated region following each query.
 * - Queries are processed in reverse order, facilitating the rollback of changes and preserving the network state's integrity as if processed sequentially from the initial setup.
 *
 * Time Complexity:
 * - The setup operations (reading populations and roads) have a complexity of O(N + M), where N is the number of towns and M is the number of roads.
 * - Processing Q queries involves:
 *   - 'D' queries, managed through the union-find structure with path compression, typically O(log* N) per query for union operations.
 *   - 'P' queries, which directly update populations and adjust max-heap in O(log N) for heap operations.
 * - Hence, the overall complexity for handling all queries is O(Q * log* N).
 * - The total time complexity of the algorithm is O((N + M) + Q * log* N), combining input reading and query processing.
 *
 * Space Complexity:
 * - The main data structures include arrays for town populations and region tracking, and adjacency lists for roads, requiring O(N + M) space.
 * - The union-find structure for regions and a max-heap for tracking the largest populations both primarily scale with the number of towns, contributing O(N) space.
 * - Additional space is needed for a stack to manage the reverse processing of queries, with each query potentially storing an index or a population change, leading to O(Q).
 * - Overall, the space complexity of the algorithm is O(N + M + Q), accounting for all towns, roads, and queries.
*/