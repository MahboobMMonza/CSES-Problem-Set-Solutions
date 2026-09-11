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
        return SegNode(min(l.val, r.val));
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

template<typename T, typename = typename enable_if<is_arithmetic<T>::value>::type>
bool oneSidedSegment(const array<pair<T, T>, 2> &edge, const array<pair<T, T>, 2> &segment) {
    constexpr auto ZERO = T{};
    auto basis = Vec2D(edge);
    auto top = Vec2D(edge[0], segment[0]);
    auto bottom = Vec2D(edge[0], segment[1]);
    auto top_res = basis ^ top, bot_res = basis ^ bottom;
    auto no_zeros = (top_res != ZERO && bot_res != ZERO);
    auto both_zeros = (top_res == ZERO && bot_res == ZERO);
    if (both_zeros) {
        return (edge[1] < segment[0]);
    }
    if constexpr (is_floating_point_v<T>) {
        return no_zeros && signbit(top_res) == signbit(bot_res);
    }
    return no_zeros && (top_res > ZERO) == (bot_res > ZERO);
}

template<typename T, typename = typename enable_if<is_arithmetic<T>::value>::type>
bool borders(const array<pair<T, T>, 2> &edge, const pair<T, T> &point) {
    static constexpr auto ZERO = T{};
    auto basis = Vec2D(edge[0], edge[1]);
    auto test = Vec2D(edge[0], point);
    auto result = basis ^ test;
    if (result != ZERO) return false;
    return (edge[0] <= point && point <= edge[1]) || (edge[1] <= point && point <= edge[0]);
}

int main() {
    /**
     * To find if a point lies on the border, check if it touches the edge and that the point falls
     * between the two vertices forming the edge.
     *
     * Once a point is ruled out for touching the border, draw a vertical line from the point to
     * infinity, and count the number of intersections with the polygon edges. If it is even,
     * then the point is outside the polygon, and if it is odd then it lies inside. Issue is a
     * true vertical line causes issues if the polygon shares an x-coordinate vertex with ray,
     * so instead cast the ray as moving one unit to the left from the point and infinity up.
     */
    fio;
    size_t n, m;
    vector<pair<ll, ll>> polygon;
    array<pair<ll, ll>, 2> ray;
    ray[1].sc = static_cast<ll>(numeric_limits<int>::max());
    cin >> n >> m;
    foraz(i, 0, n) {
        ll x, y;
        cin >> x >> y;
        polygon.eb(x, y);
    }
    polygon.pb(polygon.front());
    foraz(i, 0, m) {
        pair<ll, ll> point;
        cin >> point.fs >> point.sc;
        ray[0] = point;
        ray[1].fs = point.fs + 1ll;
        bool border = false;
        array<pair<ll, ll>, 2> edge;
        auto intersections = 0, same_x = 0;
        for (int i = 0; i < n; i++) {
            edge[0] = polygon[i], edge[1] = polygon[i + 1];
            // border check
            border = borders(edge, point);
            if (border) {
                break;
            }
            bool miss = oneSidedSegment(edge, ray) || oneSidedSegment(ray, edge);
            if (!miss) intersections++;
        }
        if (border) {
            cout << "BOUNDARY" << endl;
        } else if (intersections&1) {
            cout << "INSIDE" << edl;
        } else {
            cout << "OUTSIDE" << edl;
        }
    }
    return 0;
}
