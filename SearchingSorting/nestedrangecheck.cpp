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
#define MX (size_t) (2e5 + 5)

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

bool cmp1(pii &a, pii &b) {
    return (a.sc.fs < b.sc.fs) || (a.sc.fs == b.sc.fs && b.sc.sc <= a.sc.sc);
}

int main() {
    fio;
    vector<pii> ranges;
    vector<bool> contains, contained;
    int n, bound;
    cin >> n;
    ranges.resize(n);
    contained.resize(n, false);
    contains.resize(n, false);
    fora(i, 0, n, 1) {
        ranges[i].fs = i;
        cin >> ranges[i].sc.fs >> ranges[i].sc.sc;
    }
    sort(ranges.begin(), ranges.end(), cmp);
    // Viewer
    /*
    for (const auto &item: ranges) {
        cout << setfill('0') << setw(3) << item.fs << ": ";
        for (int i = 0; i < item.sc.fs - ranges[0].sc.fs; ++i) {
            cout << ' ';
        }
        cout << '|';
        for (int i = 1; i < item.sc.sc - item.sc.fs; ++i) {
            cout << '-';
        }
        cout << '|' << edl;
    }
    */
    // contained

    // Every one is sorted such that the leftmost bounds are first, and fir ties, larger right bounds first
    // This means that if right[i] < right[i-k] for k > 0, then i is contained by i - k. Since we don't care
    // about who exactly contains, just track the largest right boundary so far.
    bound = -1;
    fora(i, 0, n, 1) {
        if (ranges[i].sc.sc <= bound) {
            contained[ranges[i].fs] = true;
        }
        bound = max(bound, ranges[i].sc.sc);
    }
    // contains

    // Every one is sorted such that the leftmost bounds are first, and fir ties, larger right bounds first
    // This means that if right[i] >= right[i+k] for k > 0, then i contains i + k. Since we don't care
    // about who exactly contains, just track the smallest right boundary so far.
    bound = INT32_MAX;
    forde(i, n - 1, 0, 1) {
        if (ranges[i].sc.sc >= bound) {
            contains[ranges[i].fs] = true;
        }
        bound = min(bound, ranges[i].sc.sc);
    }
    for (const auto &val: contains) {
        cout << val << ' ';
    }
    cout << edl;
    for (const auto &val: contained) {
        cout << val << ' ';
    }
    cout << edl;
    return 0;
}
