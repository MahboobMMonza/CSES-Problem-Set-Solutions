#include <bits/stdc++.h>

using namespace std;

#define fs first
#define fio ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL)
#define sc second
#define pb push_back
#define eb emplace_back
#define edl '\n'
#define pf push_front
#define ppb pop_back()
#define fr front()
#define bk back()
#define sbf setbuf(stdout, 0)
#define ppf pop_front()
#define tp top()
#define ps push
#define pp pop()
#define fls fflush(stdout)
#define qu queue
#define st stack
#define pq priority_queue
#define fora(i, a, b, c) for (int (i) = (a); (i) < (b); (i) += (c))
#define forae(i, a, b, c) for (int (i) = (a); (i) <= (b); (i) += (c))
#define ford(i, a, b, c) for (int (i) = (a); (i) > (b); (i) -= (c))
#define forde(i, a, b, c) for (int (i) = (a); (i) >= (b); (i) -= (c))
#define dblinf numeric_limits<double>::infinity()

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, ll> pil;
typedef pair<ll, ll> pl;
typedef pair<ull, ull> pull;
typedef pair<int, pi> pii;
typedef pair<ll, pl> pll;
typedef pair<pi, pi> ppi;
typedef pair<double, double> pd;
typedef pair<char, int> pci;

int main() {
    fio;
    ll t, x, y, startingx, startingy, xd, yd;
    cin >> t;
    while (t--) {
        cin >> y >> x;
        // starting x value is odd
        if (x&1) {
            startingx = x * x;
            yd = -1;
        } else {
            startingx = (x - 1) * (x - 1) + 1;
            yd = 1;
        }
        // starting y-value is even
        if ((y - 1)&1) {
            startingy = y * y;
            xd = -1;
        } else {
            startingy = (y - 1) * (y - 1) + 1;
            xd = 1;
        }
        // If either of the values is one, print the opposite starting value
        // Otherwise, start at the value of whichever is bigger between x and y, then traverse down the remaining steps.
        if (x == 1) {
            cout << startingy;
        } else if (y == 1) {
            cout << startingx;
        } else if (x >= y) {
            cout << startingx + (y - 1) * yd;
        } else {
            cout << startingy + (x - 1) * xd;
        }
        cout << edl;
    }
    return 0;
}
