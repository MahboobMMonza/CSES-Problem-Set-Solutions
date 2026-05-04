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

ull solve(const vector<int> &heads, vector<int> &trav_heads, vector<int> &level, vector<edge> &edges, BitVector
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

int main() {
    /**
     * Classic implementation of non-recursive Dinic's algo. Recursion replaced with own call stack. Use a second heads
     * array to complete tracked traversal during dfs, and copy back afterwards for next stage.
     */
    fio;
    size_t n, m;
    cin >> n >> m;
    vector<int> heads(n, -1), trav_heads(n), level(n, -1);
    vector<edge> edges(2 * m);
    BitVector searching(n);
    foraz(i, 0, m) {
        int a, b, speed;
        cin >> a >> b >> speed;
        a--, b--;
        const auto idx = 2 * i;
        const auto rev_idx = idx ^ 1;
        edges[idx].to = b;
        edges[idx].nxt = heads[a];
        edges[idx].max_capacity = speed;
        heads[a] = static_cast<int>(idx);
        edges[rev_idx].to = a;
        edges[rev_idx].nxt = heads[b];
        heads[b] = static_cast<int>(rev_idx);
        edges[rev_idx].max_capacity = speed;
        edges[rev_idx].flow = speed;
    }
    cout << solve(heads, trav_heads, level, edges, searching) << edl;
    return 0;
}
