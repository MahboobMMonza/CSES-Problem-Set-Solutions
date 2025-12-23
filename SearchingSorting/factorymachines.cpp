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

bool possible(ll numProds, ll time, const vector<ll> &durations) {
    // Calculate to see if the given time is enough to make the products
    ll total = 0;
    for (int i = 0; i < durations.size(); ++i) {
        total += time / durations[i];
        // Short-circuit calculation to avoid overflow
        if (total >= numProds) {
            return true;
        }
    }
    return false;
}

int main() {
    fio;
    int n;
    ll t, mid, lower = 1, upper = 1e18;
    cin >> n >> t;
    vector<ll> durations(n);
    for (int i = 0; i < n; ++i) {
        cin >> durations[i];
    }
    // There exists some time t_min whereby every time t >= t_min is enough time to make all products. From time
    // 1...t_min - 1 it is not possible to make all the products. We can binary search t in the range 1 to 10^18,
    // using a function to check if that time is feasible, until the lower bound becomes t_min.
    while (lower < upper) {
        mid = (upper - lower) / 2l + lower;
        if (possible(t, mid, durations)) {
            upper = mid;
        } else {
            lower = mid + 1;
        }
    }
    cout << lower << edl;
    return 0;
}