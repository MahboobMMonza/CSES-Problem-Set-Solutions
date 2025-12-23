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

void topDFS(int a, vector<int> &next, vector<ll> &marks, st<pi> &stk, vector<int> &order) {
    stk.emplace(1, a);
    stk.emplace(0, a);
    while (!stk.empty()) {
        int command = stk.tp.fs, cur = stk.tp.sc;
        stk.pp;
        if (isSet(cur, marks)) {
            continue;
        }
        if (command) {
            order.pb(cur);
            continue;
        }
        toggleBit(cur, marks);
        if (isSet(next[cur], marks)) {
            continue;
        }
        stk.emplace(1, next[cur]);
        stk.emplace(0, next[cur]);
    }
}

inline void topologicalSort(vector<int> &next, vector<ll> &marks, st<pi> &stk, vector<int> &order) {
    // marks: [0, n) -> temporary; [n, 2n) -> permanent
    fora(i, 0, next.size()) {
        if (isSet(i, marks)) {
            continue;
        }
        topDFS(i, next, marks, stk, order);
    }
}

void dfs(int root, vector<int> &dists, vector<int> &next, vector<int> &roots, vector<ll> &marks) {
    int d = 0, cur = root;
    while (dists[cur] == -1) {
        dists[cur] = d++;
        cur = next[cur];
    }
}

int main() {
    /**
     * "Topological sort" the nodes, then use DFS to traverse and calculate distances from any root nodes (nodes with no
     * incoming edges). Track the root for each node. If in a query, the roots are different, it is impossible to
     * traverse. Otherwise distance is dists[b] - dists[a], where dists is a list that tracks the distance from the ith
     * node's root to i.
     *
     * Modify topological sort to ignore the cyclic edge since there is only one edge out of each node.
     */
    fio;
    int n, q;
    cin >> n >> q;
    vector<int> dists(n, -1), next(n), order, roots(n, -1);
    vector<ll> marks((n + 63) >> 6, 0);
    st<pi> stk;
    fora(i, 0, n) {
        cin >> next[i];
        next[i]--;
    }
    topologicalSort(next, marks, stk, order);
    forde(i, n - 1, 0) {
        int cur = order[i];
        if (roots[cur] == -1) {
            dfs(cur, dists, next, roots, marks);
        }
    }
    return 0;
}
