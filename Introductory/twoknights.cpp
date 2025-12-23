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

ll knights(ll x) {
    // Dividing by 2 is the same as shifting one bit to the left
    return ((x * x * (x * x - 1))>>1) - 2 * (x - 1) * (x - 2) * 2;
}

int main() {
    fio;
    /**
     * Two knights can attack each other if an L can be formed. This L is 2 units from the position of the target, and
     * then 1 unit in a perpendicular of the first direction. This is ADDED to the position of the target, so the path
     * of the knight including its start and end positions would be 3 units long and then 2 units long in a
     * perpendicular direction. This can essentially create a 3x2 or 2x3 rectangle, in which the non-adjacent corners
     * can serve as start and end positions, so there are 2 configurations that work for each rectangle. Since knights
     * are identical, we actually have 1/2 of the actual total configurations available, since A->B = B->A. There are
     * n^2 spots available, of which we choose 2. Then, we also must subtract all attacking positions. As shown before,
     * the total number of spots that can be attacked can be represented as 2x3 or 3x2 rectangles that encompass the
     * board. Since the board is a square, 2x3 and 3x2 rectangles that fit in it can be counted in the same manner since
     * it is just a reflection along the diagonal (transpose), so calculate once and double. Then for each rectangle,
     * account 2 possible attacking positions. To find the number of 2x3 rectangles that fit in an n x n square, look
     * at how many 2-wide and 3-wide rectangles can fit in a row of n squares, then multiply. If k <= n, then the number
     * of rectangles of length k that can fit inside of a rectangle of length n is (n - k + 1). To intuit this value,
     * imagine a row numbered from 1 to n, and then select continuous blocks of length k along that row. The blocks that
     * can be selected have their last block number inside of k <= a <= n. The amount of natural numbers in [k, n] is
     * n - k + 1. Then obviously since we know the column size, the same applies to the row size, and then for each
     * possible column-wise orientation, the number of rectangles that share that column are whatever number of rows are
     * available. Since k is 2 and 3, we have (n - 2 + 1 = n - 1) and (n - 3 + 1 = n - 2).
     *
     */

    ll n;
    cin >> n;
    forae(i,1,n,1) {
        cout << knights(i) << edl;
    }
    return 0;
}
