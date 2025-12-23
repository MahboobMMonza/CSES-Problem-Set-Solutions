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
    return 0 <= r && r < grid.size() && 0 <= c && c < grid[0].size() && (grid[r][c] == '.' || grid[r][c] == 'A');
}

int bfs(int r, int c, vector<string> &grid, vector<vector<int>> &trace, qu<pii> &q, const vector<int> &dir) {
    q.emplace(0, pi{r, c});
    grid[r][c] = '-';
    int d;
    while (!q.empty()) {
        d = q.fr.fs, r = q.fr.sc.fs, c = q.fr.sc.sc;
        q.pop();
        foras(i, 0, dir.size(), 2) {
            int ar = r + dir[i], ac = c + dir[i + 1];
            if (valid(ar, ac, grid)) {
                trace[ar][ac] = i/2;
                if (grid[ar][ac] == 'A') {
                    return d + 1;
                }
                grid[ar][ac] = '-';
                q.emplace(d + 1, pi{ar, ac});
            }
        }
    }
    return -1;
}

int main() {
    fio;
    int n, m, ans = 0, r, c, ar, ac;
    cin >> n >> m;
    vector<string> grid(n);
    // NORMAL: U, D, L, R
    // INVERSE: D, U, R, L
    vector<int> dir = {-1, 0, 1, 0, 0, -1, 0, 1};
    vector<vector<int>> trace(n, vector<int>(m, 0));
    qu<pii> q; // d, r, c
    fora(i, 0, n) {
        cin >> grid[i];
        fora(j, 0, m) {
            if (grid[i][j] == 'B') {
                r = i;
                c = j;
            } else if (grid[i][j] == 'A') {
                ar = i;
                ac = j;
            }
        }
    }
    ans = bfs(r, c, grid, trace, q, dir);
    if (ans == -1) {
        cout << "NO";
        return 0;
    }
    cout << "YES" << edl;
    cout << ans << edl;
    while (ar != r || ac != c) {
        switch (trace[ar][ac]) {
            case 0:
                cout << 'D';
                ar++;
                break;
            case 1:
                cout << 'U';
                ar--;
                break;
            case 2:
                cout << 'R';
                ac++;
                break;
            case 3:
                cout << 'L';
                ac--;
                break;
        }
    }
    return 0;
}
