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

size_t find(size_t x, vector<size_t> &parent) {
    size_t root = x;
    while (parent[root] != root) {
        root = parent[root];
    }
    while (parent[x] != x) {
        const size_t par = parent[x];
        parent[x] = root;
        x = par;
    }
    return root;
}

bool join(const size_t c1, const size_t c2, vector<size_t> &parent, vector<size_t> &rank) {
    size_t p1 = find(c1, parent), p2 = find(c2, parent);
    if (p1 == p2) {
        return false;
    }
    if (rank[p2] < rank[p1]) swap(p1, p2);
    parent[p1] = p2;
    rank[p2]++;
    return true;
}

bool validateGraph(const vector<size_t> &degree, vector<size_t> &parent) {
    const size_t n = degree.size();
    foraz(i, 0, n) {
        if (degree[i] & 1 || (find(i, parent) != find(0, parent) && degree[i] > 0)) return false;
    }
    return true;
}

st<int> hierholzerBidirectional(const int start, vector<int> &heads, const vector<edge> &edges, BitVector &edgeVis) {
    st<int> path;
    st<int> calls;
    calls.emplace(start);
    while (!calls.empty()) {
        const auto cur = calls.tp;
        // Find next untraversed edge
        int &edge_idx = heads[cur];
        while (edge_idx != -1 && edgeVis.get(edge_idx)) {
            edge_idx = edges[edge_idx].nxt;
        }
        // All edges exhausted, we don't need to come back here again. Add to path.
        if (edge_idx == -1) {
            path.ps(cur);
            calls.pp;
            continue;
        }
        // Mark this edge traversed and visit the neighbour, and move the edge (slight optimization).
        // We still need to come back to this node and continue checking the rest of its neighbours, so don't pop it
        // from the stack.
        edgeVis.set(edge_idx);
        edgeVis.set(edge_idx ^ 1);
        const int nbr = edges[edge_idx].to;
        calls.ps(nbr);
        edge_idx = edges[edge_idx].nxt;
    }
    return path;
}

int main() {
    /**
     * Construct an Eulerian circuit if it exists. First, check if a circuit is possible by using union-find and node
     * degree counts. The conditions are as follows:
     *   1. All nodes with degree > 0 are in the same component.
     *   2. The degree of every node is even.
     *
     * If these conditions cannot be met, then it is IMPOSSIBLE to construct an Eulerian circuit from the first node.
     *
     * Otherwise, use Hierholzer's algorithm to construct the path. The algorithm is as follows:
     *   1. Start at node 1, "recursively" DFS through each unused edge until you find a node that has no more unused
     *      edges. Add this node to the stack and backtrack.
     *   2. When backtracking, whenever we encounter a node that has no more visitable edges, add this node to the
     *      stack. This means that a node can be added to the stack multiple times, and this is expected.
     *   3. It is guaranteed that the last visited node will be the starting node, which will form a circut based on
     *      the property of Eulerian circuits and our checks above.
     *
     * To simulate backtracking non-recursively, globally track the next edge to visit using the heads array by
     * moving the tracker to the next edge after the current one is used. Note that the graph is undirected but we
     * are adding 2 complementary edges in our graph, so we need to mark both the current edge and its complementary
     * edge as visited every time we traverse an edge.
     */
    fio;
    size_t n, m;
    cin >> n >> m;
    vector<size_t> parent(n), rank(n, 0), degree(n, 0);
    vector<int> heads(n, -1); // we will essentially destroy this graph since we only ever traverse graph once
    vector<edge> edges(2 * m);
    BitVector edgeVis(2 * m);
    foraz(i, 0, n) {
        parent[i] = i;
    }
    foraz(i, 0, m) {
        int a, b;
        const int idx = static_cast<int>(2 * i);
        cin >> a >> b;
        a--, b--;
        join(a, b, parent, rank);
        degree[a]++;
        degree[b]++;
        edges[idx].to = b;
        edges[idx].nxt = heads[a];
        heads[a] = idx;
        edges[idx + 1].to = a;
        edges[idx + 1].nxt = heads[b];
        heads[b] = idx + 1;
    }
    if (!validateGraph(degree, parent)) {
        cout << "IMPOSSIBLE" << edl;
        return 0;
    }
    auto path = hierholzerBidirectional(0, heads, edges, edgeVis);
    cout << path.tp + 1;
    path.pp;
    while (!path.empty()) {
        cout << ' ' << path.tp + 1;
        path.pp;
    }
    cout << edl;
    return 0;
}
