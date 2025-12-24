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

int main() {
    /**
     * Classic longest common subsequence DP. Check every length sequence of a against every length sequence of b,
     * essentially LCS[i][j] = LCS of substring a[0...i] against substring b[0...j]. If a[i] == b[j], then add this
     * letter to the best LCS of a[0...i - 1] up to b[0...j - 1], which gives 1 + LCS[i - 1][j - 1]. Otherwise, LCS
     * is max(LCS[i - 1][j], LCS[i][j - 1]) (i.e. the best choice between not including a[i] and not including b[j]).
     *
     * Since the sequence needs to be reconstructed, cannot use the swap row technique for O(n) space. Don't include
     * row or column for null sequences, so do extra accounting for i == 0 or j == 0.
     *
     * To reconstruct the LCS, start at LCS[n - 1][m - 1] (0-indexed), and follow backwards (in the i - 1 or j - 1
     * directions) the largest LCS value neighbouring that cell. If LCS[i][j] > both LCS[i - 1][j] and LCS[i][j - 1],
     * then a take was performed on the element at a[i], in which case, navigate to LCS[i - 1][j - 1] and continue.
     * Whenever a take is performed, add a[i] to a stack. Continue until either i or j move backwards from 0. The
     * stack contains the LCS sequence in reverse order, so print it in reverse if using a vector, or print the top
     * element until the stack is empty.
     */
    fio;
    size_t n, m;
    cin >> n >> m;
    vector<vector<int>> lcs(n, vector<int>(m, 0));
    vector<int> a(n), b(m), seq;
    foraz(i, 0, n) cin >> a[i];
    foraz(i, 0, m) cin >> b[i];
    foraz(i, 0, n) {
        foraz(j, 0, m) {
            if (a[i] == b[j]) lcs[i][j] = 1 + (i == 0 || j == 0 ? 0 : lcs[i - 1][j - 1]);
            else lcs[i][j] = max(i == 0 ? 0 : lcs[i - 1][j], j == 0 ? 0 : lcs[i][j - 1]);
        }
    }
    size_t i = n - 1, j = m - 1;
    while (i < n && j < m) {
        if (lcs[i][j] > max(i == 0 ? 0 : lcs[i - 1][j], j == 0 ? 0 : lcs[i][j - 1])) {
            seq.push_back(a[i]);
            i--, j--;
        } else if (j > 0 && lcs[i][j] == lcs[i][j - 1]) {
            j--;
        } else {
            i--;
        }
    }
    cout << lcs[n - 1][m - 1] << edl;
    ford0z(idx, seq.size() - 1, seq.size()) {
        cout << seq[idx] << ' ';
    }
    return 0;
}