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

pl getPV(ll k) {
    // Calculate the total number of digits completed when moving on to the next place value block. If the total
    // surpasses k, return the current place value length and the previous sum value.
    ll ans = 0l, cs = 0l, pow = 1l;
    do {
        cs += (ans + 1) * 9l * pow;
        ans++;
        pow *= 10l;
    } while(cs < k);
    return {ans, cs - (ans) * 9l * (pow/10l)};
}

char digToPrint(ll n, ll idx) {
    string num = to_string(n);
    return num[idx - 1];
}

int main() {
    fio;
    ll q, k, ak, curNum, under;
    char ans;
    pl v;
    cin >> q;
    while (q--) {
        cin >> k;
        // Calculates the current place value length and the total number of digits that were printed before the new
        // place value
        v = getPV(k);
        // gets the number of digits left in k after discounting all previous place value digits
        ak = k - v.sc;
        // Calculate the first number in the place value range. This is added with the number of completed 'blocks'
        // to get the current number
        under = fsLogPow(10, v.fs - 1);
        // In the current place value range, (ak-1) / n gives number of completed blocks. Add this with under to get the
        // current number to print from.
        curNum = (ak-1) / v.fs + under;
        // Print from the current number. To find the index within the current number, remove all previously completed
        // digits. First set gets removed by v.sc, and second set is number of completed numbers in the current place
        // value range (curNum - under) * the place value.
        ans = digToPrint(curNum, k - v.sc - v.fs*(curNum - under));
        cout << ans << edl;
    }
    return 0;
}