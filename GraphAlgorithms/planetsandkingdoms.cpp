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

typedef struct edge {
    int to;
    int nxt;
} edge;

class ICommand {
public:
    virtual void
    execute(int a, int &idx, vector<int> &heads, vector<edge> &edges, vector<int> &index, vector<int> &low,
            st<int> &stk, BitVector &onStk, BitVector &searching, st<tuple<int, ICommand &> > &calls) = 0;

    virtual ~ICommand() = default;
};

class CompleteCommand final : public ICommand {
public:
    void execute(const int a, int &idx, vector<int> &heads, vector<edge> &edges, vector<int> &index, vector<int> &low,
                 st<int> &stk, BitVector &onStk, BitVector &searching, st<tuple<int, ICommand &> > &calls) override {
        // Update lowlink only if this is still on stack
        // No need to do anything else if we are not the lowest id of a cycle
        if (!onStk.get(a) || low[a] != index[a]) return;
        // Update lowlink of each node in the cycle and remove from stack
        onStk.clear(a);
        do {
            const int cur = stk.tp;
            stk.pp;
            onStk.clear(cur);
            low[cur] = index[a];
            if (cur == a) {
                break;
            }
        } while (!stk.empty());
    }
};

class VisitCommand final : public ICommand {
private:
    ICommand &completed;

public:
    explicit VisitCommand(ICommand &completed) : completed(completed) {
    }

    void execute(const int a, int &idx, vector<int> &heads, vector<edge> &edges, vector<int> &index, vector<int>
        &low, st<int> &stk, BitVector &onStk, BitVector &searching, st<tuple<int, ICommand &> > &calls) override {
        // Make sure we haven't completely visited this node, classic iterative DFS safeguard
        if (index[a] != -1 && heads[a] == -1 && searching.get(a)) return;
        // Come back to complete it at the end
        // Initial adding of this node completion to the component stack
        if (!searching.get(a)) {
            calls.emplace(a, completed);
            stk.emplace(a);
            onStk.set(a);
            index[a] = low[a] = idx++;
        }
        int &nbrIdx = heads[a];
        // If some previous nbr was just visited, update our lowlink with that of the previously visited nbr
        if (searching.get(a)) {
            low[a] = min(low[a], low[edges[nbrIdx].to]);
        }
        // Iterate from the next nbr to visit and visit them, skipping already visited nbrs
        for (; nbrIdx != -1; nbrIdx = edges[nbrIdx].nxt) {
            const int &nbr = edges[nbrIdx].to;
            // We found a nbr that was not yet visited, update callstack to resume iteration from next point noting
            // that we visited this nbr, then visit that nbr with no previous visits.
            if (index[nbr] == -1) {
                calls.emplace(a, *this);
                calls.emplace(nbr, *this);
                searching.set(a);
                break;
            }
            // If the nbr has been visited but not completely, update our lowlink
            if (onStk.get(nbr)) {
                low[a] = min(low[a], low[nbr]);
            }
        }
    }
};

void tarjan(const int n, vector<int> &heads, vector<edge> &edges, vector<int> &index, vector<int> &low) {
    /**
     * Iterative version of Tarjan's algorithm. Use a call stack to trace the DFS with different commands and logic
     * for when a node is being visited or has finished visiting all its neighbours. Need to bookkeep the lowlink/index
     * tracker (idx) and the which neighbour was visited/will be visited next (use heads destructively). References
     * to heads, edges, index, and low represent the graph and the global data Tarjan's algorithm needs for SCC. If
     * it were a class, they would be public members. The onStk and searching set is another global variable required
     * by the algorithm but only for the search and does not need to be returned to the user.
     */
    CompleteCommand complete;
    VisitCommand visit(complete);
    st<int> stk;
    BitVector onStk(n), searching(n);
    st<tuple<int, ICommand &> > calls;
    int idx = 0;
    fora(i, 0, n) {
        if (index[i] == -1) {
            calls.emplace(i, visit);
            while (!calls.empty()) {
                const auto cur = get<0>(calls.tp);
                auto &cmd = get<1>(calls.tp);
                calls.pp;
                cmd.execute(cur, idx, heads, edges, index, low, stk, onStk, searching, calls);
            }
        }
    }
}

int main() {
    /**
     * Implement any strongly connected components algorithm (SCC) that runs in O(V + E). Selected Tarjan's as it is
     * single-pass, though it is complicated to run iteratively.
     */
    fio;
    int n, m, a, b;
    cin >> n >> m;
    vector<int> index(n, -1), low(n, -1), heads(n, -1);
    vector<edge> edges(m);
    fora(i, 0, m) {
        cin >> a >> b;
        edges[i].to = --b;
        edges[i].nxt = heads[--a];
        heads[a] = i;
    }
    tarjan(n, heads, edges, index, low);
    unordered_map<int, int> kingCompress;
    int kingdoms = 0;
    fora(i, 0, n) {
        if (!kingCompress.count(low[i])) {
            kingCompress[low[i]] = ++kingdoms;
        }
        low[i] = kingCompress[low[i]];
    }
    cout << kingdoms << edl;
    cout << low[0];
    fora(i, 1, n) {
        cout << " " << low[i];
    }
    cout << edl;
    return 0;
}
