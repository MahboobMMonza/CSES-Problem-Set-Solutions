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
    /**
     * Iterate from 0 to (1<<n) - 1 (in binary) to get every bitwise combination possible for ONE of the sets of apples.
     * The answer is the maximum possible sum of this set that is <= to half, since the total - 2 * ans would yield the
     * difference, and the closer the answer is to half the sum, the smaller the difference. Let t be total sum. Let s1
     * be the sum of the first set, s2 be sum of the second set. t = s1 + s2 => s1 = t - s2; difference = |s1 - s2| =
     * (t - s2) - s2 = t - 2 * s2. The difference is 0 when s2 = t/2, and the closer it is, the smaller the difference.
     */
    int n;
    ll ts = 0, cs, hs, ans = LONG_LONG_MIN;
    vector<ll> x(20);
    bool fl = 0;
    cin >> n;
    fora(i,0,n,1) {
        cin >> x[i];
        ts += x[i];
    }
    hs = ts / 2;
    for(int i = 0; i < (1<<n) && !fl; i++) {
        cs = 0;
        fora(j,0,n,1) {
            if ((1<<j)&i) {
                cs += x[j];
                if (cs <= hs) {
                    ans = max(ans, cs);
                }
                if (cs == hs) {
                    fl = 1;
                    break;
                }
            }
        }
    }
    cout << ts - 2*ans;
    return 0;
}
