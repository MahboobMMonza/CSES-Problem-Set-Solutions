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
#define stk stack
#define pq priority_queue
#define fora(i, a, b, c) for (int i = (a); i < (b); i += (c))
#define forae(i, a, b, c) for (int i = (a); i <= (b); i += (c))
#define ford(i, a, b, c) for (int i = (a); i > (b); i -= (c))
#define forde(i, a, b, c) for (int i = (a); i >= (b); i -= (c))
#define foral(i, a, b, c) for (long long i = (a); i < (b); i += (c))
#define forael(i, a, b, c) for (long long i = (a); i <= (b); i += (c))
#define fordl(i, a, b, c) for (long long i = (a); i > (b); i -= (c))
#define fordel(i, a, b, c) for (long long i = (a); i >= (b); i -= (c))

typedef unsigned long long ull;
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

int main() {
    vector<int> p(8);
    // Read the board
    vector<string> board(8);
    int count = 0;
    // flag for a valid combo
    bool valid;
    fora(i,0,8,1) {
        cin >> board[i];
    }
    // Since we will never have 2 queens on the same column or row, we will have 8 different position on the 8 rows.
    // This simplifies what we need to keep track of. We now only need to check diagonals above for each position.
    // Also, each position will be a different value, so only checking permutations of the positions works instead of
    // backtracking.
    iota(p.begin(), p.end(), 0);
    do {
        valid = 1;
        // Check that the permutation consists of only open spaces.
        fora(i,0,8,1) {
            valid &= (board[i][p[i]] == '.');
        }
        if (!valid) continue;
        // Check left diagonal
        fora(i,1,8,1) {
            for(int j = p[i] - 1, k = i - 1; j >= 0 && k >= 0; j--, k--) {
                valid &= p[k] != j;
            }
        }
        // Check right diagonal
        fora(i,1,8,1) {
            for(int j = p[i] + 1, k = i - 1; j <= 7 && k >= 0; j++, k--) {
                valid &= p[k] != j;
            }
        }
        count += valid;
    } while (next_permutation(p.begin(),p.end()));
    cout << count << edl;
    return 0;
}