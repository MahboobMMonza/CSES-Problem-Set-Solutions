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

bool lpos(int p1, int p2, int pp1, int pp2) {
    return p1 < p2 && pp1 > pp2;
}

bool rpos(int p1, int p2, int pp1, int pp2) {
    return p1 > p2 && pp1 < pp2;
}

int main() {
    /**
     * Employ the same criteria as the previous collecting numbers problem. This time, store the positions in an array,
     * and check and see how the swap affects the position of the numbers in relation to the one directly before and
     * after it. If there was a change that puts it after the one before or before the one after, then decrement count,
     * otherwise increment count. Check for both numbers, and to make sure that the same numbers were not counted twice.
     */
    // 2 4 1 5 3
    fio;
    const int MX = 2e5 + 5;
    vector<int> arr(MX);
    // Use a second vector to compare to
    vector<vector<int>> pos(2, vector<int>(MX));
    int n, ans = 1, a, b, m, nx, ny;
    cin >> n >> m;
    forae(i, 1, n, 1) {
        cin >> arr[i];
        pos[0][arr[i]] = pos[1][arr[i]] = i;
    }
    // For the last element, make the next element always greater than it
    pos[0][n + 1] = pos[1][n + 1] = 2 * n;
    forae(i, 2, n, 1) {
        ans += pos[0][i] < pos[0][i - 1];
    }
    fora(i, 0, m, 1) {
        cin >> a >> b;
        swap(pos[i & 1][arr[a]], pos[i & 1][arr[b]]);
        nx = arr[a], ny = arr[b];
        if (lpos(pos[i & 1][nx], pos[i & 1][nx + 1], pos[(i + 1) & 1][nx], pos[(i + 1) & 1][nx + 1]) ||
            lpos(pos[i & 1][nx - 1], pos[i & 1][nx], pos[(i + 1) & 1][nx - 1], pos[(i + 1) & 1][nx])) {
            ans--;
        }
        if (rpos(pos[i & 1][nx], pos[i & 1][nx + 1], pos[(i + 1) & 1][nx], pos[(i + 1) & 1][nx + 1]) ||
            rpos(pos[i & 1][nx - 1], pos[i & 1][nx], pos[(i + 1) & 1][nx - 1], pos[(i + 1) & 1][nx])) {
            ans++;
        }
        if (lpos(pos[i & 1][ny], pos[i & 1][ny + 1], pos[(i + 1) & 1][ny], pos[(i + 1) & 1][ny + 1]) && ny + 1 != nx ||
            lpos(pos[i & 1][ny - 1], pos[i & 1][ny], pos[(i + 1) & 1][ny - 1], pos[(i + 1) & 1][ny]) && ny - 1 != nx) {
            ans--;
        }
        if (rpos(pos[i & 1][ny], pos[i & 1][ny + 1], pos[(i + 1) & 1][ny], pos[(i + 1) & 1][ny + 1]) && ny + 1 != nx ||
            rpos(pos[i & 1][ny - 1], pos[i & 1][ny], pos[(i + 1) & 1][ny - 1], pos[(i + 1) & 1][ny]) && ny - 1 != nx) {
            ans++;
        }
        cout << ans << edl;
        swap(pos[(i + 1) & 1][arr[a]], pos[(i + 1) & 1][arr[b]]);
        swap(arr[a], arr[b]);
    }
    return 0;
}