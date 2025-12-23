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

bool join(int c1, int c2, vector<int> &parent, vector<int> &rank) {
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
    fio;
    /**
     * Use disjoint-se structure with union-find to see what the current reachability is. If all nodes are reachable,
     * then return, otherwise pair any nodes that do not reach from 1 using join, which returns true only when a new
     * connection is formed.
     */
    int n, m, ec = 0, a, b;
    cin >> n >> m;
    vector<int> parent(n), rank(n, 0), ans;
    fora(i, 0, n) {
        parent[i] = i;
    }
    fora(i, 0, m) {
        cin >> a >> b;
        a--, b--;
        ec += join(a, b, parent, rank);
        if (ec == n - 1) {
            break;
        }
    }
    cout << (n - 1 - ec) << edl;
    if (ec == n - 1) {
        return 0;
    }
    fora(i, 1, n) {
        if (join(i, 0, parent, rank)) {
            cout << 1 << ' ' << i + 1 << edl;
        }
    }
    return 0;
}
