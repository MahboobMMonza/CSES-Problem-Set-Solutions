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
    vis[a >> 6] ^= (1ll << (63 - (a % 64)));
}

int detectCycle(vector<ll> &done, vector<ll> &in, st<pi> &stk, vector<int> pred) {
    fill(done.begin(), done.end(), 0);
    fill(in.begin(), in.end(), 0);
    while (!stk.empty()) {
        stk.pp;
    }
    fora(i, 0, pred.size()) {
        if (isSet(i, done)) {
            continue;
        }
        int u = i, c;
        stk.emplace(0, u); // COMMAND, idx
        while (!stk.empty()) {
            c = stk.tp.fs, u = stk.tp.sc;
            stk.pp;
            if (c) {
                // should be second toggle, so back to 0
                toggleBit(u, in);
                // should be first toggle, so set to 1
                toggleBit(u, done);
                continue;
            }
            stk.emplace(1, u);
            toggleBit(u, in);
            if (pred[u] == -1) continue;
            if (isSet(pred[u], in)) return pred[u];
            if (!isSet(pred[u], done)) stk.emplace(0, pred[u]);
        }
    }
    return -1;
}

void printCycle(const vector<int> &cycle) {
    cout << "YES" << edl;
    for (int i = cycle.size() - 1; i >= 0; --i) {
        cout << cycle[i] + 1 << ' ';
    }
}

vector<int> traceCycle(const int b, const vector<int> &pred) {
    vector<int> ans;
    int a = b;
    ans.pb(a);
    while (pred[a] != b) {
        ans.pb(pred[a]);
        a = pred[a];
    }
    ans.pb(b);
    return ans;
}

typedef struct edge {
    ll score;
    int to;
    int nxt;
} edge;

int main() {
    /**
     * Use SPFA (which is just a faster Bellman-Ford) to calculate the shortest path. Every nth iteration of the loop,
     * check for a negative cycle, and if one exists, then terminate with the appropriate output. This check at the nth
     * iteration compensates for SPFA's inability to detect negative cycles inherently.
     */
    fio;
    int n, m, a, b, iters = 0;
    ll x;
    cin >> n >> m;
    const size_t NODE_DWORDS = (n + 63) >> 6;
    vector<ll> inq(NODE_DWORDS, 0), cycleIn(NODE_DWORDS, 0), cycleDone(NODE_DWORDS, 0),
            dists(n, INT64_MAX);
    vector<int> heads(n, -1), pred(n, -1);
    vector<edge> edges(m);
    st<pi> stk;
    deque<int> dq;
    fora(i, 0, m) {
        cin >> a >> b >> x;
        edges[i].to = --b;
        edges[i].score = x;
        edges[i].nxt = heads[--a];
        heads[a] = i;
    }
    fora(i, 0, n) {
        dists[i] = 0;
        dq.pb(i);
        toggleBit(i, inq);
    }
    while (!dq.empty()) {
        a = dq.fr;
        dq.ppf;
        toggleBit(a, inq);
        for (int i = heads[a]; i != -1; i = edges[i].nxt) {
            edge& curEdge = edges[i];
            if (dists[curEdge.to] <= dists[a] + curEdge.score) {
                continue;
            }
            pred[curEdge.to] = a;
            dists[curEdge.to] = dists[a] + curEdge.score;
            iters++;
            if (iters == n) {
                iters = 0;
                b = detectCycle(cycleDone, cycleIn, stk, pred);
                if (b != -1) {
                    printCycle(traceCycle(b, pred));
                    return 0;
                }
            }
            if (!isSet(curEdge.to, inq)) {
                if (!dq.empty() && dists[curEdge.to] < dists[dq.fr]) {
                    dq.pf(curEdge.to);
                } else {
                    dq.pb(curEdge.to);
                }
                toggleBit(curEdge.to, inq);
            }
        }
    }
    b = detectCycle(cycleDone, cycleIn, stk, pred);
    if (b != -1) {
        printCycle(traceCycle(b, pred));
    } else {
        cout << "NO";
    }
    return 0;
}