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
     * Note that as long as the rule about picking up numbers during a run is followed, then the numbers can be picked
     * starting with the leftmost number each time. This is because the order of the remaining numbers does not change
     * in relation to the other numbers after some numbers are picked. If 1 is before 2, it will always remain before 2,
     * and if 8 is after 10, it will always be after 10 (if the numbers are not picked that run). As a result, we can
     * always start from the leftmost number on the current "run" and pick up as many numbers as needed. Since this is
     * the case, we can count the number of runs required in a single sweep. Start at the leftmost value, and check if
     * the value directly greater than it has already been picked up (i.e. it is before it in the array). If it was,
     * then an extra run would be required, since the current run would collect the current number, and another run will
     * be required to collect the next number. Otherwise the current run would pick up both numbers. Use a bitset to
     * keep track of the numbers.
     */
    fio;
    const int MX = 2e5+5;
    bitset<MX> vis;
    int n, x, ans = 1;
    cin >> n;
    fora(i,0,n,1) {
        cin >> x;
        if (vis[x+1]) {
            ans++;
        }
        vis[x] = true;
    }
    cout << ans << edl;
    return 0;
}