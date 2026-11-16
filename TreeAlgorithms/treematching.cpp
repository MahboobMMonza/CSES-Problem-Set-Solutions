#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

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
#define MOD (int) (1e9 + 7)

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<size_t, size_t> pz;
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
        if (y & 1) res = (res + x) % m;
        if (res < 0) res += m;
        x = (x << 1) % m;
        y >>= 1;
    }
    return res % m;
}

inline ll logPow(ll x, ll y, ll m = numeric_limits<ll>::max()) {
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

struct custom_hash {
    static ull splitmix64(ull x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    ull operator()(ull x) const {
        static const ull FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    size_t operator()(const pz &x) const {
        static const size_t FIXED_RANDOM = static_cast<size_t>(chrono::steady_clock::now().time_since_epoch().count());
        auto packed = (static_cast<ull>(x.fs) << 32) | static_cast<ull>(x.sc);
        return splitmix64(packed + FIXED_RANDOM);
    }
};

template<typename T>
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T, typename K>
using indexed_map = tree<T, K, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename Derived, typename T>
class ISegNode {
public:
    static Derived create(const T& val) {
        return Derived::create_impl(val);
    }

    static Derived op(const Derived &l, const Derived &r) {
        return Derived::op_impl(l, r);
    }
};

template<typename T, T neutral>
class SegNode : public ISegNode<SegNode<T, neutral>, T> {
public:
    T val;

    SegNode() : val(neutral) {}
    SegNode(T value) : val(value) {}

    static SegNode create_impl(T val) {
        return SegNode(val);
    }

    static SegNode op_impl(const SegNode &l, const SegNode &r) {
        return SegNode(l.val + r.val);
    }
};

template<typename T, typename D>
class SegmentTree {
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

    SegmentTree(const size_t &n) : sz(n) {
        rangeData.resize(2 * n);
    }

    void update(size_t i, const T& value) {
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
            if (l&1) {
                if (!lefted) {
                    left = rangeData[l];
                    lefted = true;
                } else {
                    left = D::op(left, rangeData[l]);
                }
                l++;
            }
            if (r&1) {
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
        if (!lefted) return right;
        if (!righted) return left;
        return D::op(left, right);
    }

};

typedef SegNode<int, 0> iadd_node;

template<typename T, typename = typename enable_if<is_arithmetic<T>::value>::type>
struct Vec2D {
    T x{}, y{};

    Vec2D() {}

    Vec2D(T x_val, T y_val) : x(x_val), y(y_val) {}

    Vec2D(const array<pair<T, T>, 2> &coords) : Vec2D(coords[0], coords[1]) {}

    Vec2D(const pair<T, T> &anchor, const pair<T, T> &tip) {
        x = tip.fs - anchor.fs;
        y = tip.sc - anchor.sc;
    }

    T norm() const {
        return x * x + y * y;
    }

    T operator^(const Vec2D &other) const {
        return (x * other.y) - (other.x * y);
    }

    Vec2D operator*(const T& k) const {
        return Vec2D(k * x, k * y);
    }

    Vec2D operator+(const Vec2D &other) const {
        return Vec2D(x + other.x, y + other.y);
    }

    Vec2D operator-(const Vec2D &other) const {
        return Vec2D(x - other.x, y - other.y);
    }

    Vec2D operator-() const {
        return Vec2D(-x, -y);
    }
};

class BitVector {
public:
    explicit BitVector(const size_t n) : v((n + 63) >> 6, 0) {
    };

    ~BitVector() = default;

    bool get(const size_t i) const {
        return v[i >> 6] & (1ull << (i & 63));
    }

    void set(const size_t i) {
        v[i >> 6] |= 1ull << (i & 63);
    }

    void clear(const size_t i) {
        v[i >> 6] &= ~(1ull << (i & 63));
    }

    void toggle(const size_t i) {
        v[i >> 6] ^= 1ull << (i & 63);
    }

    void clear() {
        fill(v.begin(), v.end(), 0);
    }

    void set() {
        fill(v.begin(), v.end(), 0xFFFFFFFFFFFFFFFF);
    }

    static string to_string(const BitVector &bv) {
        ostringstream ss;
        for (const auto &x: bv.v) {
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
     * This can be done greedily or with DP. This solution will be greedy.
     *
     * Traverse the tree in bottom-up traversal, skipping any nodes that are
     * already marked. If a node is unmarked and has an unmarked neighbour,
     * then increment the count and mark this node and the neighbour as taken
     * and move on to the next node in the traversal.
     *
     * To get bottom-up traversal, conduct a BFS from an arbitrary root node
     * and iterate the nodes in reverse of when they were visited in the BFS.
     */
    fio;
    size_t n, ans = 0;
    vector<vector<size_t>> adj;
    cin >> n;
    BitVector vis(n);
    adj.resize(n);
    foraz(i, 0, n - 1) {
        size_t u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<size_t> order;
    size_t f = 0;
    order.pb(0);
    vis.set(0);
    while (f < n) {
        const auto cur = order[f++];
        for (const auto& nbr : adj[cur]) {
            if (vis.get(nbr)) continue;
            vis.set(nbr);
            order.pb(nbr);
        }
    }
    vis.clear();
    ford0z(i, n - 1, n) {
        const auto& cur = order[i];
        if (vis.get(cur)) continue;
        for (const auto& nbr : adj[cur]) {
            if (vis.get(nbr)) continue;
            vis.set(cur);
            vis.set(nbr);
            ans++;
            break;
        }
    }
    cout << ans << edl;
    return 0;
}
