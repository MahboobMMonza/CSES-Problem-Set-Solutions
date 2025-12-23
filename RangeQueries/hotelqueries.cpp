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
    function<T(T, T)> op;
    function<bool(T, T)> walkComp;
    vector<T> rangeData;
    size_t sz;

public:
    SegmentTree(vector<T> &data, function<T(T, T)> op, function<bool(T, T)> walkComp, T neutral) : op(op),
                                                                                                   walkComp(std::move(
                                                                                                           walkComp)) {
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

    size_t size() {
        return rangeData.size();
    }

    pair<size_t, T> findFirst(T val) {
        size_t i = 1;
        if (!walkComp(rangeData[i], val)) {
            return {rangeData.size() + 1, rangeData[0]};
        }
        while ((i << 1) < rangeData.size()) {
            i <<= 1;
            i += !walkComp(rangeData[i], val);
        }
        return {i, rangeData[i]};
    }

    T queryRange(size_t a, size_t b) {
        // INCLUSIVE OF a AND b
        a += sz, b += sz;
        T ans = rangeData[0]; // neutral
        while (a <= b) {
            if (a & 1) {
                ans = op(ans, rangeData[a++]);
            }
            // if b is even then use the result
            if ((b + 1) & 1) {
                ans = op(ans, rangeData[b--]);
            }
            a >>= 1, b >>= 1;
        }
        return ans;
    }

};

int add_int(int a, int b) {
    return max(a, b);
}

int main() {
    /**
     * Use segment tree as a BST by keeping the minimum, and finding the first element that meets requirements. The
     * offset of the segment tree is (n - 1), so factor that in when printing the result.
     */
    fio;
    int n, q;
    int a;
    pair<size_t, int> ans;
    size_t idx;
    cin >> n >> q;
    vector<int> data(n);
    int msb = 31 - __builtin_clz(n);
    if (n ^ (1<<msb)) {
        data.resize((1 << (msb + 1)));
    }
    fora(i, 0, n) {
        cin >> data[i];
    }
    SegmentTree<int> seg(data, add_int, greater_equal<int>(), INT32_MIN);
    while (q--) {
        cin >> a;
        ans = seg.findFirst(a);
        if (ans.fs > seg.size()) {
            cout << 0;
        } else {
            idx = ans.fs - data.size();
            cout << idx + 1;
            seg.update(idx, ans.sc - a);
        }
        cout << ' ';
    }
    return 0;
}
