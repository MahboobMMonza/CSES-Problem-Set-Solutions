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
    char label;

    edge() = default;

    edge(const int to, const int nxt, const char label) : to(to), nxt(nxt), label(label) {
    }
} edge;

string hierholzerDeBruijn(const int start, vector<int> &heads, const vector<edge> &edges) {
    string path;
    path.reserve(edges.size());
    st<int> calls;
    calls.emplace(start);
    while (!calls.empty()) {
        const auto cur = calls.tp;
        // Find next untraversed edge
        int &edge_idx = heads[cur];
        // All edges exhausted, we don't need to come back here again. Add to path.
        if (edge_idx == -1) {
            calls.pp;
            continue;
        }
        // Traverse this edge and move to next one (slight optimization).
        // We still need to come back to this node and continue checking the rest of its neighbours, so don't pop it
        // from the stack.
        const auto nbr = edges[edge_idx].to;
        const auto label = edges[edge_idx].label;
        path.pb(label);
        edge_idx = edges[edge_idx].nxt;
        if (nbr == cur) {
            continue;
        }
        calls.ps(nbr);
    }
    return path;
}

int main() {
    /**
     * Construct an Eulerian circuit of all combinations of binary strings of length n - 1 from 0. Construct edges by
     * adding a 0 or a 1 to the right and truncating the leftmost bit.
     *
     * Use Hierholzer's algorithm to construct the path, and record the order of edges visited. Really, just record
     * the value/label of the edge and proceed as normal. Not bidirectional edges, so no need for opposite edge check.
     * The path is a queue since the order of traversal matters in a directed graph.
     *
     * To simulate backtracking non-recursively, globally track the next edge to visit using the heads array by
     * moving the tracker to the next edge after the current one is used. If the edge points to our node again, just
     * add the edge value to the queue and go to the next edge instead of adding the same node to the call stack.
     *
     * The queue in our case is a string to optimize our print, meaning labels will be chars.
     */
    fio;
    int k;
    cin >> k;
    if (k == 1) {
        cout << "01" << edl;
        return 0;
    }
    const int n = 1 << (k  - 1);
    // 00, 01, 10, 11
    vector<int> heads(n, -1); // we will essentially destroy this graph since we only ever traverse graph
    vector<edge> edges(2 * n);
    BitVector edgeVis(2 * n);
    int edge_idx = 0;
    fora(i, 0, n) {
        fora(j, 0, 2) {
            const int nbr = ((i << 1) | j) & (n - 1);
            edges[edge_idx].to = nbr;
            edges[edge_idx].nxt = heads[i];
            edges[edge_idx].label = static_cast<char>('0' + static_cast<char>(j & 1));
            heads[i] = edge_idx++;
        }
    }
    auto path = hierholzerDeBruijn(0, heads, edges);
    cout << setfill('0') << setw(k - 1) << 0;
    cout << path << edl;
    return 0;
}
