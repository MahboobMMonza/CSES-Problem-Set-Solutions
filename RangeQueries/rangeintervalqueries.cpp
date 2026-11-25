#include <bits/stdc++.h>
#include <cstddef>
#include <ext/pb_ds/assoc_container.hpp>
#include <limits>
#include <vector>

using namespace std;
using namespace __gnu_pbds;

#define fs first
#define fio                                                                    \
    ios::sync_with_stdio(0);                                                   \
    cin.tie(0);                                                                \
    cout.tie(0)
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
#define foraz(i, a, b) for (size_t i = (a); i < (b); ++i)
#define foraez(i, a, b) for (size_t i = (a); i <= (b); ++i)
#define fordz(i, a, b) for (size_t i = (a); i > (b); --i)
#define fordez(i, a, b) for (size_t i = (a); i >= (b); --i)
#define ford0z(i, a, b) for (size_t i = (a); i < (b); --i)
#define forazs(i, a, b, c) for (size_t i = (a); i < (b); i += (c))
#define foraezs(i, a, b, c) for (size_t i = (a); i <= (b); i += (c))
#define fordzs(i, a, b, c) for (size_t i = (a); i > (b); i -= (c))
#define fordezs(i, a, b, c) for (size_t i = (a); i >= (b); i -= (c))
#define ford0zs(i, a, b, c) for (size_t i = (a); i < (b); i -= (c))
#define MOD (int)(1e9 + 7)

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

inline ll mulMod(ll x, ll y, ll m = numeric_limits<ll>::max()) {
    x %= m;
    ll res = 0;
    while (y) {
        if (y & 1)
            res = (res + x) % m;
        if (res < 0)
            res += m;
        x = (x << 1) % m;
        y >>= 1;
    }
    return res % m;
}

inline ll logPow(ll x, ll y, ll m = numeric_limits<ll>::max()) {
    x %= m;
    ll res = 1;
    while (y) {
        if (y & 1)
            res = mulMod(res, x, m);
        x = mulMod(x, x, m);
        y >>= 1;
    }
    return res % m;
}

inline ll fsLogPow(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y & 1)
            res *= x;
        x *= x;
        y >>= 1;
    }
    return res;
}

inline ll pLogPow(ll x, ll y, ll m = 9223372036854775783) {
    return logPow(x, y % (m - 1), m);
}

struct custom_hash {
    static ull splitmix64(ull x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    ull operator()(ull x) const {
        static const ull FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

template <typename T>
using indexed_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename K>
using indexed_map =
    tree<T, K, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename Derived, typename T> class ISegNode {
  public:
    static Derived create(const T &val) { return Derived::create_impl(val); }

    static Derived op(const Derived &l, const Derived &r) {
        return Derived::op_impl(l, r);
    }

    static size_t query(const Derived &s, T lo, T hi) {
        return Derived::query_impl(s, lo, hi);
    }
};

template <typename T> class SegNode : public ISegNode<SegNode<T>, T> {
  public:
    vector<T> values;

    SegNode() {}
    SegNode(T value) { values = {value}; }
    SegNode(vector<T> vals) : values(std::move(vals)) {}

    static SegNode create_impl(T val) { return SegNode(val); }

    static SegNode op_impl(const SegNode &l, const SegNode &r) {
        vector<T> arr(l.values.size() + r.values.size());
        merge(l.values.begin(), l.values.end(), r.values.begin(),
              r.values.end(), arr.begin());
        return SegNode(std::move(arr));
    }

    static size_t query_impl(const SegNode &s, T lo, T hi) {
        // Number of items in array <= q_val
        return static_cast<size_t>(
            upper_bound(s.values.begin(), s.values.end(), hi) -
            lower_bound(s.values.begin(), s.values.end(), lo));
    }
};

template <typename T, typename D> class SegmentTree {
  private:
    vector<D> rangeData;
    size_t sz;

  public:
    SegmentTree(const vector<T> &data) {
        rangeData.resize(2 * data.size());
        rangeData[0] = D();
        sz = data.size();
        for (size_t i = 0; i < sz; i++) {
            rangeData[sz + i] = D::create(data[i]);
        }
        for (size_t i = sz - 1; i > 0; --i) {
            rangeData[i] = D::op(rangeData[2 * i], rangeData[2 * i + 1]);
        }
    }

    size_t queryRange(size_t l, size_t r, T lo, T hi) {
        // EXCLUSIVE OF r, <= q_val
        l += sz, r += sz;
        size_t left = 0, right = 0;
        while (l < r) {
            if (l & 1) {
                left += D::query(rangeData[l], lo, hi);
                l++;
            }
            if (r & 1) {
                --r;
                right += D::query(rangeData[r], lo, hi);
            }
            l >>= 1, r >>= 1;
        }
        return left + right;
    }
};

typedef SegNode<uint> uint_merge_node;

int main() {
    /**
     * Using the segment tree/node abstraction, we can define the segment node
     * to hold a sorted list of the values (with leaf nodes holding lists of
     * size 1), and modify our query function and structure to fit the question.
     * The node now has a query function which counts the number of values in
     * the segment for lo <= x_i <= hi, and these totals are added together
     * similar to result combinations in other implemetnations.
     *
     * The number of values in [lo, hi] for a given sorted array is the
     * difference in position between the first value >= lo and the first value
     * > hi, which corresponds to the difference between uppoer_bound(arr, hi)
     * and lower_bound(arr, lo).
     *
     * The segment tree is sorted upon build based on the same principles as
     * merge sort. It takes O(nlogn) time to build (O(logn) levels * O(n) merge
     * at each level), and O(log^2n) time to query (O(logn) queries * O(logn)
     * time per query).
     */
    fio;
    size_t n, q;
    cin >> n >> q;
    vector<uint> arr(n);
    foraz(i, 0, n) { cin >> arr[i]; }
    SegmentTree<uint, uint_merge_node> seg(arr);
    while (q--) {
        size_t a, b;
        uint c, d;
        cin >> a >> b >> c >> d;
        a--;
        // < c count
        auto ans = seg.queryRange(a, b, c, d);
        cout << ans << edl;
    }
    return 0;
}
