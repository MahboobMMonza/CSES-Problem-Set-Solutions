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
#define fora(i, a, b) for (int i = (a); i < (b); ++i)
#define forae(i, a, b) for (int i = (a); i <= (b); ++i)
#define foras(i, a, b, c) for (int i = (a); i < (b); i += (c))
#define foraes(i, a, b, c) for (int i = (a); i <= (b); i += (c))
#define ford(i, a, b) for (int i = (a); i > (b); --i)
#define forde(i, a, b) for (int i = (a); i >= (b); --i)
#define fords(i, a, b, c) for (int i = (a); i > (b); i -= (c))
#define fordes(i, a, b, c) for (int i = (a); i >= (b); i -= (c))
#define forals(i, a, b, c) for (long long i = (a); i < (b); i += (c))
#define foraels(i, a, b, c) for (long long i = (a); i <= (b); i += (c))
#define fordls(i, a, b, c) for (long long i = (a); i > (b); i -= (c))
#define fordels(i, a, b, c) for (long long i = (a); i >= (b); i -= (c))
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
    /**
     * 2D-PSA. 2PSA{(r1, c1), (r2, c2)} = 2psa[r2, c2] - 2psa[r1 - 1, c2] - 2psa[r2, c2 - 1] + 2psa[r1 - 1, c1 - 1].
     * Think of each as a range from the top left corner to the corner in question; the last addition is necessary
     * because that rectangle is subtracted twice, so we must prevent under-counting. Same applies for when building
     * the grid, since each cell holds the sum from (1, 1) up to (r, c), 1-indexed.
     */
    fio;
    int n, q, r1, c1, r2, c2;
    cin >> n >> q;
    string line;
    vector<vector<int>> psa2d(n + 1, vector<int>(n + 1, 0));
    forae(i, 1, n) {
        cin >> line;
        forae(j, 1, n) {
            psa2d[i][j] = psa2d[i - 1][j] + psa2d[i][j - 1] - psa2d[i - 1][j - 1] + (line[j - 1] == '*');
        }
    }
    while (q--) {
        cin >> r1 >> c1 >> r2 >> c2;
        cout << (psa2d[r2][c2] - psa2d[r1 - 1][c2] - psa2d[r2][c1 - 1] + psa2d[r1 - 1][c1 - 1]) << edl;
    }
    return 0;
}
