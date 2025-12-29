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

bool reverseDFS(const int a, const int idx, const vector<int> &heads, const vector<edge> &edges, BitVector &vis,
    vector<int> &comp, string &pizza) {
    st<int> calls;
    vis.set(a);
    calls.emplace(a);
    while (!calls.empty()) {
        const auto cur = calls.tp;
        comp[cur] = idx;
        if (comp[cur ^ 1] == idx) return false;
        calls.pp;
        for (int i = heads[cur]; i != -1; i = edges[i].nxt) {
            auto nbr = edges[i].to;
            if (vis.get(nbr)) continue;
            vis.set(nbr);
            calls.emplace(nbr);
        }
    }
    return true;
}

int main() {
    /**
     * This is a 2SAT problem, as each topping can be included (TRUE) or not included (FALSE). Construct the graph as
     * explained the book: For every pairing (ai | bi) create connections ~ai -> bi and ~bi -> ai. To make it easy to
     * work with, make each node labeling adjacent to its complement. This means, using 0-indexing, x0 is
     * toppings[0], ~x0 is toppings[1], x1 is toppings[2], ~x1 is toppings[3], ... xi is toppings[2i] and ~xi is
     * toppings[2i + 1].
     *
     * Run Kosaraju's on this graph, and when assigning components, check that the topping's complement is not
     * present. This can be done using XOR: x ^ 1 = x - 1 if x is odd (i.e. topping is false), and x ^ 1 = x + 1 if x
     * is even (i.e. topping is true). Assign a value to the final toppings if it has not been assigned while doing
     * this traversal. Note that both xi and ~xi will map to pizza[i - (i&1)] as each topping is space separated.
     */
    fio;
    size_t n, m;
    cin >> n >> m;
    BitVector vis(2 * m), rev_vis(2 * m);
    vector<edge> edges(2 * n), rev_edges(2 * n);
    vector<int> components(2 * m, -1), heads(2 * m, -1), rev_heads(2 * m, -1);
    string pizza(2 * m - 1, ' ');
    st<int> order;
    foraz(i, 0, n) {
        int a, b;
        char top_a, top_b;
        cin >> top_a >> a >> top_b >> b;
        --a, --b;
        a *= 2, b *= 2;
        if (top_a == '-') a ^= 1;
        if (top_b == '-') b ^= 1;
        const auto na = a ^ 1, nb = b ^ 1;
        const auto idx = static_cast<int>(2 * i);
        edges[idx].to = b;
        edges[idx].nxt = heads[na];
        heads[na] = idx;
        edges[idx + 1].to = a;
        edges[idx + 1].nxt = heads[nb];
        heads[nb] = idx + 1;
        rev_edges[idx].to = na;
        rev_edges[idx].nxt = rev_heads[b];
        rev_heads[b] = idx;
        rev_edges[idx + 1].to = nb;
        rev_edges[idx + 1].nxt = rev_heads[a];
        rev_heads[a] = idx + 1;
    }
    foraz(i, 0, 2 * m) {
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
        const auto result = reverseDFS(cur, comp_idx++, rev_heads, rev_edges, rev_vis, components, pizza);
        if (!result) {
            cout << "IMPOSSIBLE" << edl;
            return 0;
        }
    }
    forazs(i, 0, 2 * m, 2) {
        pizza[i] = components[i] > components[i ^ 1] ? '+' : '-';
    }
    cout << pizza << edl;
    return 0;
}
