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

bool valid(int r, int c, const vector<string> &grid) {
    return 0 <= r && r < grid.size() && 0 <= c && c < grid[0].size() && grid[r][c] == '.';
}

void bfs(int r, int c, vector<string> &grid, qu<pi> &q, const vector<int> &dir) {
    q.emplace(r, c);
    grid[r][c] = '-';
    while (!q.empty()) {
        r = q.fr.fs, c = q.fr.sc;
        q.pop();
        foras(i, 0, dir.size(), 2) {
            int ar = r + dir[i], ac = c + dir[i + 1];
            if (valid(ar, ac, grid)) {
                grid[ar][ac] = '-';
                q.emplace(ar, ac);
            }
        }
    }
}

int main() {
    /**
     * Simple flood fill BFS implementation. Iterate through all the cells, and if that cell is unvisited, increment the
     * count and run a BFS (flood fill) from that cell, marking all the room cells that were found as visited. Since the
     * cells are marked after being visited, BFS only runs once per room found, so total complexity is O(nm).
     */
    fio;
    int n, m, ans = 0;
    cin >> n >> m;
    vector<string> grid(n);
    vector<int> dir = {-1, 0, 1, 0, 0, -1, 0, 1};
    qu<pi> q;
    fora(i, 0, n) {
        cin >> grid[i];
    }
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (valid(i, j, grid)) {
                ans++;
                bfs(i, j, grid, q, dir);
            }
        }
    }
    cout << ans;
    return 0;
}