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
    fio;
    int n, m;
    ll total = 0, valid;
    cin >> n >> m;
    vector<int> nums(n);
    // Extra buffer for less if statement checks. Can be done with just m + 1
    vector<vector<ll>> ways(n, vector<ll>(m + 2, 0));
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    // For the first number, there is 1 way to make it. If it is 0, it can be any number from 1 to j
    for (int i = 1; i <= m; ++i) {
        if (nums[0] == i || nums[0] == 0) {
            ways[0][i] = 1;
        }
    }
    // For each of the rest of the numbers, calculate the number of different arrays based on the number of ways to make
    // the numbers that could precede it. If nums[i] is 0, then any number could appear here based on what came before.
    // Otherwise, the number of ways can only be non-zero if the current number being calculated is nums[i].
    fora(i, 1, n, 1) {
        forae(j, 1, m, 1) {
            forae(k, -1, 1, 1) {
                valid = nums[i] == 0 || nums[i] == j;
                ways[i][j] += valid * ways[i - 1][j + k];
                ways[i][j] %= MOD;
            }
        }
    }
    // Add all the ways for the possible values of the last number in the array, since it could be 0
    for (int i = 1; i <= m; ++i) {
        if (nums[n - 1] == i || nums[n - 1] == 0) {
            total += ways[n - 1][i];
            total %= MOD;
        }
    }
    cout << total << edl;
    return 0;
}