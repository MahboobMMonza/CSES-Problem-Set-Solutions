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

template<typename T>
class BIT {
private:
    vector<T> rangeData;
    function<T(T, T)> op, inverse;

    inline size_t lsb(size_t i) {
        return i & -i;
    }

    inline T prefix_op(size_t i) {
        T res = rangeData[0];
        while (i) {
            res = op(res, rangeData[i]);
            i &= ~lsb(i);
        }
        return res;
    }

public:
    BIT(vector<T> &data, function<T(T, T)> op, function<T(T, T)> inverse, T neutral) {
        rangeData = vector<T>(data.size() + 1);
        copy(data.begin(), data.end(), rangeData.begin() + 1);
        for (size_t i = 1; i < rangeData.size(); ++i) {
            size_t j = i + lsb(i);
            if (j < rangeData.size()) rangeData[j] = op(rangeData[j], rangeData[i]);
        }
        this->op = op;
        this->inverse = inverse;
        rangeData[0] = neutral;
    }

    T queryRange(size_t a, size_t b) {
        return inverse(prefix_op(b), prefix_op(a - 1));
    }

    void update(size_t i, T value) {
        while (i < rangeData.size()) {
            rangeData[i] = op(rangeData[i], value);
            i += lsb(i);
        }
    }

    void set(size_t i, T value) {
        T prev = queryRange(i, i);
        T delta = inverse(value, prev);
        update(i, delta);
    }

};

inline ll add(ll a, ll b) {
    return a + b;
}

inline ll subtract(ll a, ll b) {
    return a - b;
}

int main() {
    /**
     * Fenwick tree/BIT. Made mine slightly more general since any associative operation will do.
     */
    fio;
    int n, q, t;
    size_t a;
    ll b;
    cin >> n >> q;
    vector<ll> data(n);
    fora(i, 0, n) {
        cin >> data[i];
    }
    BIT<ll> fenwick(data, add, subtract, 0ll);
    while (q--) {
        cin >> t >> a >> b;
        if (t == 1) {
            fenwick.set(a, b);
        } else {
            cout << fenwick.queryRange(a, (size_t) b) << edl;
        }
    }
    return 0;
}
