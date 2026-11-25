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
typedef __int128_t gll;
typedef __uint128_t gull;
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

template <typename T,
          typename = typename enable_if<is_arithmetic<T>::value>::type>
struct Vec2D {
    T x{}, y{};

    Vec2D() {}

    Vec2D(T x_val, T y_val) : x(x_val), y(y_val) {}

    Vec2D(const array<pair<T, T>, 2> &coords) : Vec2D(coords[0], coords[1]) {}

    Vec2D(const pair<T, T> &anchor, const pair<T, T> &tip) {
        x = tip.fs - anchor.fs;
        y = tip.sc - anchor.sc;
    }

    T norm() const { return x * x + y * y; }

    T operator^(const Vec2D &other) const {
        return (x * other.y) - (other.x * y);
    }

    Vec2D operator*(const T &k) const { return Vec2D(k * x, k * y); }

    Vec2D operator+(const Vec2D &other) const {
        return Vec2D(x + other.x, y + other.y);
    }

    Vec2D operator-(const Vec2D &other) const {
        return Vec2D(x - other.x, y - other.y);
    }

    Vec2D operator-() const { return Vec2D(-x, -y); }
};

ostream& operator<<(ostream& os, gull val) {
    static constexpr gull K_1E18 = 1000000000000000000ll;
    ull parts[3];
    size_t c = 0;
    while (val > 0) {
        parts[c++] = static_cast<ull>(val % K_1E18);
        val /= K_1E18;
    }
    os << parts[c - 1];
    auto old = os.fill('0');
    ford0z(i, c - 2, c) {
        os << setw(18) << parts[i];
    }
    os.fill(old);
    return os;
}

ostream& operator<<(ostream& os, gll val) {
    if (val < 0) {
        os << '-';
        return os << static_cast<gull>(0 - static_cast<gull>(val));
    }
    return os << static_cast<gull>(val);
}

int main() {
    /**
     * Sort the x and y coordinates separately, then take prefix sums on them.
     * Then iterating i in [1, n - 1], sum the following for both x and y:
     * (coord[i] * i) - psa_coord[i - 1]. The sorting is necessary to ensure
     * that an x distance or a y distance difference is always non-negative.
     *
     * Even with this, the sum of all distances can overflow 64-bit integers.
     * Use __int128_t to handle the summation. We consequently need a special
     * function to write the __int128_t value to output. This is classic binary
     * to decimal conversion, except we needn't restrict ourselves to base 10:
     * we can work in base 10^18 as this fits inside 64 bit integer, and pad
     * lower place values with 0's to make them 18 digits wide.
     */
    fio;
    size_t n;
    cin >> n;
    if (n == 1) {
        cout << 0 << edl;
        return 0;
    }
    vector<ll> x(n), y(n);
    foraz(i, 0, n) { cin >> x[i] >> y[i]; }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    gll total = 0, sum_x = static_cast<gll>(x[0]),
         sum_y = static_cast<gll>(y[0]); // typedef for faster typing, giant ll
    foraz(i, 1, n) {
        auto gx = static_cast<gll>(x[i]);
        auto gy = static_cast<gll>(y[i]);
        total += gx * static_cast<ll>(i) - sum_x;
        total += gy * static_cast<ll>(i) - sum_y;
        sum_x += gx;
        sum_y += gy;
    }
    cout << total << edl;
    return 0;
}
