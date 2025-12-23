#include <bits/stdc++.h>

using namespace std;

#define fs first
#define fio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
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
#define fora(i, a, b, c) for (int i = (a); i < (b); i += (c))
#define forae(i, a, b, c) for (int i = (a); i <= (b); i += (c))
#define ford(i, a, b, c) for (int i = (a); i > (b); i -= (c))
#define forde(i, a, b, c) for (int i = (a); i >= (b); i -= (c))
#define foral(i, a, b, c) for (long long i = (a); i < (b); i += (c))
#define forael(i, a, b, c) for (long long i = (a); i <= (b); i += (c))
#define fordl(i, a, b, c) for (long long i = (a); i > (b); i -= (c))
#define fordel(i, a, b, c) for (long long i = (a); i >= (b); i -= (c))
#define MOD (int) (1e9 + 7)

typedef unsigned long long ull;
typedef unsigned int uint;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, ll> pil;
typedef pair<ll, ll> pl;
typedef pair<ull, ull> pull;
typedef pair<int, pi> pii;
typedef pair<ll, pl> pll;
typedef pair<pi, pi> ppi;
typedef pair<char, int> pci;

inline ll mulMod(ll x, ll y, ll m = LONG_LONG_MAX) {
    x %= m;
    ll res = 0;
    while (y) {
        if (y & 1) res = (res + x) % m;
        if (res < 0) res += m;
        x = (x << 1) % m;
        y >>= 1;
    }
    return res % m;
}

inline ll logPow(ll x, ll y, ll m = LONG_LONG_MAX) {
    x %= m;
    ll res = 1;
    while (y) {
        if (y & 1) res = mulMod(res, x, m);
        x = mulMod(x, x, m);
        y >>= 1;
    }
    return res % m;
}

inline ll fsLogPow(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y & 1) res *= x;
        x *= x;
        y >>= 1;
    }
    return res;
}

inline ll pLogPow(ll x, ll y, ll m = 9223372036854775783) { return logPow(x, y % (m - 1), m); }

int main() {
    fio;
    int height, width;
    cin >> height >> width;
    // Always let the height be smaller than the width (better for caching)
    if (height > width) {
        swap(height, width);
    } else if (height == width) {
        // If the dimensions are already square, no cuts needed
        cout << 0 << edl;
        return 0;
    }
    vector<vector<int>> cuts(height + 1, vector<int>(width + 1, 0));
    // When you have a 1 x w rectangle, best you can do is cut it into 1 x 1 squares (base case)
    forae(i, 1, width, 1) {
        cuts[1][i] = i - 1;
    }
    // Notice that for a rectangle, we can cut it parallel to h along the width at int values k in range [1, w - 1]
    // At each cut, we are left with a rectangle that is h x k, and another that is h x (w - k). Also notice that the
    // Rectangles are symmetric after k surpasses w / 2, so we only really need to consider k in range [i, w / 2].

    // Similarly, we can cut along the height for values of k in range [1, h / 2]. Finally, note that the answer for a
    // p x q rectangle is the same as a q x p rectangle, since it can be rotated 90-degrees without changing any
    // properties. So, we can choose min(p, q) for height and max(p, q) for width, since this value is already computed
    // in bottom-up approach. Time complexity is O(n^3), which is ok since h x w is at most 500^2.
    forae(i, 2, height, 1) {
        forae(j, 1, width, 1) {
            if (i == j) {
                continue;
            } else if (j == 1) {
                cuts[i][j] = cuts[j][i];
                continue;
            }
            cuts[i][j] = INT32_MAX - 1; // Just for safety
            forae(k, 1, j / 2, 1) {
                cuts[i][j] = min(cuts[i][j], 1 + cuts[min(i, k)][max(i, k)] + cuts[min(i, j - k)][max(i, j - k)]);
            }
            forae(k, 1, i / 2, 1) {
                cuts[i][j] = min(cuts[i][j], 1 + cuts[min(j, k)][max(j, k)] + cuts[min(j, i - k)][max(j, i - k)]);
            }
        }
    }
    cout << cuts[height][width] << edl;
    return 0;
}
