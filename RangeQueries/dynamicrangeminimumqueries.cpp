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

template<typename T>
class SegmentTree {
private:
    function <T(T, T)> op;
    vector<T> rangeData;
    size_t sz;

public:
    SegmentTree(vector<T> &data, function<T(T, T)> op, T neutral) : op(op) {
        rangeData = vector<T>(2 * data.size());
        sz = data.size();
        copy(data.begin(), data.end(), rangeData.begin() + sz);
        for (size_t i = sz - 1; i > 0; --i) {
            rangeData[i] = op(rangeData[2 * i], rangeData[2 * i + 1]);
        }
        rangeData[0] = neutral;
    }

    void update(size_t i, T value) {
        i += sz;
        rangeData[i] = value;
        for (i >>= 1; i > 0; i >>= 1) {
            rangeData[i] = op(rangeData[2 * i], rangeData[2 * i + 1]);
        }
    }

    T queryRange(size_t a, size_t b) {
        // INCLUSIVE OF a AND b
        a += sz, b += sz;
        T ans = rangeData[0]; // neutral
        while (a <= b) {
            if (a&1) {
                ans = op(ans, rangeData[a++]);
            }
            // if b is even then use the result
            if ((b + 1)&1) {
                ans = op(ans, rangeData[b--]);
            }
            a >>= 1, b >>= 1;
        }
        return ans;
    }

};

int add_int(int a, int b) {
    return min(a, b);
}

int main() {
    /**
     * Segment tree for minimum operation.
     */
    fio;
    int n, q, t;
    size_t a, b;
    cin >> n >> q;
    vector<int> data(n);
    fora(i, 0, n) {
        cin >> data[i];
    }
    SegmentTree<int> seg(data, add_int, INT32_MAX);
    while (q--) {
        cin >> t >> a >> b;
        if (t == 2) {
            cout << seg.queryRange(--a, --b) << edl;
        } else {
            seg.update(--a, (int) b);
        }
    }
    return 0;
}
