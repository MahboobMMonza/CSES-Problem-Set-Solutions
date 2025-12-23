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

    bool get(const size_t i) {
        return (v[i >> 6] & (1 << (i & 63)));
    }

    void set(const size_t i) {
        v[i >> 6] |= (1 << (i & 63));
    }

    void clear(const size_t i) {
        v[i >> 6] &= ~(1 << (i & 63));
    }

    void toggle(const size_t i) {
        v[i >> 6] ^= (1 << (i & 63));
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
    execute(int a, int &idx, int nbrIdx, int prvNbr, vector<int> &heads, vector<edge> &edges, vector<int> &index,
            vector<int> &low, st<int> &stk, BitVector &onStk, st<tuple<int, int, int, ICommand &> > &calls) = 0;

    virtual ~ICommand() = default;
};

class CompleteCommand final : public ICommand {
public:
    void execute(const int a, int &idx, int nbrIdx, int prvNbr, vector<int> &heads, vector<edge> &edges,
                 vector<int> &index, vector<int> &low, st<int> &stk, BitVector &onStk,
                 st<tuple<int, int, int, ICommand &> > &calls) override {
        // Update lowlink only if this is still on stack
        if (!onStk.get(a)) return;
        // No need to do anything else if we are not the lowest id of a cycle
        if (low[a] != index[a]) return;
        // Update lowlink of each node in the cycle and remove from stack
        onStk.clear(a);
        int cur = stk.tp;
        stk.pp;
        while (!stk.empty()) {
            onStk.clear(cur);
            low[cur] = index[a];
            if (cur == a) {
                break;
            }
            cur = stk.tp;
            stk.pp;
        }
    }
};

class VisitCommand final : public ICommand {
private:
    ICommand &completed;

public:
    explicit VisitCommand(ICommand &completed) : completed(completed) {
    }

    void execute(const int a, int &idx, int nbrIdx, int prvNbr, vector<int> &heads, vector<edge> &edges,
                 vector<int> &index, vector<int> &low, st<int> &stk, BitVector &onStk,
                 st<tuple<int, int, int, ICommand &> > &calls) override {
        // Make sure we haven't completely visited this node, classic iterative DFS safeguard
        if (index[a] != -1 && nbrIdx == -1 && prvNbr == -1) return;
        // Come back to complete it at the end
        // Initial adding of this node to the component stack
        if (nbrIdx == heads[a]) {
            calls.emplace(a, -1, -1, completed);
            stk.emplace(a);
            onStk.set(a);
            index[a] = low[a] = idx++;
        }
        // If some previous neighbour was just visited
        if (prvNbr != -1) {
            low[a] = min(low[a], low[prvNbr]);
        }
        for (; nbrIdx != -1; nbrIdx = edges[nbrIdx].nxt) {
            const int &nbr = edges[nbrIdx].to;
            const int &next = edges[nbrIdx].nxt;
            if (index[nbr] == -1) {
                calls.emplace(a, next, nbr, *this);
                calls.emplace(nbr, heads[nbr], -1, *this);
                break;
            }
            if (onStk.get(nbr)) {
                low[a] = min(low[a], low[nbr]);
            }
        }
    }
};

void tarjan(const int n, vector<int> &heads, vector<edge> &edges, vector<int> &index, vector<int> &low) {
    CompleteCommand complete;
    VisitCommand visit(complete);
    st<int> stk;
    BitVector onStk(n);
    st<tuple<int, int, int, ICommand &> > calls;
    int idx = 0;
    fora(i, 0, n) {
        if (index[i] == -1) {
            calls.emplace(i, heads[i], -1, visit);
            while (!calls.empty()) {
                const auto cur = get<0>(calls.tp);
                const auto nbrIdx = get<1>(calls.tp);
                auto prvNbr = get<2>(calls.tp);
                auto &cmd = get<3>(calls.tp);
                calls.pp;
                cmd.execute(cur, idx, nbrIdx, prvNbr, heads, edges, index, low, stk, onStk, calls);
            }
        }
    }
}

int main() {
    /**
     * Run SCC, and if there is more than 1 component, then they can't be visited.
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
