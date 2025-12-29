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
    int from, to;
    ll cost;
    int fnxt, rnxt;
} edge;

int main() {
    /**
     * Simple application of Dijkstra's from a singular source node to all other nodes, and construction of the
     * reverse graph Dijkstra's from the destination to the source. Then try every single edge, and if traversing to
     * that edge when the cost is halved reduces the cost of the trip, then update the new minimum cost. To calculate
     * the new cost, take the cost of the forward graph from the source node to the "from: node of the edge, add the
     * cost of the reverse graph from the destination to the "to" node of the graph, and add the cost of the edge / 2
     * . The distance of any node in the reverse graph corresponds to the sortest distance to the destination node
     * from that node in the forward graph.
     */
    fio;
    int n, m, b, a, nbr;
    ll c, ccst, ans;
    cin >> n >> m;
    vector<pi> heads(n, {-1, -1}); // fs: forwards | sc: reverse
    vector<edge> edges(m);
    vector<ll> d(n, INT64_MAX), rd(n, INT64_MAX);
    vector<ll> vis((n + 63) >> 6, 0);
    pq<pli, vector<pli>, greater<pli>> q; // (w, v)
    fora(i, 0, m) {
        cin >> a >> b >> c;
        a--, b--;
        edges[i].from = a;
        edges[i].to = b;
        edges[i].cost = c;
        edges[i].fnxt = heads[a].fs;
        edges[i].rnxt = heads[b].sc;
        heads[a].fs = i;
        heads[b].sc = i;
    }
    // Forwards
    d[0] = 0ll;
    q.emplace(0ll, 0);
    while (!q.empty()) {
        c = q.tp.fs, a = q.tp.sc;
        q.pp;
        if (isSet(a, vis)) {
            continue;
        }
        toggleBit(a, vis);
        for (int idx = heads[a].fs; idx != -1; idx = edges[idx].fnxt) {
            nbr = edges[idx].to;
            ccst = edges[idx].cost + d[a];
            if (isSet(nbr, vis) || ccst >= d[nbr]) {
                continue;
            }
            d[nbr] = ccst;
            // assert(d[nbr] >= 0);
            q.emplace(ccst, nbr);
        }
    }
    // Reverse
    fill(vis.begin(), vis.end(), 0);
    rd[n - 1] = 0ll;
    q.emplace(0ll, n - 1);
    while (!q.empty()) {
        c = q.tp.fs, a = q.tp.sc;
        q.pp;
        if (isSet(a, vis)) {
            continue;
        }
        toggleBit(a, vis);
        for (int idx = heads[a].sc; idx != -1; idx = edges[idx].rnxt) {
            nbr = edges[idx].from;
            ccst = edges[idx].cost + rd[a];
            if (isSet(nbr, vis) || ccst >= rd[nbr]) {
                continue;
            }
            rd[nbr] = ccst;
            // assert(rd[nbr] >= 0);
            q.emplace(ccst, nbr);
        }
    }
    ans = INT64_MAX;
    for (int i = 0; i < m; ++i) {
        if (d[edges[i].from] == INT64_MAX || rd[edges[i].to] == INT64_MAX) {
            continue;
        }
        ans = min(ans, d[edges[i].from] + (edges[i].cost / 2ll) + rd[edges[i].to]);
    }
    cout << ans << edl;
    return 0;
}
