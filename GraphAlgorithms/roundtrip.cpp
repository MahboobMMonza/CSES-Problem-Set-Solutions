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

bool dfsCycle(int src, vector<vector<int>> &adj, vector<int> &pred, vector<bool> &done, vector<bool> &vis,
              vector<int> &cycle, st<pi> &stk) {
    stk.emplace(0, src);
    int status, cur, x;
    while (!stk.empty()) {
        status = stk.top().fs, cur = stk.top().sc;
        stk.pop();
        if (status == 1) {
            done[cur] = true;
            vis[cur] = false;
            continue;
        }
        vis[cur] = true;
        stk.emplace(1, cur);
        for (const int &nbr : adj[cur]) {
            if (vis[nbr] && pred[cur] != nbr) {
                pred[nbr] = cur;
                cycle.pb(nbr);
                x = nbr;
                while (pred[x] != nbr) {
                    cycle.pb(pred[x]);
                    x = pred[x];
                }
                cycle.pb(nbr);
                cout << cycle.size() << edl;
                for (const int &c : cycle) {
                    cout << c << ' ';
                }
                return true;
            }
            if ((vis[nbr] && pred[cur] == nbr) || done[nbr]) {
                continue;
            }
            pred[nbr] = cur;
            stk.emplace(0, nbr);
        }
    }
    return false;
}

int main() {
    /**
     * Do a DFS on the graph, tracking the predecessor of the node during the traversal. If we neighbour a node we
     * have already visited which is not the direct predecessor to our node, then we have found a cycle of 3 or more
     * nodes.
     */
    fio;
    int n, m;
    cin >> n >> m;
    int a, b;
    vector<vector<int>> adj(n + 1);
    vector<int> pred(n + 1, 0), cycle;
    vector<bool> done(n + 1, false), vis(n + 1, false);
    st<pi> stk; // 0: ADD, 1: REMOVE
    fora(i, 0, m) {
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    forae(i, 1, n) {
        if (!done[i] && dfsCycle(i, adj, pred, done, vis, cycle, stk)) {
            return 0;
        }
    }
    cout << "IMPOSSIBLE" << edl;
    return 0;
}