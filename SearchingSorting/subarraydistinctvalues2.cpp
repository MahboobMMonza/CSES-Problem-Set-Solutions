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

struct custom_hash {
    static ull splitmix64(ull x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    ull operator()(ull x) const {
        static const ull FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

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
     * Need to use an expanding sliding window approach. By default, toggleBit to expand. As long as the number of unique
     * values encountered so far is <= k, keep expanding. Whenever this is the case, add to the running total the
     * number of subarrays within the window which end with the element at the right endpoint. This value is just
     * r - l + 1. If it is not the case, then toggleBit expand flag to false and move the left pointer to the right by one
     * index. At the next iteration, recalculate the number of unique elements in the window considering that the
     * element just before the left pointer is no longer part of the window. Always flip the flag if the number of
     * unique elements surpasses or falls back down to k.
     *
     * To count the number of unique elements in the window, use a frequency map to track the values; add 1 to the count
     * if the frequency of the current element at the right endpoint is 1, and subtract 1 if the frequency of the
     * element before the left endpoint is 0 once it is removed during contraction.
     */
    fio;
    int n, k;
    int l = 0, r = 0;
    int uniques = 0;
    ll total = 0;
    bool expand = true;
    unordered_map<int, int, custom_hash> frqs;
    cin >> n >> k;
    vector<int> arr(n);
    fora(i, 0, n) {
        cin >> arr[i];
    }
    while (r < n) {
        if (expand) {
            // Increase the frequency of the element at the current right endpoint index
            frqs[arr[r]]++;
            // If the frequency of the element at the right endpoint is 1, increase the unique count
            uniques += frqs[arr[r]] == 1;
        } else {
            // Contracting, so the left endpoint moved to the left by 1. Since this is the case, the element just before
            // the window is no longer considered, so remove it from the frequency. Reduce the unique count if the
            // frequency of that value is now 0.
            frqs[arr[l - 1]]--;
            uniques -= frqs[arr[l - 1]] == 0;
        }
        if (uniques <= k) {
            total += r - l + 1;
            r++;
            expand = true;
        } else {
            l++;
            expand = false;
        }
    }
    cout << total << edl;
    return 0;
}