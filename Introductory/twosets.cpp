#include <bits/stdc++.h>

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
int main() {
    fio;
    // Check if the sum of the numbers from 1 to n is even. If it is odd, it is impossible to make 2 sets of even sum.
    // If it is possible, then alternate between taking the ith-last and ith number in 1 ... n until the sum of the set
    // is half of the sum calculated before. The next set should contain the numbers that were not in the first set.
    ll n, beg, last, sum, s = 0;
    vector<ll> setA;
    cin >> n;
    sum = (n * (n + 1)) / 2;
    if (sum&1) {
        cout << "NO" << edl;
    } else {
        cout << "YES" << edl;
        beg = 1, last = n;
        for (ll i = 1; s < sum / 2; i++) {
            setA.pb(n + 1 - i);
            s += n + 1 - i;
            last--;
            if (s < sum / 2) {
                setA.pb(i);
                s += i;
                beg++;
            }
        }
        cout << setA.size() << edl;
        foral(i,0,(ll (setA.size())),1) {
            cout << setA[i] << ' ';
        }
        cout << edl;
        cout << (n - setA.size()) << edl;
        forael(i,beg,last,1) {
            cout << i << ' ';
        }
        cout << edl;
    }
    return 0;
}