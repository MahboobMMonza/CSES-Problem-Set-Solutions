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
    int to;
    int nxt;

    edge() = default;

    edge(const int to, const int nxt) : to(to), nxt(nxt) {
    }
} edge;

enum class Stage {
    COMPLETE,
    VISIT
};

st<int> hierholzerDirected(const int start, vector<int> &heads, const vector<edge> &edges) {
    st<int> path;
    st<int> calls;
    calls.emplace(start);
    while (!calls.empty()) {
        const auto cur = calls.tp;
        // Find next untraversed edge
        int &edge_idx = heads[cur];
        // All edges exhausted, we don't need to come back here again. Add to path.
        if (edge_idx == -1) {
            path.ps(cur);
            calls.pp;
            continue;
        }
        // Mark this edge traversed and visit the neighbour, and move the edge (slight optimization).
        // We still need to come back to this node and continue checking the rest of its neighbours, so don't pop it
        // from the stack.
        const int nbr = edges[edge_idx].to;
        edge_idx = edges[edge_idx].nxt;
        calls.ps(nbr);
    }
    return path;
}

void forwardDFS(const int a, const vector<int> &heads, const vector<edge> &edges, BitVector &vis, st<int> &order) {
    st<tuple<int, Stage>> calls;
    calls.emplace(a, Stage::VISIT);
    while (!calls.empty()) {
        const auto cur = get<0>(calls.tp);
        const auto stg = get<1>(calls.tp);
        calls.pp;
        if (stg == Stage::COMPLETE) {
            order.ps(cur);
            continue;
        }
        if (vis.get(cur)) continue;
        calls.emplace(cur, Stage::COMPLETE);
        vis.set(cur);
        for (auto i = heads[cur]; i != -1; i = edges[i].nxt) {
            const auto nbr = edges[i].to;
            if (vis.get(nbr)) continue;
            calls.emplace(nbr, Stage::VISIT);
        }
    }
}

void reverseDFS(const int a, const int idx, const vector<int> &heads, const vector<edge> &edges, BitVector &vis,
    vector<int> &comp) {
    st<int> calls;
    vis.set(a);
    calls.ps(a);
    while (!calls.empty()) {
        const auto cur = calls.tp;
        calls.pp;
        comp[cur] = idx;
        for (auto i = heads[cur]; i != -1; i = edges[i].nxt) {
            const auto nbr = edges[i].to;
            if (vis.get(nbr)) continue;
            vis.set(nbr);
            calls.ps(nbr);
        }
    }
}

int main() {
    /**
     * Construct an Eulerian path from the start node to the end node, but first validate if the conditions of
     * existence are met:
     *      1. All nodes with edges belong to the same connected component.
     *      2. The start node has one more outbound edge than inbound edge, the end node has one more inbound edge
     *         than outbound edge, and all other edges have the same number of inbound and outbound edges.
     *
     * Use SCC algorithm and indegree/outdegree counters to validate, then run Hierholzer's algorithm. In order to
     * validate the condition that all edges are in the same component, add a fake edge from the last node to the
     * start node, then run Kosaraju's. "Remove" this edge after the algorithm is done. This is done by moving the
     * head of the last node to the next node in our graph representation.
     *
     * Use Hierholzer's algorithm to construct the path, and record the order of nodes visited, pushing to a stack.
     * To simulate backtracking non-recursively, globally track the next edge to visit using the heads array by
     * moving the tracker to the next edge after the current one is used. If the edge points to our node again, just
     * add the edge value to the queue and go to the next edge instead of adding the same node to the call stack.
     */
    fio;
    size_t n, m;
    cin >> n >> m;
    vector<edge> edges(m + 1), rev_edges(m + 1);
    vector<int> heads(n, -1), rev_heads(n, -1), indeg(n, 0), outdeg(n, 0), comp(n, -1);
    st<int> order;
    int comp_idx = 0;
    BitVector vis(n), rev_vis(n);
    foraz(i, 0, m) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        edges[i].to = b;
        edges[i].nxt = heads[a];
        heads[a] = static_cast<int>(i);
        indeg[b]++;
        outdeg[a]++;
        rev_edges[i].to = a;
        rev_edges[i].nxt = rev_heads[b];
        rev_heads[b] = static_cast<int>(i);
    }
    // Condition for an Euler path starting at first level and ending at last level
    if (outdeg[0] - indeg[0] != 1 || indeg[n - 1] - outdeg[n - 1] != 1) {
        cout << "IMPOSSIBLE" << edl;
        return 0;
    }
    // All edges must be in the same connected component, so adding an edge from last -> first level should thus make
    // the graph a single connected component
    edges[m].to = 0;
    edges[m].nxt = heads[n - 1];
    heads[n - 1] = static_cast<int>(m);
    rev_edges[m].to = static_cast<int>(n - 1);
    rev_edges[m].nxt = rev_heads[0];
    rev_heads[0] = static_cast<int>(m);
    indeg[0]++;
    outdeg[n - 1]++;
    forwardDFS(0, heads, edges, vis, order);
    reverseDFS(order.tp, comp_idx++, rev_heads, rev_edges, rev_vis, comp);
    foraz(i, 0, n) {
        // If the current node has an edge, but it is not in the same component as the first node, then Euler path
        // impossible
        if (comp[i] == -1 && heads[i] != -1 || indeg[i] != outdeg[i]) {
            cout << "IMPOSSIBLE" << edl;
            return 0;
        }
    }
    heads[n - 1] = edges[heads[n - 1]].nxt;
    auto path = hierholzerDirected(0, heads, edges);
    while (!path.empty()) {
        cout << path.tp + 1 << ' ';
        path.pp;
    }
    cout << edl;
    return 0;
}
