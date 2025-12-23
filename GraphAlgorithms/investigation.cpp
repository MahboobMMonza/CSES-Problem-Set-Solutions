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
typedef pair<ll, int> pli;
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

inline bool isSet(const int a, const vector<ll> &vis) {
    return vis[a >> 6] & (1ll << (63 - (a % 64)));
}

inline void toggleBit(const int a, vector<ll> &vis) {
    vis[a >> 6] |= (1ll << (63 - (a % 64)));
}

typedef struct {
    int to;
    ll cost;
    int nxt;
} edge;

int main() {
    /**
     * Apply Dijkstra's from node 1. Keep track of all the required information. Whenever distance to a node is updated,
     * overwrite all the info for that node. If the distance from using the current edge gives the same as the best
     * distance for that node (so far), update that info by adding/minning/maxing the current node's tracked values as
     * required. Then print the info for the given case. Since it is Dijkstra's, once a node is popped from pq, it is
     * the smallest distance it can be, so no more updates to that node will occur.
     */
    fio;
    int n, m, b, a, nbr;
    ll c, ccst;
    cin >> n >> m;
    vector<int> heads(n, -1); // fs: forwards | sc: reverse
    vector<edge> edges(m);
    vector<ll> d(n, INT64_MAX), ways(n, 0), minStops(n, INT64_MAX), maxStops(n, 0);
    vector<ll> vis((n + 63) >> 6, 0);
    pq<pli, vector<pli>, greater<pli>> q; // (w, v)
    fora(i, 0, m) {
        cin >> a >> b >> c;
        a--, b--;
        edges[i].to = b;
        edges[i].cost = c;
        edges[i].nxt = heads[a];
        heads[a] = i;
    }
    // Forwards
    d[0] = 0ll;
    ways[0] = 1;
    minStops[0] = 0;
    maxStops[0] = 0;
    q.emplace(0ll, 0);
    while (!q.empty()) {
        c = q.tp.fs, a = q.tp.sc;
        q.pp;
        if (isSet(a, vis)) {
            continue;
        }
        toggleBit(a, vis);
        if (a == n - 1) {
            break;
        }
        for (int idx = heads[a]; idx != -1; idx = edges[idx].nxt) {
            nbr = edges[idx].to;
            ccst = edges[idx].cost + d[a];
            if (isSet(nbr, vis) || ccst > d[nbr]) {
                continue;
            } else if (ccst == d[nbr]) {
                ways[nbr] = (ways[nbr] + ways[a]) % MOD;
                minStops[nbr] = min(minStops[nbr], minStops[a] + 1);
                maxStops[nbr] = max(maxStops[nbr], maxStops[a] + 1);
            } else {
                ways[nbr] = ways[a];
                minStops[nbr] = (minStops[a] + 1) % MOD;
                maxStops[nbr] = (maxStops[a] + 1) % MOD;
                d[nbr] = ccst;
                q.emplace(ccst, nbr);
            }
        }
    }
    cout << d.back() << ' ' << ways.back() << ' ' << minStops.back() << ' ' << maxStops.back() << edl;
    return 0;
}
