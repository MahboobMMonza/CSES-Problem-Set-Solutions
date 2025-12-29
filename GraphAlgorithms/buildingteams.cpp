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

bool dfs(int src, const vector<vector<int>> &friends, vector<int> &teams, qu<pi> &q) {
    q.emplace(src, 1);
    int cur, team, nt;
    while (!q.empty()) {
        cur = q.fr.fs, team = q.fr.sc;
        q.pp;
        teams[cur] = team;
        nt = (team & 1) + 1; // 1 -> 2, 2 -> 1
        for (const int frd : friends[cur]) {
            if (teams[frd] == team) {
                q = {};
                return false;
            }
            if (teams[frd] == 0) {
                q.emplace(frd, nt);
            }
        }
    }
    return true;
}

int main() {
    /**
     * Simple graph 2-colorability. Track visited status using the "colour"/team array. 0 -> unvisited, 1 -> team 1,
     * 2 -> team 2. If any neighbour is the same colour as the currently explored node in the DFS, then it is
     * impossible to assign the teams in such a way that no two neighbours are friends.
     */
    fio;
    int n, m, a, b;
    cin >> n >> m;
    vector<int> teams(n, 0);
    vector<vector<int>> friends(n);
    qu<pi> q; // node, team
    fora(i, 0, m) {
        cin >> a >> b;
        friends[a - 1].pb(b - 1);
        friends[b - 1].pb(a - 1);
    }
    fora(i, 0, n) {
        if (teams[i] != 0) {
            continue;
        }
        if (!dfs(i, friends, teams, q)) {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }
    cout << teams[0];
    fora(i, 1, n) {
        cout << ' ' << teams[i];
    }
    return 0;
}