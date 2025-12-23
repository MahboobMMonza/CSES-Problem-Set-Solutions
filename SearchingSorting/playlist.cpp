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
     * Conduct a linear sweep using 2 pointers. Both pointers start at the leftmost indice (0 and 1), and as long as
     * a duplicate is not found, keep on increasing the right pointer. Once it reaches a duplicate, calculate the length
     * as the distance between the pointers, as this will exclude the right pointer's current position. The interval
     * calculated is going to be [l, r - 1]. Then, move the left pointer forwards until the initial duplicate value is
     * found and passed, then continue the process. Use a visited set to see if the current value is a duplicate,
     * and update each one as true when the right pointer passes it, and false when the left pointer passes it. To
     * shorten the runtime, once the right pointer reaches the end, the length of the interval will be the largest
     * possible with the pointer fixed in that position, since any other interval would have to move the left pointer,
     * making a smaller interval.
     */
    fio;
    const int MX = 2e5 + 5;
    vector<int> arr(MX);
    set<int> vis;
    int n, ans = 0, l = 0, r = 1;
    cin >> n;
    fora(i,0,n,1) {
        cin >> arr[i];
    }
    vis.insert(arr[l]);
    while (r < n) {
        if (!vis.count(arr[r])) {
            vis.insert(arr[r]);
            r++;
        } else {
            ans = max(ans, r - l);
            vis.erase(arr[l]);
            l++;
            vis.insert(arr[l]);
        }
        if (l == r) {
            r++;
        }
    }
    ans = max(ans, r - l);
    cout << ans << edl;
    return 0;
}