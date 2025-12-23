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
     * The approach to this problem is finding the sliding window maximum of the PSA of the input array, where the
     * window is of sz b - a + 1, with some small modifications. The reason why sliding window works is as follows:
     *
     * Consider all subarrays that start after index i (i.e. the leftmost element of the subarray is index i + 1). The
     * smallest subarray from this position that can be considered ends at index i + a, and the largest subarray ends at
     * index i + b, b >= a >= 1. We can thereby consider a window range of [i + a, i + b] in the PSA for the right
     * endpoints of all valid subarrays. Any window of sz k, a <= k <= b, is a valid subarray that can be considered
     * in this range. The subarray sum of a window of sz k starting after index i is thereby formed as
     * psa[i + k] - psa[i]. For any subarray which ends inside the current window, all of them will subtract psa[i], so
     * it is a constant. Therefore, for a given window, the sum of a subarray ending at index j is larger than the sum
     * of a subarray ending at index k iff psa[j] > psa[k].
     *
     * The sliding window maximum algorithm can be used on the PSA with window sizes of b - a + 1, starting with the
     * first viable subarray right endpoint, which will be index a in the PSA when i = 0. For the current window, the
     * best answer will thereby come from the maximum in the window, which will then subtract psa[i] to get the
     * corresponding subarray sum for the maximum subarray in that window. The only remaining consideration is when the
     * sliding window of sz b - a + 1 has reached the end of the array, since the window does not consider subarrays
     * which include the last element with sz < b. To account for this, shrink the window by 1 on the left side and
     * recalculate the maximum sum until the window is sz 1, which would represent the subarray of sz a which
     * includes the last element of the array.
     *
     */
    fio;
    deque<int> monoq;
    int n, a, b;
    cin >> n >> a >> b;
    vector<ll> psa(n + 1);
    psa[0] = 0;
    forae(i, 1, n) {
        cin >> psa[i];
        psa[i] += psa[i - 1];
    }
    ll ans = INT64_MIN;
    // Build and calculate first window
    forae(i, a, b) {
        while (!monoq.empty() && psa[monoq.back()] - psa[0] < psa[i] - psa[0]) {
            monoq.pop_back();
        }
        monoq.pb(i);
    }
    ans = max(ans, psa[monoq.fr] - psa[0]);
    // Slide window of sz b - a + 1 along the array
    forae(i, 1, n - b) {
        if (!monoq.empty() && monoq.fr < i + a) {
            monoq.pop_front();
        }
        while (!monoq.empty() && psa[monoq.back()] - psa[i] < psa[i + b] - psa[i]) {
            monoq.pop_back();
        }
        monoq.pb(i + b);
        ans = max(ans, psa[monoq.fr] - psa[i]);
    }
    // Shrink the window by 1 on the left and consequently move the subtracted endpoint to the right by 1 to consider
    // all remaining viable subarrays.
    forae(i, n - b + 1, n - a) {
        if (!monoq.empty() && monoq.fr < i + a) {
            monoq.pop_front();
        }
        ans = max(ans, psa[monoq.fr] - psa[i]);
    }
    cout << ans;
    return 0;
}