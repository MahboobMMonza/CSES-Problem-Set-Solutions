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
    int n, pairs = 0;
    array<ll, (int)(2e5+5)> child{};
    ll x;
    cin >> n >> x;
    fora(i,0,n,1) {
        cin >> child[i];
    }
    /**
     * Sort all of the data first, then try to create the largest pairs possible each time until no pairs can be made.
     * This is done through the 2 pointers method, one at the end and one at the beginning. While the one at the end
     * is larger than the one at the beginning, if the sum of the current children fits, then increase pairs count and
     * move left pointer up 1, right pointer down 1. This is because anything to the right of the right pointer is
     * either already paired up or too big to pair since it couldn't be paired with a number <= left pointer. If the
     * sum is too big, decrease the right pointer since any number to the left of it is <= the current right pointer,
     * while all numbers to the left of the left pointer are already paired/DNE and all to the right are >= left pointer
     * value. when left pointer and right pointer intersect, terminate the loop, and the answer is n - # of pairs. This
     * is because of the n children, 2 * p are paired, and n - 2 * p are not paired. We put all paired children into 1
     * gondola per pair, using p gondolas. Then we use n - 2 * p gondolas for the rest. n - 2 * p + p = n - p.
     */
    sort(child.begin(), child.begin() + n);
    int i = 0, j = n - 1;
    while (i < j) {
        if (child[i] + child[j] > x) {
            j--;
        }
        if (child[i] + child[j] <= x) {
            pairs++;
            i++;
            j--;
        }
    }
    cout << n - pairs << edl;
    return 0;
}