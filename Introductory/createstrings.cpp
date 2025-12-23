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
#define stk stack
#define pq priority_queue
#define fora(i, a, b, c) for (int i = (a); i < (b); i += (c))
#define forae(i, a, b, c) for (int i = (a); i <= (b); i += (c))
#define ford(i, a, b, c) for (int i = (a); i > (b); i -= (c))
#define forde(i, a, b, c) for (int i = (a); i >= (b); i -= (c))
#define foral(i, a, b, c) for (long long i = (a); i < (b); i += (c))
#define forael(i, a, b, c) for (long long i = (a); i <= (b); i += (c))
#define fordl(i, a, b, c) for (long long i = (a); i > (b); i -= (c))
#define fordel(i, a, b, c) for (long long i = (a); i >= (b); i -= (c))

typedef unsigned long long ull;
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

int main() {
    // Brute force dfs with bitmask to keep track of what letters have already been used, and avoiding repetition
    // in beginning by only starting with unique letters. Can probably be made better by selecting only a unique
    // letter in each step.
    string inp;
    set<string> strs;
    set<char> sl;
    int l;
    pair<pi,string> cur;
    cin >> inp;
    l = (int) inp.length();
    strs.insert(inp);
    stk<pair<pi, string>> dfs;
    for (int i = 0; i < l; i++) {
        cur = {{0, 0}, ""};
        if (!sl.count(inp[i])) {
            cur.fs.sc |= (1 << i);
            cur.sc.pb(inp[i]);
            for (int j = 0; j < l; j++) {
                if (!((1 << j) & cur.fs.sc)) {
                    dfs.ps({{j, cur.fs.sc | (1 << j)}, cur.sc});
                }
            }
            while (!dfs.empty()) {
                cur = dfs.tp;
                dfs.pp;
                cur.sc.pb(inp[cur.fs.fs]);
                if (cur.fs.sc == (1 << l) - 1) {
                    strs.insert(cur.sc);
                } else {
                    for (int j = 0; j < l; j++) {
                        if (!((1 << j) & cur.fs.sc)) {
                            dfs.ps({{j, cur.fs.sc | (1 << j)}, cur.sc});
                        }
                    }
                }
            }
        }
        sl.insert(inp[i]);
    }
    cout << strs.size() << edl;
    for (auto& s : strs) {
        cout << s << edl;
    }
    return 0;
}
