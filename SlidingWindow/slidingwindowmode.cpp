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
     * Track the frequency of each number using a frequency map, as well as a reverse map of frequencies to values as
     * {freq -> ordered set of elements}. Also track the maximum frequency count to quickly access the reverse map to
     * get the mode.
     *
     * After building the initial window, the frequency of an element either goes up by 1 or down by 1. If it goes
     * down, the element should exist in the reverse map at key = (oldFreq - 1), so only need to remove the element from
     * the set at the highest frequency. The maximum frequency count also can either increase or decrease by at most 1
     * at each window slide, so if the size of the set of the reverse frequency map is zero, then the max frequency can
     * be decremented. The max frequency is updated against the frequency of the newly added element after it is
     * accounted for.
     *
     * To obtain the mode at each window, find the smallest element in the set of the maximum frequency (set.begin()).
     */
    fio;
    unordered_map<int, set<int>> modes;
    unordered_map<int, int> frqs;
    int n, k, maxfreq;
    cin >> n >> k;
    vector<int> arr(n);
    fora(i, 0, n) {
        cin >> arr[i];
    }
    if (k == 1) {
        forae(i, 0, n - k) {
            cout << arr[i] << ' ';
        }
        return 0;
    }
    fora(i, 0, k) {
        maxfreq = max(maxfreq, ++frqs[arr[i]]);
        if (!modes.count(maxfreq)) {
            modes[maxfreq] = set<int>();
        }
        modes[frqs[arr[i]]].insert(arr[i]);
    }
    forae(i, 0, n - k) {
        cout << *modes[maxfreq].begin() << ' ';
        if (i >= n - k || arr[i] == arr[i + k]) continue;
        modes[frqs[arr[i]]].erase(arr[i]);
        if (frqs[arr[i]] == maxfreq && modes[frqs[arr[i]]].empty()) {
            maxfreq--;
        }
        frqs[arr[i]]--;
        maxfreq = max(maxfreq, ++frqs[arr[i + k]]);
        if (!modes.count(maxfreq)) {
            modes[maxfreq] = set<int>();
        }
        modes[frqs[arr[i + k]]].insert(arr[i + k]);
    }
    return 0;
}
