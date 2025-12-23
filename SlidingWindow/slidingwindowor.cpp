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

int main() {
    /**
     * Use prefix and suffix arrays, where each block of k elements stores an aggregated OR of the first or last j
     * elements, for j = 1...k.
     *
     * i.e.: prefix[i] = a[0] | a[1] | a[2] | ... | a[i], 0 <= i < k (take mod k for each block)
     * i.e.: suffix[i] = a[k - 1] | a[k - 2] | a[k - 3] | ... | a[i], 0 <= i < k (take mod k for each block)
     *
     * At each stage, the sliding window's aggregated OR is prefix[i + k - 1] | suffix[i].
     *
     * Note: suffix for the last block of n - k - 1 elements is not needed (i.e. only compute suffixes in [0, n - k + 1]
     */
    fio;
    constexpr size_t MAXEL = 10000000;
    vector<ull> arr(MAXEL), prefix(MAXEL), suffix(MAXEL);
    size_t n, k;
    int x, a, b, c;
    cin >> n >> k;
    cin >> x >> a >> b >> c;
    arr[0] = x;
    prefix[0] = x;
    for (size_t i = 1; i < n; i++) {
        arr[i] = (a * arr[i - 1] + b) % c;
        if (i % k == 0) {
            prefix[i] = arr[i];
        } else {
            prefix[i] = arr[i] | prefix[i - 1];
        }
    }
    for (size_t i = n - k + 1; i < n; i--) {
        if ((i + 1) % k == 0) {
            suffix[i] = arr[i];
        } else {
            suffix[i] = arr[i] | suffix[i + 1];
        }
    }
    ull ans = 0;
    for (size_t i = 0; i <= n - k; i++) {
        const auto value = prefix[i + k - 1] | suffix[i];
        ans ^= value;
    }
    cout << ans << edl;
    return 0;
}
