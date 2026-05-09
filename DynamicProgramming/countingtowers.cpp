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

typedef unsigned long long ull;
typedef unsigned int uint;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pl;
typedef pair<ull, ull> pull;
typedef pair<int, pi> pii;
typedef pair<ll, pl> pll;
typedef pair<pi, pi> ppi;
typedef pair<char, int> pci;

struct custom_hash {
    static ull splitmix64(ull x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    ull operator()(const ull x) const {
        static const ull FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    size_t operator()(const pi &x) const {
        static const size_t FIXED_RANDOM = static_cast<size_t>(chrono::steady_clock::now().time_since_epoch().count());
        auto packed = (static_cast<ull>(x.fs) << 32) | static_cast<ull>(x.sc);
        return splitmix64(packed + FIXED_RANDOM);
    }
};

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

    void clearAll() {
        fill(v.begin(), v.end(), 0);
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
    int to = -1;
    int nxt = -1;
    int flow = 0;
    int max_capacity = 0;

    edge() = default;

    edge(const int _to, const int _nxt, const int _flow, const int _cap) : to(_to), nxt(_nxt), flow(_flow), max_capacity
                                                                           (_cap) {
    }

    int getCapacity() const {
        return max_capacity - flow;
    }
} edge;

inline ull getCount(const vector<vector<ull> > &towers, const size_t i, const ull MOD) {
    return (towers[1][i] + towers[2][i]) % MOD;
}

int main() {
    /**
     * Use DP counting strategy (similar to counting number of ways to make a sum given given a set of coins). Only
     * difference is here, the transition needs to be mapped out clearly. For simplicity, we are rotating the tower
     * 90 degrees clockwise. Take as transition point a 2 x 2 junction, excluding the outer edges. This creates 8
     * types of junctions:
     *
     * &&   && | &&-| && |-&&-|-&&---&&-u-&&-d-&&
     *
     * Where u represents a line along the top (i.e left side in tower) and d represents alone along the bottom (i.e.
     * right side in tower).
     *
     * Label each of these in order from 0 to 7. When viewing transitions (in the rotated prespective), take the
     * right side of the junction, and try to match features with the left side of the connecting junction. This
     * means an empty right side, such as the one in junction 0, can only connect with an empty left side, like
     * junction 1. Once all transitions are mapped out, the base (starting) and end cases need to be outlined. For
     * the base case, consider the empty space to the left of the rotated 2x1 block space as part of the junction.
     * There are two possible start cases: 2 1x1 blocks stacked (junction 3) or a single 2x1 block (junction 1). For
     * the end case, take the empty space to the right side of the tower along with the last 2x1 block space as the
     * junction. The only endings can be 2 1x1 blocks stacked (junction 2) or again a 2x1 block (junction 1). When a
     * height is thereby provided, the number of total solutions is the sum of the # of towers of height h ending with
     * J2 + # of towers of height h ending with J1, modulo 1e9+7.
     *
     * Note, the transition states can be further simplified to 2, but this space optimization is not necessary to AC
     * the problem.
     *
     * Precompute the entire table up to 1 million beforehand, and then query the table as stated above at dp[h].
     */
    fio;
    constexpr size_t MAXN = 1e6 + 1;
    constexpr ull MOD = 1e9 + 7;
    vector<vector<ull> > towers(8, vector<ull>(MAXN, 0));
    vector<vector<size_t> > transitions(8, vector<size_t>());
    // Set up transition table
    transitions[0] = {0, 1, 3};
    transitions[1] = {0, 1, 3};
    transitions[2] = {0, 1, 3};
    transitions[3] = {2, 4, 5, 6, 7};
    transitions[4] = {2, 4, 5, 6, 7};
    transitions[5] = {2, 4, 5, 6, 7};
    transitions[6] = {2, 4, 5, 6, 7};
    transitions[7] = {2, 4, 5, 6, 7};
    // Base case
    towers[1][0] = 1;
    towers[3][0] = 1;
    // Populate table full table. NOTE: at MAXN column, only idx 1 and 3 are valid
    foraz(i, 0, MAXN - 1) {
        foraz(j, 0, transitions.size()) {
            foraz(k, 0, transitions[j].size()) {
                const auto &nxt = transitions[j][k];
                towers[nxt][i + 1] += towers[j][i];
                towers[nxt][i + 1] %= MOD;
            }
        }
    }
    // Read queries and answer accordingly
    size_t t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        cout << getCount(towers, n, MOD) << edl;
    }
    return 0;
}
