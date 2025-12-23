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
#define fora(i, a, b, c) for (int i = (a); i < (b); i += (c))
#define forae(i, a, b, c) for (int i = (a); i <= (b); i += (c))
#define ford(i, a, b, c) for (int i = (a); i > (b); i -= (c))
#define forde(i, a, b, c) for (int i = (a); i >= (b); i -= (c))
#define foral(i, a, b, c) for (long long i = (a); i < (b); i += (c))
#define forael(i, a, b, c) for (long long i = (a); i <= (b); i += (c))
#define fordl(i, a, b, c) for (long long i = (a); i > (b); i -= (c))
#define fordel(i, a, b, c) for (long long i = (a); i >= (b); i -= (c))

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

bool vis[7][7];
string seq;
ll ans;

bool isOk(int x, int y) {
    return x < 7 && x > -1 && y < 7 && y > -1 && !vis[x][y];
}

int cnt = 0;

void dfs(int x, int y) {
    // If we reached the bottom left square, terminate the search after updating the score
    if (x == 6 && y == 0) {
        ans += cnt == 48;
        return;
    }
    // Check if a forward and backwards move cannot be made but the other directions can
    // Forward/Backwards pairings are R/L and U/D, and the opposite pair are the "other directions"
    if ((!isOk(x + 1, y) && isOk(x, y - 1) && isOk(x, y + 1) &&
         !isOk(x - 1, y)) ||
        (!isOk(x, y + 1) && isOk(x + 1, y) && isOk(x - 1, y) &&
         !isOk(x, y - 1))) {
        return;
    }
    // Visit this position
    vis[x][y] = true;
    // If the direction can be moved to (fixed/unfixed), move to that position
    // Checks for U, D, R, L
    if ((seq[cnt] == '?' || seq[cnt] == 'U') && isOk(-1 + x, y)) {
        cnt++;
        dfs(x - 1, y);
        cnt--;
    }
    if ((seq[cnt] == '?' || seq[cnt] == 'D') && isOk(1 + x, y)) {
        cnt++;
        dfs(x + 1, y);
        cnt--;
    }
    if ((seq[cnt] == '?' || seq[cnt] == 'R') && isOk(x, 1 + y)) {
        cnt++;
        dfs(x, y + 1);
        cnt--;
    }
    if ((seq[cnt] == '?' || seq[cnt] == 'L') && isOk(x, -1 + y)) {
        cnt++;
        dfs(x, y - 1);
        cnt--;
    }
    vis[x][y] = false;
}

int main() {
    fio;
    cin >> seq;
    // Recursively check each possible move and count total reaches
    // Note that looping through directions is slower than just hard-coding it, but logically it is the same thing
    dfs(0, 0);
    cout << ans << edl;
    return 0;
}