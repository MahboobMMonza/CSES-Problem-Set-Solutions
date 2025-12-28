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
     * Store a count for each node how many edges it must traverse before it reaches/recognizes a cycle node using
     * for nodes that are not part of a cycle using DFS. For each non-cyclic node, also store which node in a cycle
     * its path leads to. For cyclic nodes, identify the component by one of the nodes in the cycle, and the distance
     * to the "head" of the cycle.
     *
     * This can be done in a single DFS by using an array to track dists, components, and leads. For components and
     * leads, if a node i is cyclic, leads[i] = -1, and for a non-cyclic node, components[i] = -1. For cyclic nodes,
     * dists[i] is the distance between node i and the defined head of the component. If the node is the head of the
     * component, then dists[i] is the size of the cycle. For non-cyclic nodes, dists[i] is the distance between the
     * current node and the first node in the path which is part of a cycle.
     *
     * In the DFS, if a cycle is found and its head is defined as the id of the already visited node. On the roll-back,
     * update dists and component id values until the cyclic node is rolled-back to. At the cyclic node, update
     * dists[i] and reset the distance tracker to 0. This node is now the lead node for any non-cyclic predecessors.
     * For the remaining roll-back calls, update dists[i] and set leads[i] to the head of the cycle.
     *
     * If the DFS finds some already processed successor (i.e. dists[succ] >= 0), set distance to be 1 + dists[succ]
     * then check if the successor node is a cyclic node (components[succ] != -1). If it is, set leads[i] to succ.
     * If it is not, then track the leads[succ]. On the roll-back, update distances and set leads[i] to the tracked
     * lead.
     *
     * Also construct a binary lifted successor graph to quickly find and confirm distances between two nodes not in a
     * cycle.
     *
     * For each query,
     * 1. Neither node is part of a cycle: If dists[a] <= dists[b], this implies that either a comes after b or that
     * they are not on the same path, so print -1. Otherwise, try to walk dists[a] - dists[b] nodes from a and see if
     * you land on b, in which case the distance is dists[a] - dists[b] else -1.
     * 2. Both nodes are in the same cycle: calculate the distance by (dists[a] - dists[b] + |C|) % |C|, where |C| is
     * the size of the component.
     * 3. Node a is not cyclic and b is cyclic: If leads[a] is not in the same cycle as b, print -1. Otherwise, we
     * need to traverse from node a to the first node in the cycle coming from a (leads[a]), then from leads[a] to b.
     * dists[a] stores the first part, and the second part is the distance between two nodes in a cycle which is
     * defined above, and the printed distance i the sum of the two parts.
     * 4. Both nodes are cyclic but in different components: Print -1.
     *
     * O(n) DFS + O(nlogn) binary lifting + O(logn) queries (worst case). Technically since we lift up to the same
     * power of two each time, it is O(n) lifting but the constant is large enough to be considered logn.
     */
    fio;
    int n, q;
    cin >> n >> q;
    vector<int> dists(n, -1), components(n, -1), leads(n, -1);
    vector<vector<int> > successor(30, vector<int>(n));
    BitVector marks(n);
    st<pi> stk;
    fora(i, 0, n) {
        cin >> successor[0][i];
        successor[0][i]--;
    }
    fora(step, 1, 30) {
        fora(i, 0, n) {
            successor[step][i] = successor[step - 1][successor[step - 1][i]];
        }
    }
    fora(i, 0, n) {
        if (dists[i] != -1) continue;
        cycleLengths(i, successor[0], marks, dists, components, leads);
    }
    while (q--) {
        int a, b, d = -1;
        cin >> a >> b;
        --a, --b;
        if (a == b) {
            d = 0;
        }
        // Both nodes are in a cycle, but not the same cycle
        else if (components[a] != components[b] && components[a] != -1 && components[b] != -1) {
            d = -1;
        }
        // Same component
        else if (components[a] == components[b] && components[a] != -1) {
            d = (dists[a] - dists[b] + dists[components[a]]) % dists[components[a]];
        }
        // One is the predecessor of the other, or they are not in the same tree, both not in cycle
        else if (components[a] == components[b] && components[a] == -1) {
            d = walk(a, b, dists, successor);
        } else if (components[a] == -1 && components[b] != -1) {
            const auto origin = leads[a];
            if (components[origin] == components[b]) {
                d = dists[a] + (dists[origin] - dists[b] + dists[components[origin]]) % dists[components[origin]];
            }
        }
        cout << d << edl;
    }
    return 0;
}
