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
};

template <typename T, T neutral>
class SegNode : public ISegNode<SegNode<T, neutral>, T> {
  public:
    T val;

    SegNode() : val(neutral) {}
    SegNode(T value) : val(value) {}

    static SegNode create_impl(T val) { return SegNode(val); }

    static SegNode op_impl(const SegNode &l, const SegNode &r) {
        return SegNode(min(l.val, r.val));
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

    void update(size_t i, const T &value) {
        i += sz;
        rangeData[i] = D::create(value);
        while (i >>= 1) {
            rangeData[i] = D::op(rangeData[2 * i], rangeData[2 * i + 1]);
        }
    }

    D queryRange(size_t l, size_t r) {
        // EXCLUSIVE OF r
        l += sz, r += sz;
        D left, right;
        bool lefted = false, righted = false;
        while (l < r) {
            if (l & 1) {
                if (!lefted) {
                    left = rangeData[l];
                    lefted = true;
                } else {
                    left = D::op(left, rangeData[l]);
                }
                l++;
            }
            if (r & 1) {
                --r;
                if (!righted) {
                    righted = true;
                    right = rangeData[r];
                } else {
                    right = D::op(rangeData[r], right);
                }
            }
            l >>= 1, r >>= 1;
        }
        if (!lefted)
            return right;
        if (!righted)
            return left;
        return D::op(left, right);
    }
};

typedef SegNode<ll, static_cast<ll>(numeric_limits<int>::max())> imin_node;

size_t query(const size_t &l, const size_t &r,
             const vector<vector<size_t>> &jump) {
    // EXCLUSIVE OF r
    size_t ans = 1;
    size_t cur = l;
    ford0z(pow, jump.size() - 1, jump.size()) {
        if (jump[pow][cur] < r) {
            ans += 1 << pow;
            cur = jump[pow][cur];
        }
    }
    return ans;
}

int main() {
    /**
     * Consider for each building the first building taller than it to the
     * right. We can see this would create a DAG of increasing subsequences
     * starting at each index. We can use binary lifting (successor paths) to
     * find for each building which building would be k steps away in the DAG.
     * Then for each query, we can binary search how many steps it would take
     * to reach a building outside the desired range, since binary lifting
     * stores step sizes of powers of 2.
     *
     * The way the binary search is structured is as follows:
     *   1. Starting at the left building in range, try the biggest binary lift
     *      that does not breach the right bound.
     *   2. Add the size of this lift to the answer because at least that many
     *      buildings are visible after the left one.
     *   2. Go to this building. The next jump largest jump can be at most half
     *      the size of the last jump.
     *   3. Repeat this process until a jump of size 1 cannot be made.
     *
     * This is analagous to making a jump of size 2^k for every set bit in the
     * binary representation of the answer. Thus, if we iterate from the largest
     * possible power of two for the binary lift down to 0 and apply jumps of
     * size 2^k every time a jump doesn't go past the right bound, this can be
     * done in O(logn) time.
     */
    fio;
    size_t n, q;
    cin >> n >> q;
    const auto MAX_LOG = static_cast<size_t>(64 - __builtin_clzll(n));
    vector<int> buildings(n);
    vector<vector<size_t>> jump(MAX_LOG, vector<size_t>(n, n));
    st<size_t> monos;

    foraz(i, 0, n) { cin >> buildings[i]; }
    ford0z(i, n - 1, n) {
        while (!monos.empty() && buildings[monos.tp] <= buildings[i]) {
            monos.pp;
        }
        if (!monos.empty()) {
            jump[0][i] = monos.tp;
        }
        monos.ps(i);
    }

    foraz(step, 1, MAX_LOG) {
        foraz(i, 0, n) {
            if (jump[step - 1][i] >= n) {
                continue;
            }
            jump[step][i] = jump[step - 1][jump[step - 1][i]];
        }
    }

    while (q--) {
        size_t a, b;
        cin >> a >> b;
        a--;
        cout << query(a, b, jump) << edl;
    }
    return 0;
}
