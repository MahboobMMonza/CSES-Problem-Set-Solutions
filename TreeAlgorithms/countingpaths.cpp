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

size_t min(size_t a, size_t b, const vector<size_t> &depth) {
    return (depth[a] <= depth[b]) ? a : b;
}

int main() {
    /**
     * If we denote l as LCA(a, b), the path a -> b affects the nodes from a up
     * its parents to l and also from b up its parents to l. If we naively
     * implemented an algorithm that incremented all these nodes on a walk, we
     * would double count l. Since this is in effect applying range updates to
     * [a -> l] and [b -> l], and all updates are done _before_ queries, we can
     * treat this as some batch of static range update queries; this means we
     * can use a difference array to track the count changes, then sum them all
     * up in some fashion to get the final result. However, it is rarely the
     * case in a flattened tree representation results, so some clever
     * workarounds are necessary.
     *
     * From Subtree Queries, we know that all nodes in the subtree of x are
     * situated directly beside x in the flattened array. We can structure our
     * updates in such a way that getting the final answer for x would look at
     * the net sum of the changes which occurred in the subtree of x.
     *
     * Considering the update as two separate changes from a and b respectively
     * up to l, we see that the subtrees of a, b, l, and all parents of l are
     * affected. If we only incremented a and b's positions in the traversal,
     * then there will be a double count for l and all parents of l up to the
     * root. We can fix this double count by placing one decrement at l and
     * another decrement at the direct parent of l. This means when the overall
     * changes are pushed by taking the running sum from the root, unwanted
     * changes above l are cancelled out and l is not double counted. If we just
     * take the running sum as difference arrays do after all updates are made,
     * then arr[a] is a PSA of all changes from the root down to a, including
     * paths not from the root to a. We mitigate this by taking the range sum of
     * the subtree of a, because:
     *      1. all unrelated paths from the root spanning up to a will also be
     *         counted from the root to any child of a and thereby cancelled
     *         out.
     *      2. any paths in the subtree of a whose LCA is a child of a will
     *         have both increments and decrements within the subtree,
     *         resulting in a net 0 effect on a.
     *      3. any paths for which a is the LCA will have a correct +1 net
     *         effect as both +1's from the endpoints and a single -1 at a will
     *         be included in the sum.
     *      4. any path for which a is an endpoint and not the LCA will have
     *         only its +1 effect since b lies beyond the subtree of a and the
     *         effects of all nodes before a in the traversal are cancelled.
     */
    fio;
    size_t n, m;
    cin >> n >> m;
    const size_t tour_size = 2 * n - 1;
    const auto log_tour = 64 - static_cast<size_t>(__builtin_clzll(tour_size));

    vector<vector<size_t>> adj(n), sparse(log_tour, vector<size_t>(tour_size));
    vector<size_t> depth(n, n), heads(n, 0), seen(n, 0), parent(n, 0);
    BitVector vis(n), discovered(n);

    vector<size_t> order(n), span(n);
    vector<ll> diff(n + 1, 0);

    foraz(i, 1, n) {
        size_t a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    st<size_t> dfs;
    depth[0] = 0;
    dfs.ps(0);
    vis.set(0);

    size_t t = 0, f = 0;
    while (!dfs.empty()) {
        const auto &cur = dfs.tp;
        seen[cur] = t;
        sparse[0][t++] = cur;
        if (!discovered.get(cur)) {
            discovered.set(cur);
            order[cur] = f++;
            span[cur] = f;
        } else {
            span[cur] = f;
        }
        const auto &conns = adj[cur];
        auto &nbr_idx = heads[cur];
        while (nbr_idx < conns.size() && vis.get(conns[nbr_idx])) {
            nbr_idx++;
        }
        if (nbr_idx >= conns.size()) {
            dfs.pp;
            continue;
        }
        const auto &nbr = conns[nbr_idx];
        vis.set(conns[nbr_idx]);
        depth[conns[nbr_idx]] = depth[cur] + 1;
        parent[nbr] = cur;
        dfs.ps(conns[nbr_idx++]);
    }

    foraz(i, 1, log_tour) {
        const size_t pow = 1 << i;
        // correctness is provable
        foraz(j, 0, tour_size + 1 - pow) {
            sparse[i][j] =
                min(sparse[i - 1][j], sparse[i - 1][j + (pow >> 1)], depth);
        }
    }

    while (m--) {
        size_t a, b;
        cin >> a >> b;
        a--, b--;
        auto idx_a = seen[a], idx_b = seen[b];
        if (idx_a > idx_b) {
            swap(idx_a, idx_b);
            swap(a, b);
        }
        auto k = 63 - static_cast<size_t>(__builtin_clzll(idx_b - idx_a + 1));
        auto lca =
            min(sparse[k][idx_a], sparse[k][idx_b - (1 << k) + 1], depth);
        diff[order[a]]++, diff[order[b]]++;
        diff[order[lca]]--;
        if (lca != 0) {
            diff[order[parent[lca]]]--;
        }
    }
    foraez(i, 1, n) { diff[i] += diff[i - 1]; }
    cout << diff.back();
    foraz(i, 1, n) { cout << ' ' << diff[span[i] - 1] - diff[order[i] - 1]; }
    return 0;
}
