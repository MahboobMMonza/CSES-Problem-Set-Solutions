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

bool cmp(int a, int b) {
    return abs(a) < abs(b);
}

int main() {
    fio;
    /**
     * Create an array with TWICE the size of n. Store all exit times as negative numbers, and place them as
     * separate entries in the array. Then sort all 2 * n data with a custom comparator that only checks the magnitude
     * of each of the numbers. Create a variable to store the answer and one to count the total number of customers
     * at the current time, which is the magnitude of the current index in the array. Start at the beginning, and if
     * the value is positive, increase the number of customers by 1, else decrease it by one, and update the answer to
     * be the maximum value.
     */
    const int MX = 2e5+5;
    int n;
    ll ans = 0, p = 0;
    array<int, 2*MX> t{};
    cin >> n;
    fora(i,0,2*n,2) {
        cin >> t[i] >> t[i+1];
        t[i+1] *= -1;
    }
    sort(t.begin(), t.begin()+2*n, cmp);
    fora(i,0,2*n,1) {
        if (t[i] > 0) {
            p++;
        } else {
            p--;
        }
        ans = max(ans, p);
    }
    cout << ans;
    return 0;
}