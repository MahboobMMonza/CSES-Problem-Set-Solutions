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
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

pair<bool, int> join(int c1, int c2, vector<int> &parent, vector<int> &size) {
    int p1 = find(c1, parent), p2 = find(c2, parent);
    if (p1 == p2) {
        return {false, size[p1]};
    }
    if (size[p1] < size[p2]) {
        swap(p1, p2);
    }
    parent[p2] = p1;
    size[p1] += size[p2];
    return {true, size[p1]};
}

int main() {
    /**
     * Construct an MST using disjoint-set with unity by size and path halfing (not full path compression, not needed
     * really because we find again afterwards). Once an edge is given, attempt a join, tracking the size of each
     * component, and return the size of the combined component at the end of the join. Update the max size based on
     * these joins and print after each edge is given. If all nodes are already connected, then we can by pass
     * processing altogether.
     */
    fio;
    int n, m, ec = 0, a, b;
    int largest = 1, numGroups;
    cin >> n >> m;
    numGroups = n;
    vector<int> parent(n), size(n, 1), ans;
    fora(i, 0, n) {
        parent[i] = i;
    }
    fora(i, 0, m) {
        if (ec == n - 1) {
            cout << 1 << ' ' << n << edl;
            continue;
        }
        cin >> a >> b;
        a--, b--;
        auto res = join(a, b, parent, size);
        if (res.fs) {
            ec++;
            numGroups--;
            largest = max(largest, res.sc);
        }
        cout << numGroups << ' ' << largest << edl;
    }
    return 0;
}
