#include <bits/stdc++.h>
using namespace std;

// Define the maximum number of employees, considering the constraints.
const int MAX_EMPLOYEES = 5001;
// Create adjacency lists to hold direct precedence and inverse precedence relations.
vector<int> directPrecedenceGraph[MAX_EMPLOYEES], inversePrecedenceGraph[MAX_EMPLOYEES];
// Array to keep track of visited nodes in DFS, initialized to 0.
int visited[MAX_EMPLOYEES] = {}, currentVisitId = 0;

// Performs a DFS in the precedence graph to calculate the number of employees
// directly or indirectly superior or inferior to the given employee.
int DFS(int employee, vector<int> graph[]) {
    // If the employee has already been visited in this DFS pass, return 0 to avoid cycles.
    if (visited[employee] == currentVisitId) return 0;
    // Mark the current employee as visited.
    visited[employee] = currentVisitId;
    // Start with a count of 1 for the current employee.
    int count = 1;
    // Recursively visit all directly connected employees (either superiors or inferiors).
    for (auto connectedEmployee : graph[employee])
        count += DFS(connectedEmployee, graph);
    return count;
}

// Solves the promotion eligibility problem by calculating the number of guaranteed promotions
// at both the lower and upper bounds of promotions, as well as those with no promotion chance.
void solve(int promotionLowerBound, int promotionUpperBound, int numberOfEmployees, int numberOfPrecedenceRules) {
    int superior, inferior;
    // Clear the adjacency lists for a new test case.
    for (int i = 0; i < numberOfEmployees; i++) {
        directPrecedenceGraph[i].clear();
        inversePrecedenceGraph[i].clear();
    }

    // Read the precedence rules and build the precedence graphs.
    for (int i = 0; i < numberOfPrecedenceRules; i++) {
        cin >> superior >> inferior;
        directPrecedenceGraph[superior].push_back(inferior);
        inversePrecedenceGraph[inferior].push_back(superior);
    }

    // Variables to count guaranteed promotions and no-promotion chances.
    int guaranteedPromotionsLowerBound = 0, guaranteedPromotionsUpperBound = 0, noPromotionChance = 0;
    for (int i = 0; i < numberOfEmployees; i++) {
        currentVisitId++;
        // Calculate how difficult it is to promote this employee based on direct precedences.
        int promotionDifficulty = numberOfEmployees - DFS(i, directPrecedenceGraph) + 1;
        currentVisitId++;
        // Calculate how many employees are either equal or superior to this employee.
        int promotionOpportunity = DFS(i, inversePrecedenceGraph);
        // Update counts based on promotion difficulty and opportunity.
        if (promotionDifficulty <= promotionLowerBound) guaranteedPromotionsLowerBound++;
        if (promotionDifficulty <= promotionUpperBound) guaranteedPromotionsUpperBound++;
        if (promotionOpportunity > promotionUpperBound) noPromotionChance++;
    }
    // Output the results for this test case.
    cout << guaranteedPromotionsLowerBound << endl << guaranteedPromotionsUpperBound << endl << noPromotionChance << endl;
}

int main() {
    int promotionLowerBound, promotionUpperBound, numberOfEmployees, numberOfPrecedenceRules;
    // Read input until EOF.
    while (cin >> promotionLowerBound >> promotionUpperBound >> numberOfEmployees >> numberOfPrecedenceRules) {
        solve(promotionLowerBound, promotionUpperBound, numberOfEmployees, numberOfPrecedenceRules);
    }
    return 0;
}


/**
 * Algorithm Explanation:
 * - The solution models the problem using a directed graph where nodes represent employees and edges signify precedence. 
 * - We determine promotion eligibility within a specified range using DFS to explore direct and inverse precedence.
 * - The algorithm computes:
 *   1. Promotion Difficulty: The challenge of promoting an employee, indicated by the reachability in the direct graph.
 *   2. Promotion Opportunity: The potential for promotion, reflected by reachability in the inverse graph.
 * - These metrics help identify guaranteed promotions and those with no chance of promotion within the specified interval.
 * - Guaranteed promotions are flagged if the difficulty is within the lower bound and opportunities within the upper bound.
 * - No promotion chances are noted when the opportunity score exceeds the upper bound, indicating too many superior/equal employees.
 *
 * Complexity Analysis:
 * - Time Complexity: O(E * (E + P)), with E representing employees and P the precedence relations.
 *   This accounts for DFS traversals for each employee in both graphs.
 * - Space Complexity: O(E + P), due to storage of graph structures for all employees and precedence relations.
 */
