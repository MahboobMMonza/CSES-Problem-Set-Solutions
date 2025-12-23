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

bool check(const vector<ll> &psa, ll mxs, int n, int k) {
    int lidx = 0, divs = 0;
    for (int i = 1; i <= n; i++) {
        if (psa[i] - psa[lidx] <= mxs && n - i >= k - divs - 1) {
            continue;
        }
        lidx = i - 1;
        divs++;
        if (divs == k - 1) {
            break;
        }
    }
    return mxs >= psa[n] - psa[lidx];
}

int main() {
    /**
     * Similar to factory machines: we need to binary search on a given range to find the smallest sum such that the
     * array can be divided into subsections <= sum. To conduct the actual check, greedily keep taking items for the
     * current chunk until either the sum of the subarray exceeds the checked value, or the number of elements left
     * if this current element is taken in the chunk would cause there to not be enough splits (i.e. with x splits
     * remaining, we need x + 1 elements left). Note that for k subdivisions, we need to perform k - 1 splits. Since
     * the first k - 1 subdivisions are greedily selected to ensure that they are within the maximum searched sum,
     * return whether the last subdivision does not exceed the sum being checked.
     *
     * The range being binary searched is the maximum of the array to the sum of the array, since a subdivision with
     * one element can contain just the maximum of the array, and the sum of a subarray will always be smaller than the
     * sum of the entire array. Handle the special case of 1 subarray (i.e. no splits) separately.
     */
    fio;
    int n, k;
    cin >> n >> k;
    vector<ll> psa(n + 1);
    ll low = -1, mid, high, ans;
    psa[0] = 0;
    forae(i, 1, n) {
        cin >> psa[i];
        low = max(low, psa[i]);
        psa[i] += psa[i - 1];
    }
    high = psa[n];
    ans = high;
    if (k == 1) {
        cout << ans;
        return 0;
    }
    while (low < high) {
        mid = (high - low) / 2 + low;
        if (check(psa, mid, n, k)) {
            high = mid;
            ans = high;
        } else {
            low = mid + 1;
        }
    }
    cout << ans;
    return 0;
}
