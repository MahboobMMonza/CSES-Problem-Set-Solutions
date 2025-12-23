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
    vis[a >> 6] |= (1ll << (63 - (a % 64)));
}

typedef struct {
    int to;
    ll cost;
    int fnxt;
} edge;

int main() {
    /**
     * Apply Dijkstra's but instead allow a repeat node to appear up to K times.
     */
    fio;
    int n, m, b, a, nbr, k;
    ll c, ccst;
    cin >> n >> m >> k;
    vector<int> heads(n, -1), count(n, 0);
    vector<edge> edges(m);
    vector<ll> ans;
    ans.reserve(k);
    unordered_set<int> shortPath;
    pq<pli, vector<pli>, greater<pli>> q; // (w, v)
    pq<ll, vector<ll>, greater<ll>> spq;
    fora(i, 0, m) {
        cin >> a >> b >> c;
        a--, b--;
        edges[i].to = b;
        edges[i].cost = c;
        edges[i].fnxt = heads[a];
        heads[a] = i;
    }
    // Forwards
    q.emplace(0ll, 0);
    while (!q.empty()) {
        c = q.tp.fs, a = q.tp.sc;
        q.pp;
        if (count[a] >= k) {
            continue;
        }
        count[a]++;
        if (a == n - 1) {
            ans.pb(c);
        }
        if (count[n - 1] == k) {
            break;
        }
        for (int idx = heads[a]; idx != -1; idx = edges[idx].fnxt) {
            nbr = edges[idx].to;
            ccst = edges[idx].cost + c;
            q.emplace(ccst, nbr);
        }
    }
    sort(ans.begin(), ans.end());
    fora(i, 0, k) {
        cout << ans[i] << ' ';
    }
    return 0;
}
