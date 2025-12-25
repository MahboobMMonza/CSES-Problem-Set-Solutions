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
} edge;

enum class Stage {
    COMPLETE,
    VISIT
};

void forwardDFS(const int a, const vector<int> &heads, const vector<edge> &edges, BitVector &vis, st<int> &order) {
    st<pair<int, Stage>> calls;
    calls.emplace(a, Stage::VISIT);
    while (!calls.empty()) {
        auto cur = calls.tp.fs;
        const auto com = calls.tp.sc;
        calls.pp;
        if (com == Stage::COMPLETE) {
            order.ps(cur);
            continue;
        }
        if (vis.get(cur)) continue;
        calls.emplace(cur, Stage::COMPLETE);
        vis.set(cur);
        for (int i = heads[cur]; i != -1; i = edges[i].nxt) {
            auto nbr = edges[i].to;
            if (vis.get(nbr)) continue;
            calls.emplace(nbr, Stage::VISIT);
        }
    }
}

void reverseDFS(const int a, const int idx, const vector<int> &heads, const vector<edge> &edges, BitVector &vis,
    vector<int> &comp) {
    st<int> calls;
    vis.set(a);
    calls.emplace(a);
    while (!calls.empty()) {
        const auto cur = calls.tp;
        comp[cur] = idx;
        calls.pp;
        for (int i = heads[cur]; i != -1; i = edges[i].nxt) {
            auto nbr = edges[i].to;
            if (vis.get(nbr)) continue;
            vis.set(nbr);
            calls.emplace(nbr);
        }
    }
}

int main() {
    /**
     * Implement any strongly connected components algorithm (SCC) that runs in O(V + E). Do Kosaraju's since it is
     * much easier to implement iteratively (almost like simple top-sort DFS).
     *
     * If there is only one SCC, then the entire graph is connected, otherwise there are multiple SCCs, meaning that
     * depending on a given direction, the root of one SCC is not reachable from the root of another SCC. Note that
     * Kosaraju's algorithm uses a reverse graph in the second phase to assign the components. Each edge present in the
     * reverse graph is not present in the original graph if two nodes are not cyclically connected. That means for
     * two separate components, if there is a reverse edge from A -> B, then there is no edge from A -> B in the
     * original graph. This means that for some SCC A, if another SCC B is processed/assigned after A, then there
     * does not exist any edge between any node in B to any node in A. PROOF: In the reverse graph, when component A is
     * assigned, no nodes in component B are visited. When component B is assigned, either (1) there did not exist any
     * reverse edge between any node in component B to any node in component A, or (2) there did exist a reverse edge
     * between some node in component B to one in component A. In case (1), components B and A are completely disjoint,
     * so it is impossible to visit between any node in B and any node in A. In case (2), a reverse edge between B -> A
     * exists, which means in the original graph, no edge between B -> A existed, meaning it is impossible to start
     * from any node in B and go to any node in A.
     *
     * Label components by the first node visited in that component by the reverse DFS, and keep a stack of the
     * component assignment order. When popping the stack, it is guaranteed that no edge exists between the currently
     * popped item and any items proceeding it. We only need to mention the first possible edge, which exists between
     * the top item in the stack and the one directly after it.
     */
    fio;
    size_t n, m;
    cin >> n >> m;
    BitVector vis(n), rev_vis(n);
    vector<edge> edges(m), rev_edges(m);
    vector<int> components(n, -1), heads(n, -1), rev_heads(n, -1);
    st<int> order;
    foraz(i, 0, m) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        const auto idx = static_cast<int>(i);
        edges[i].to = b;
        edges[i].nxt = heads[a];
        heads[a] = idx;
        rev_edges[i].to = a;
        rev_edges[i].nxt = rev_heads[b];
        rev_heads[b] = idx;
    }
    foraz(i, 0, n) {
        if (vis.get(i)) continue;
        forwardDFS(static_cast<int>(i), heads, edges, vis, order);
    }
    int comp_idx = 0;
    st<int> disjoint;
    while (!order.empty()) {
        const auto cur = order.tp;
        order.pp;
        if (rev_vis.get(cur)) continue;
        disjoint.emplace(cur);
        reverseDFS(cur, comp_idx++, rev_heads, rev_edges, rev_vis, components);
    }
    if (comp_idx == 1) {
        cout << "YES" << edl;
        return 0;
    }
    cout << "NO" << edl;
    foraz(i, 0, 2) {
        cout << (disjoint.tp + 1) << ' ';
        disjoint.pp;
    }
    return 0;
}
