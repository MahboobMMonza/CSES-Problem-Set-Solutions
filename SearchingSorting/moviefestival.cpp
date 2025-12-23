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

inline ull trunk(ull x) {
    return (ull) (UINT32_MAX) & x;
}

bool cmp(ull a, ull b) {
    return (trunk(a)) < (trunk(b));
}

int main() {
    /**
     * (Can be done using an array of arrays of size 2, but this seems much nicer.) Store all of the data in unsigned
     * 64-bit longs, since values can only be positive. Read a and b values, and assign each index of the array (size
     * n) with the first 32 bits containing the value of a, and the second 32 bits containing the value of b. Create a
     * custom comparator that compares only the last 32 bits (ending times), so that the array is sorted by end times.
     * Afterwards, watch the first movie since it has the earliest end time, and keep track of the end time. For
     * following films, if the start time is >= to the current end time, increment the answer and save end time of the
     * current film as the new one to check.
     */
    fio;
    const int MX = 2e5+5;
    array<ull, MX> mv{};
    int n, ans = 1;
    ull a, b;
    cin >> n;
    fora(i,0,n,1) {
        cin >> a >> b;
        mv[i] |= b | (a<<32);
    }
    sort(mv.begin(), mv.begin()+n, cmp);
    b = trunk(mv[0]);
    fora(i,1,n,1) {
        // If the beginning of this movie is greater than the end of the previously watched movie, watch it.
        if ((mv[i]>>32) >= trunk(b)) {
            ans++;
            b = trunk(mv[i]);
        }
    }
    cout << ans << edl;
    return 0;
}