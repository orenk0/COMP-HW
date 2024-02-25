
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
 * In order to calculate the sum of the digits between a and b, we compute the
 * sum of digits from 0 to a and from 0 to b separately, and then subtract
 * the smaller resulting sum (of a) from the larger resulting sum (of b),
 * making sure not to count a's digits twice.
 * We compute the sum of the digits using the following mathematical formula:
 * For each digit place (1s, 10s...) we add to the respective sum:
 *    1) (x / (digit_place * 10)) * 45 * digit_place
 *    2) ((x / digit_place) % 10) * (((x / digit_place) % 10) - 1) / 2 * digit_place
 *    3) ((x / digit_place) % 10) * ((x % digit_place) + 1)
 * where x is either b or a.
 * We then subtract a's digits from a's total sum (to not count it twice), and
 * then we return the difference between b's total sum and a's total sum.
 *
 * Time Complexity: O(log(base10)b)
 * The runtime is dependent on the amount of digits in a and b, such that the
 * overall time complexity is O(log(base10)b), as b >= a.
 * All in all: O(log(base10)b)
 *
 * Space Complexity:
 * All variables use O(1) space.
 * All in all: O(1)
 */

void solve(unsigned long long a, unsigned long long b) {
    unsigned long long digits_a = 1;
    unsigned long long digits_b = 1;
    unsigned long long ans_a = 0;
    unsigned long long ans_b = 0;
    for (unsigned long long i = 1; i <= b; i *= 10) { // count the number of digits in b
        digits_b += 1;
    }
    for (unsigned long long i = 1; i <= a; i *= 10) { // count the number of digits in a
        digits_a += 1;
    }
    digits_a -= 1;
    digits_b -= 1;
    unsigned long long digits_a_copy = digits_a; // save a's digit counter for later
    unsigned long long a_copy = a; // save a's value for later
    unsigned long long digits_place = 1;
    while (digits_b > 0) { // Calculate sum of digits for b ([0, b])
        ans_b += (b/(digits_place*10))*45*digits_place;
        ans_b += ((b/digits_place)%10 * (((b/digits_place)%10) - 1))/2*digits_place;
        ans_b += ((b/digits_place)%10) * ((b%digits_place) + 1);
        digits_place *= 10; // progresses digits place
        digits_b -= 1;
    }
    digits_place = 1;
    while (digits_a > 0) { // Calculate sum of digits for a ([0, a])
        ans_a += (a/(digits_place*10))*45*digits_place;
        ans_a += ((a/digits_place)%10 * (((a/digits_place)%10) - 1))/2*digits_place;
        ans_a += ((a/digits_place)%10) * ((a%digits_place) + 1);
        digits_place *= 10; // progresses digits place
        digits_a -= 1;
    }
    for (unsigned long long e = 0; e < digits_a_copy; e++) { // changes a's sum
        // from [0, a] to [0, a)
        ans_a -= a_copy % 10;
        a_copy -= a_copy % 10;
        a_copy /= 10;
    }
    cout << ans_b - ans_a << endl; // returns [0, b] - [0, a), which is equal to [a, b]
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--) {
        unsigned long long a = 0;
        unsigned long long b = 0;
        cin >> a;
        cin >> b;
        solve(a, b);
    }
    return 0;
}
