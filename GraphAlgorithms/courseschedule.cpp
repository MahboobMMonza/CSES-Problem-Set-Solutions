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

inline bool isSet(const size_t a, const vector<ll> &vis) {
    return vis[a >> 6] & (1ll << (63 - (a % 64)));
}

inline void toggleBit(const size_t a, vector<ll> &vis) {
    vis[a >> 6] ^= (1ll << (63 - (a % 64)));
}

typedef struct edge {
    int to;
    int nxt;
} edge;

class ICommand {
public:
    virtual bool
    execute(int a, vector<int> &heads, vector<edge> &edges, vector<ll> &marks, st<pair<int, ICommand &>> &stk,
            vector<int> &order) = 0;

    virtual ~ICommand() = default;
};

class CompleteCommand : public ICommand {
public:
    bool execute(int a, vector<int> &heads, vector<edge> &edges, vector<ll> &marks, st<pair<int, ICommand &>> &stk,
                 vector<int> &order) override {
        if (isSet(a + heads.size(), marks)) {
            return true;
        }
        toggleBit(a, marks);
        toggleBit(a + heads.size(), marks);
        order.pb(a);
        return true;
    }
};

class VisitCommand : public ICommand {
private:
    ICommand &completed;
public:
    explicit VisitCommand(ICommand &completed) : completed(completed) {}

    bool execute(int a, vector<int> &heads, vector<edge> &edges, vector<ll> &marks, st<pair<int, ICommand &>> &stk,
                 vector<int> &order) override {
        if (isSet(a + heads.size(), marks)) {
            return true;
        }
        toggleBit(a, marks);
        for (int idx = heads[a]; idx != -1; idx = edges[idx].nxt) {
            int nbr = edges[idx].to;
            if (isSet(nbr + heads.size(), marks)) {
                continue;
            }
            if (isSet(nbr, marks)) {
                return false;
            }
            stk.emplace(nbr, completed);
            stk.emplace(nbr, *this);
        }
        return true;
    }
};

bool dfs(int a, vector<int> &heads, vector<edge> &edges, vector<ll> &marks, st<pair<int, ICommand &>> &stk,
         vector<int> &order, ICommand &complete, ICommand &visit) {
    stk.emplace(a, complete);
    stk.emplace(a, visit);
    while (!stk.empty()) {
        ICommand &command = stk.tp.sc;
        int cur = stk.tp.fs;
        stk.pp;
        bool res = command.execute(cur, heads, edges, marks, stk, order);
        if (!res) {
            return false;
        }
    }
    return true;
}

inline bool
topologicalSort(vector<int> &heads, vector<edge> &edges, vector<ll> &marks, st<pair<int, ICommand &>> &stk,
                vector<int> &order) {
    CompleteCommand complete;
    VisitCommand visit(complete);
    // marks: [0, n) -> temporary; [n, 2n) -> permanent
    fora(i, 0, heads.size()) {
        if (isSet(heads.size() + i, marks)) {
            continue;
        }
        if (!dfs(i, heads, edges, marks, stk, order, complete, visit)) {
            return false;
        }
    }
    return true;
}

int main() {
    /**
     * Topological sort using DFS because why not? Just note that the order is reversed when the list is made, so print
     * backwards.
     */
    fio;
    int n, m, a, b;
    cin >> n >> m;
    vector<int> heads(n, -1), order;
    order.reserve(n);
    vector<ll> marks(((2 * n) + 63) >> 6, 0);
    vector<edge> edges(m);
    st<pair<int, ICommand &>> stk;
    fora(i, 0, m) {
        cin >> a >> b;
        edges[i].to = --b;
        edges[i].nxt = heads[--a];
        heads[a] = i;
    }
    if (!topologicalSort(heads, edges, marks, stk, order)) {
        cout << "IMPOSSIBLE" << edl;
        return 0;
    }
    ford(i, n - 1, 0) {
        cout << order[i] + 1 << ' ';
    }
    cout << order[0] + 1 << edl;
    return 0;
}
