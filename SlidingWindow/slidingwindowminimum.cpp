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
     * Use a monotonically increasing queue to maintain the window minimum. The front of the queue is thereby the
     * minimum for the window. Remove out of bounds indices.
     */
    fio;
    constexpr size_t MAXEL = 10000000;
    vector<ll> arr(MAXEL);
    deque<size_t> min_deq_idx;
    size_t n, k;
    int x, a, b, c;
    ll ans = 0;
    cin >> n >> k;
    cin >> x >> a >> b >> c;
    arr[0] = x;
    for (size_t i = 1; i < n; i++) {
        arr[i] = (a * arr[i - 1] + b) % c;
    }
    for (size_t i = 0; i < k; i++) {
        while (!min_deq_idx.empty()) {
            auto idx = min_deq_idx.bk;
            if (arr[i] < arr[idx]) {
                min_deq_idx.ppb;
            } else {
                break;
            }
        }
        min_deq_idx.pb(i);
    }
    for (size_t i = 0; i <= n - k; i++) {
        auto idx = min_deq_idx.fr;
        ans ^= arr[idx];
        if (i + k >= n) continue;
        size_t ins = i + k;
        while (!min_deq_idx.empty()) {
            auto idx = min_deq_idx.bk;
            if (arr[ins] < arr[idx]) {
                min_deq_idx.ppb;
            } else {
                break;
            }
        }
        while (!min_deq_idx.empty()) {
            auto idx = min_deq_idx.fr;
            if (idx <= i) {
                min_deq_idx.ppf;
            } else {
                break;
            }
        }
        min_deq_idx.pb(ins);
    }
    cout << ans << edl;
    return 0;
}