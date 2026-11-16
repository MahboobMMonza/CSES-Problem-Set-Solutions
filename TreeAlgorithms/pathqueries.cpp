#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

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
        return SegNode(l.val + r.val);
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

    SegmentTree(const size_t &n) : sz(n) { rangeData.resize(2 * n); }

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

typedef SegNode<int, 0> iadd_node;
typedef SegNode<ll, 0> ladd_node;

class BitVector {
  public:
    explicit BitVector(const size_t n) : v((n + 63) >> 6, 0) {};

    ~BitVector() = default;

    bool get(const size_t i) const { return v[i >> 6] & (1ull << (i & 63)); }

    void set(const size_t i) { v[i >> 6] |= 1ull << (i & 63); }

    void clear(const size_t i) { v[i >> 6] &= ~(1ull << (i & 63)); }

    void toggle(const size_t i) { v[i >> 6] ^= 1ull << (i & 63); }

    static string to_string(const BitVector &bv) {
        ostringstream ss;
        for (const auto &x : bv.v) {
            bitset<64> bits(x);
            string seq = bits.to_string();
            reverse(seq.begin(), seq.end());
            ss << seq;
        }
        return ss.str();
    }

  private:
    vector<ull> v;
};

typedef struct edge {
    size_t to;
    size_t nxt;

    edge() = default;

    edge(const size_t to, const size_t nxt) : to(to), nxt(nxt) {}
} edge;

int main() {
    /**
     * Creates a traversal tree which tracks the initial visit time for each
     * node, and the size of the subtree from that node, and create a segment
     * tree on the sum of the path from the root up to this node.
     */
    fio;
    size_t n, q;
    cin >> n >> q;
    vector<size_t> order(n), value(n), span(n);
    vector<ll> trav_value(n, 0), diff(n, 0);
    vector<vector<size_t>> adj(n);
    BitVector vis(n);
    size_t t = 0;

    foraz(i, 0, n) { cin >> value[i]; }
    foraz(i, 1, n) {
        size_t a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    st<size_t> dfs;
    dfs.ps(0);
    ll psum = 0;
    while (!dfs.empty()) {
        const auto cur = dfs.tp;
        if (!vis.get(cur)) {
            order[cur] = t;
            psum += value[cur];
            trav_value[t++] = psum;
            vis.set(cur);
        } else {
            span[cur] = t;
            psum -= value[cur];
            dfs.pp;
            continue;
        }
        for (const auto &nbr : adj[cur]) {
            if (vis.get(nbr)) {
                continue;
            }
            dfs.ps(nbr);
        }
    }
    diff[0] = trav_value[0];
    foraz(i, 1, n) { diff[i] = trav_value[i] - trav_value[i - 1]; }
    SegmentTree<ll, ladd_node> seg(diff);

    while (q--) {
        size_t comm, s, x;
        cin >> comm >> s;
        s--;
        if (comm == 1) {
            cin >> x;
            auto v_diff = static_cast<ll>(x) - static_cast<ll>(value[s]);
            value[s] = x;
            diff[order[s]] += v_diff;
            seg.update(order[s], diff[order[s]]);
            if (span[s] < n) {
                diff[span[s]] -= v_diff;
                seg.update(span[s], diff[span[s]]);
            }
        } else {
            cout << seg.queryRange(0, order[s] + 1).val << edl;
        }
    }
    return 0;
}
