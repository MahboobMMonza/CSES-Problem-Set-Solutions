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
typedef pair<ll, int> pli;
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

typedef struct edge {
    int to;
    int nxt;
} edge;

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

void cycleLengths(int a, const vector<int> &next, BitVector &marks, vector<int> &dists, vector<int> &components,
                  vector<int> &leads) {
    st<pi> stk;
    stk.emplace(0, a);
    marks.set(a);
    int dist = 0;
    int comp = -1, lead = -1;
    bool out_cycle = false;
    while (!stk.empty()) {
        const int command = stk.tp.fs, cur = stk.tp.sc;
        stk.pp;
        if (command) {
            if (!out_cycle) {
                components[cur] = comp;
            }
            leads[cur] = lead;
            dists[cur] = ++dist;
            if (cur == comp) {
                out_cycle = true;
                lead = comp;
                dist = 0;
            }
            continue;
        }
        const int succ = next[cur];
        // If we have already traversed part of the graph, by necessity the new search is from a predecessor to the
        // cycle.
        if (dists[succ] >= 0) {
            if (leads[succ] == -1) {
                lead = succ;
            } else {
                lead = leads[succ];
                dist = dists[succ];
            }
            dists[cur] = ++dist;
            leads[cur] = lead;
            continue;
        }
        stk.emplace(1, cur);
        if (marks.get(succ)) {
            comp = succ;
            continue;
        }
        stk.emplace(0, succ);
        marks.set(succ);
    }
}

int traverse(const int start, const int k, const vector<vector<int> > &successor) {
    int ans = start;
    for (int power = 32 - __builtin_clz(k); power >= 0; power--) {
        if (k & (1 << power)) {
            ans = successor[power][ans];
        }
    }
    return ans;
}

int walk(const int a, const int b, const vector<int> &dists, const vector<vector<int> > &successor) {
    if (dists[b] > dists[a]) return -1;
    const int diff = dists[a] - dists[b];
    const int land = traverse(a, diff, successor);
    if (land != b) return -1;
    return diff;
}

int main() {
    /**
     * See Planet Queries 2 solution for the full breakdown on how to find cycle lengths/leads in DFS. The required
     * information is tracked in dists[] array, components[] array, and leads[] array. Run the DFS, and then for each
     * node, check if it is part of a cyclic component. If so, print the size of the component. Otherwise, print the
     * distance of the node to its lead (which is already stored in dist[]) + size of the component the lead node is in.
     */
    fio;
    int n;
    cin >> n;
    vector<int> dists(n, -1), components(n, -1), leads(n, -1);
    vector<int> successor(n);
    BitVector marks(n);
    st<pi> stk;
    fora(i, 0, n) {
        cin >> successor[i];
        successor[i]--;
    }
    fora(i, 0, n) {
        if (dists[i] == -1) cycleLengths(i, successor, marks, dists, components, leads);
        if (components[i] != -1) {
            cout << dists[components[i]];
        } else {
            cout << dists[i] + dists[components[leads[i]]];
        }
        cout << ' ';
    }
    return 0;
}