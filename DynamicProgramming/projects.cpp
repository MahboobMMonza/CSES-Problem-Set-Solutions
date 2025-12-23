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

bool cmp(const pll &a, const pll &b) {
    return a.fs <= b.fs;
}

int main() {
    fio;
    int n;
    cin >> n;
    // Profit for choosing up to the ith project
    vector<ll> profits(n + 1);
    // Sort the projects by who ends first. That way, it is possible to find the best project that ended BEFORE the
    // current one started. Let that index be p. The choice then becomes dp[i] = max(dp[i - 1], dp[p] + proj[i].profit).
    // To make the search easier, have a "zero-project" at the beginning.
    vector<pll> projects(n + 1); // (end, {start, profit})
    pll searcher;
    size_t pos;
    projects[0] = {0l, {0l, 0l}};
    forae(i, 1, n, 1) {
        cin >> projects[i].sc.fs >> projects[i].fs >> projects[i].sc.sc;
    }
    sort(projects.begin(), projects.end(), cmp);
    profits[1] = projects[1].sc.sc;
    forae(i, 2, n, 1) {
        // From the first i elements, find the latest project that ends *after* this project starts. The project before
        // this latest project will have thereby ended before this project - let this be pos. We then only need to
        // consider the best option from projects 1...pos, which is stored in profits[pos].
        searcher.fs = projects[i].sc.fs;
        searcher.sc = projects[i].sc;
        pos = upper_bound(projects.begin(), projects.begin() + i, searcher, cmp) - projects.begin() - 1;
        profits[i] = max(profits[i - 1], projects[i].sc.sc + profits[pos]);
    }
    cout << profits[n] << edl;
    return 0;
}
