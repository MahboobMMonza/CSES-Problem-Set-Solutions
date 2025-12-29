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

inline bool isSet(const size_t a, const vector<ll> &vis) {
    return vis[a >> 6] & (1ll << (63 - (a % 64)));
}

inline void toggleBit(const size_t a, vector<ll> &vis) {
    vis[a >> 6] ^= (1ll << (63 - (a % 64)));
}

typedef struct edge {
    int to;
    int nxt;
} edge;

bool dfs(int a, vector<int> &heads, vector<edge> &edges, vector<ll> &marks, st<pi> &stk, vector<int> &order) {
    stk.emplace(1, a);
    stk.emplace(0, a);
    while (!stk.empty()) {
        int command = stk.tp.fs, cur = stk.tp.sc;
        stk.pp;
        if (isSet(cur + heads.size(), marks)) {
            continue;
        }
        if (command) {
            toggleBit(cur, marks);
            toggleBit(cur + heads.size(), marks);
            order.pb(cur);
            continue;
        }
        toggleBit(cur, marks);
        for (int idx = heads[cur]; idx != -1; idx = edges[idx].nxt) {
            if (isSet(edges[idx].to + heads.size(), marks)) {
                continue;
            } else if (isSet(edges[idx].to, marks)) {
                return false;
            }
            stk.emplace(1, edges[idx].to);
            stk.emplace(0, edges[idx].to);
        }
    }
    return true;
}

inline bool
topologicalSort(vector<int> &heads, vector<edge> &edges, vector<ll> &marks, st<pi> &stk, vector<int> &order) {
    // marks: [0, n) -> temporary; [n, 2n) -> permanent
    fora(i, 0, heads.size()) {
        if (isSet(heads.size() + i, marks)) {
            continue;
        }
        if (!dfs(i, heads, edges, marks, stk, order)) {
            return false;
        }
    }
    return true;
}

int main() {
    /**
     * Topological sort using DFS (same caveats as Course Schedule). Afterwards, traverse the order, ignoring everyone
     * until the starting node is node 1, then update the cost of each of the neighbours to be 1 + cur cost or best
     * cost. This is because the graph is a DAG, and we can find the longest path of a DAG using top-sorting/DP.
     */
    fio;
    int n, m, a, b;
    cin >> n >> m;
    vector<int> heads(n, -1), order, dists(n, -1), preds(n, -1);
    vector<int> ans;
    order.reserve(n);
    vector<ll> marks(((2 * n) + 63) >> 6, 0);
    vector<edge> edges(m);
    st<pi> stk;
    fora(i, 0, m) {
        cin >> a >> b;
        edges[i].to = --b;
        edges[i].nxt = heads[--a];
        heads[a] = i;
    }
    bool start = false;
    topologicalSort(heads, edges, marks, stk, order);
    forde(i, n - 1, 0) {
        if (order[i] == 0) {
            start = true;
            dists[order[i]] = 0;
        }
        if (!start) {
            continue;
        }
        int cur = order[i];
        for (int idx = heads[cur]; idx != -1; idx = edges[idx].nxt) {
            int nbr = edges[idx].to, prevDist = dists[nbr];
            dists[nbr] = max(dists[nbr], dists[cur] + 1);
            if (prevDist < dists[nbr]) {
                preds[nbr] = cur;
            }
        }
    }
    if (dists.back() == -1) {
        cout << "IMPOSSIBLE" << edl;
        return 0;
    }
    cout << dists.back() + 1 << edl;
    ans.reserve(dists.back() + 1);
    for (int i = n - 1; i != -1 ; i = preds[i]) {
        ans.push_back(i);
    }
    ford(i, ans.size() - 1, 0) {
        cout << ans[i] + 1 << ' ';
    }
    cout << ans[0] + 1 << edl;
    return 0;
}
