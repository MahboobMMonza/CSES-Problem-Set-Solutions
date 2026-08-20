#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

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
#define foraz(i, a, b) for (size_t i = (a); i < (b); ++i)
#define foraez(i, a, b) for (size_t i = (a); i <= (b); ++i)
#define fordz(i, a, b) for (size_t i = (a); i > (b); --i)
#define fordez(i, a, b) for (size_t i = (a); i >= (b); --i)
#define ford0z(i, a, b) for (size_t i = (a); i < (b); --i)
#define forazs(i, a, b, c) for (size_t i = (a); i < (b); i += (c))
#define foraezs(i, a, b, c) for (size_t i = (a); i <= (b); i += (c))
#define fordzs(i, a, b, c) for (size_t i = (a); i > (b); i -= (c))
#define fordezs(i, a, b, c) for (size_t i = (a); i >= (b); i -= (c))
#define ford0zs(i, a, b, c) for (size_t i = (a); i < (b); i -= (c))
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

struct custom_hash {
    static ull splitmix64(ull x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    ull operator()(const ull x) const {
        static const ull FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    size_t operator()(const pi &x) const {
        static const size_t FIXED_RANDOM = static_cast<size_t>(chrono::steady_clock::now().time_since_epoch().count());
        auto packed = (static_cast<ull>(x.fs) << 32) | static_cast<ull>(x.sc);
        return splitmix64(packed + FIXED_RANDOM);
    }
};

inline ll mulMod(ll x, ll y, ll m = numeric_limits<ll>::max()) {
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

inline ll logPow(ll x, ll y, ll m = numeric_limits<ll>::max()) {
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

class BitVector {
public:
    explicit BitVector(const size_t n) : v((n + 63) >> 6, 0) {
    };

    ~BitVector() = default;

    bool get(const size_t i) const {
        return v[i >> 6] & (1ull << (i & 63));
    }

    void set(const size_t i) {
        v[i >> 6] |= 1ull << (i & 63);
    }

    void clear(const size_t i) {
        v[i >> 6] &= ~(1ull << (i & 63));
    }

    void toggle(const size_t i) {
        v[i >> 6] ^= 1ull << (i & 63);
    }

    void clearAll() {
        fill(v.begin(), v.end(), 0);
    }

    static string to_string(const BitVector &bv) {
        ostringstream ss;
        for (const auto &x: bv.v) {
            bitset<64> bits(x);
            string seq = bits.to_string();
            reverse(seq.begin(), seq.end());
            ss << seq;
        }
        return ss.str();
    }

private:
    vector<ull> v;
};

typedef struct edge {
    int to = -1;
    int nxt = -1;
    int flow = 0;
    int max_capacity = 0;

    edge() = default;

    edge(const int _to, const int _nxt, const int _flow, const int _cap) : to(_to), nxt(_nxt), flow(_flow), max_capacity
                                                                           (_cap) {
    }

    int getCapacity() const {
        return max_capacity - flow;
    }
} edge;

bool bfs(const vector<int> &heads, vector<int> &level, const vector<edge> &edges) {
    qu<int> q;
    level[0] = 0;
    q.ps(0);
    while (!q.empty()) {
        const auto cur = q.fr;
        q.pp;
        for (int i = heads[cur]; i != -1; i = edges[i].nxt) {
            const auto &e = edges[i];
            if (e.getCapacity() == 0 || level[e.to] != -1) continue;
            level[e.to] = level[cur] + 1;
            q.ps(e.to);
        }
    }
    return level.bk != -1;
}

ll dfs(vector<int> &heads, vector<edge> &edges, vector<int> &level, BitVector &searching) {
    st<size_t> calls;
    st<pi> caps;
    int cap = INT_MAX;
    bool found = false;
    const auto n = heads.size();
    calls.ps(0);
    while (!calls.empty()) {
        const auto cur = calls.tp;
        int &edge_idx = heads[cur];
        if (cur == n - 1) {
            found = true;
            cap = caps.tp.sc;
            calls.pp;
            continue;
        }
        if (found) {
            edges[edge_idx].flow += cap;
            edges[edge_idx ^ 1].flow -= cap;
            calls.pp;
            continue;
        }
        while (!caps.empty() && caps.tp.fs >= level[cur]) caps.pp;
        if (edge_idx != -1 && searching.get(cur)) edge_idx = edges[edge_idx].nxt;
        searching.set(cur);
        while (edge_idx != -1 && (edges[edge_idx].getCapacity() == 0 || level[edges[edge_idx].to] <= level[cur])) {
            edge_idx = edges[edge_idx].nxt;
        }
        if (edge_idx == -1) {
            // No paths out from this node, mark as dead end to avoid traversal next time
            calls.pp;
            level[cur] = -1;
            continue;
        }
        const auto &e = edges[edge_idx];
        if (caps.empty() || caps.tp.sc > e.getCapacity()) caps.emplace(level[cur], e.getCapacity());
        calls.ps(static_cast<size_t>(e.to));
    }
    return found ? cap : 0;
}

ull getFlow(const vector<int> &heads, vector<int> &trav_heads, vector<int> &level, vector<edge> &edges, BitVector
          &searching) {
    ull max_flow = 0;
    while (bfs(heads, level, edges)) {
        copy(heads.begin(), heads.end(), trav_heads.begin());
        for (ll flo = dfs(trav_heads, edges, level, searching); flo != 0; flo = dfs(trav_heads, edges, level,
                                                                              searching)) {
            max_flow += flo;
            searching.clearAll();
        }
        fill(level.begin(), level.end(), -1);
        searching.clearAll();
    }
    return max_flow;
}

vector<pi> getCut(const vector<int> &heads, const vector<edge>& edges, BitVector &vis) {
    qu<int> q;
    vector<int> reach;
    vector<pi> cut;
    reach.reserve(heads.size());
    q.ps(0);
    vis.set(0);
    reach.pb(0);
    // Find all reachable nodes in residual graph
    while (!q.empty()) {
        const auto cur = q.fr;
        q.pp;
        for (auto i = heads[cur]; i != -1; i = edges[i].nxt) {
            const auto &e = edges[i];
            if (e.getCapacity() == 0 || vis.get(e.to)) continue;
            vis.set(e.to);
            reach.pb(e.to);
            q.ps(e.to);
        }
    }
    // Find all filled ORIGINAL edges. Original edges will have even index values based on how they were mapped
    for (const auto& cur : reach) {
        for (auto i = heads[cur]; i != -1; i = edges[i].nxt) {
            const auto &e = edges[i];
            // Skip unfilled or reverse edges
            if (i & 1 || e.getCapacity() > 0 || vis.get(e.to)) continue;
            cut.eb(cur, e.to);
        }
    }
    return cut;
}

int main() {
    /**
     * Implement Dinic's again (see Download Speed problem for more implementation details). To represent bidirectional
     * edges, use two forward/reverse edge pairs for each direction. Just makes life easier. As a result, each edge in
     * the original graph creates 4 edges in the residual graph:
     *  - fwd: regular forward direction of graph
     *  - fwd_rev: residual reverse of forward direction
     *  - bck: regular backwards direction of graph
     *  - bck_rev: residual reverse of backward direction
     *
     * This will not cause an issue with Dinic's of using both forward and backward edges because of the BFS heuristic
     * Dinic's establishes.
     *
     * Once max flow is found, use graph search to find set of reachable vertices in the residual graph, and then
     * the cutting edges (the roads that need to be blocked) are all max-capacity edges emerging from this set of
     * vertices which are found in the ORIGINAL graph.
     *
     * Based on graph design, original edges have even indices. BFS is used to get a set of all reachable vertices,
     * then for each vertex, iterate all edges which are in the original graph, and if the capacity is 0 AND the
     * opposite node is not part of the reachable set, then the edge is part of the minimum cut, so add it to the
     * list to be displayed.
     */
    fio;
    size_t n, m;
    cin >> n >> m;
    vector<int> heads(n, -1), trav_heads(n), level(n, -1);
    vector<edge> edges(4 * m);
    BitVector searching(n);
    // Read edges
    foraz(i, 0, m) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        const auto fwd_idx = 4 * i;
        const auto fwd_rev_idx = fwd_idx ^ 1;
        const auto bck_idx = fwd_idx + 2;
        const auto bck_rev_idx = bck_idx ^ 1;
        // Forwards pair
        edges[fwd_idx].to = b;
        edges[fwd_idx].nxt = heads[a];
        edges[fwd_idx].max_capacity = 1;
        heads[a] = static_cast<int>(fwd_idx);
        edges[fwd_rev_idx].to = a;
        edges[fwd_rev_idx].nxt = heads[b];
        heads[b] = static_cast<int>(fwd_rev_idx);
        edges[fwd_rev_idx].max_capacity = 1;
        edges[fwd_rev_idx].flow = 1;
        // Backwards pair
        edges[bck_idx].to = a;
        edges[bck_idx].nxt = heads[b];
        edges[bck_idx].max_capacity = 1;
        heads[b] = static_cast<int>(bck_idx);
        edges[bck_rev_idx].to = b;
        edges[bck_rev_idx].nxt = heads[a];
        heads[a] = static_cast<int>(bck_rev_idx);
        edges[bck_rev_idx].max_capacity = 1;
        edges[bck_rev_idx].flow = 1;
    }
    auto paths = getFlow(heads, trav_heads, level, edges, searching);
    auto cut = getCut(heads, edges, searching);
    cout << paths << edl;
    for (const auto& e : cut) {
        cout << e.fs + 1 << ' ' << e.sc + 1 << edl;
    }
    return 0;
}
