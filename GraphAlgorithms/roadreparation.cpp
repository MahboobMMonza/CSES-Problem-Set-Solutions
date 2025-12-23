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
typedef pair<ll, pi> plpi;

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

int find(int x, vector<int> &parent) {
    int root = x, par;
    while (parent[root] != root) {
        root = parent[root];
    }
    while (parent[x] != x) {
        par = parent[x];
        parent[x] = root;
        x = par;
    }
    return root;
}

bool join(int c1, int c2, vector<int> &parent, vector<int> &rank, st<int> &stk) {
    int p1 = find(c1, parent), p2 = find(c2, parent);
    if (p1 == p2) {
        return false;
    }
    if (rank[p1] < rank[p2]) {
        parent[p1] = p2;
        rank[p2]++;
    } else {
        parent[p2] = p1;
        rank[p1]++;
    }
    return true;
}

int main() {
    /**
     * Simple implementation of Kruskal's algorithm using disjoint-set structure.
     */
    fio;
    int n, m, ec = 0, a, b;
    ll cost = 0, c;
    cin >> n >> m;
    vector<int> parent(n), rank(n, 0), ans;
    vector<plpi> edges(m);
    fora(i, 0, n) {
        parent[i] = i;
    }
    fora(i, 0, m) {
        cin >> a >> b >> c;
        a--, b--;
        edges[i] = {c, {a, b}};
    }
    sort(edges.begin(), edges.end());
    fora(i, 0, m) {
        bool res = join(edges[i].sc.fs, edges[i].sc.sc, parent, rank, stk);
        if (res) {
            ec++;
            cost += edges[i].fs;
        }
        if (ec == n - 1) {
            break;
        }
    }
    if (ec != n - 1) {
        cout << "IMPOSSIBLE" << edl;
        return 0;
    }
    cout << cost << edl;
    return 0;
}
