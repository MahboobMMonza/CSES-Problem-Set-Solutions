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
#define fora(i, a, b, c) for (int i = (a); i < (b); i += (c))
#define forae(i, a, b, c) for (int i = (a); i <= (b); i += (c))
#define ford(i, a, b, c) for (int i = (a); i > (b); i -= (c))
#define forde(i, a, b, c) for (int i = (a); i >= (b); i -= (c))
#define foral(i, a, b, c) for (long long i = (a); i < (b); i += (c))
#define forael(i, a, b, c) for (long long i = (a); i <= (b); i += (c))
#define fordl(i, a, b, c) for (long long i = (a); i > (b); i -= (c))
#define fordel(i, a, b, c) for (long long i = (a); i >= (b); i -= (c))
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

int main() {
    fio;
    // Edit distance is increased by 1 if the letters mismatch, but stays the same if they do match
    // Similar approach to LCS.
    vector<vector<int>> edit(2);
    string a, b;
    cin >> a >> b;
    fora(i, 0, 2, 1) {
        edit[i].resize(a.length() + 1);
    }
    // edit[i][j] represents the least number of moves to make the first i letters of b match the first j letters of a

    // If the letter at b[i] matches the letter of a[j], we don't need to make any modifications and can just look
    // at the best modifications for a[0...j-1] and b[0...i-1]

    // If the letters mismatch, then we are presented with 3 options.
    // Replace: Change b[0...i-1] to a[0...j-1] and change b[i] to a[j] (1 + edit[i - 1][j - 1])
    // Insert: Change b[0...i] to a[0...j-1] and add a[j] after b[i]    (1 + edit[i][j - 1])
    // Delete: Change b[0...i-1] to a[0...j] after removing b[i]        (1 + edit[i - 1][j])

    // Flip-grid table can be used (i&1 for current, 1 - i&1 for previous) since result only relies on previous row
    // Space optimization
    forae(i, 0, b.length(), 1) {
        forae(j, 0, a.length(), 1) {
            if (j == 0) {
                edit[i & 1][j] = i;
                continue;
            }
            if (i == 0) {
                edit[i & 1][j] = j;
                continue;
            }
            if (a[j - 1] == b[i - 1]) {
                // If the letters here are the same, make no change
                edit[i & 1][j] = edit[1 - i & 1][j - 1];
            } else {
                // If the letters mismatch, add a change to the lowest cost option so far
                // Inserting a letter means taking the best from edit[i][j - 1] and adding 1.
                // Deleting a letter means taking the best from edit[i - 1][j] and adding 1.
                // Replacing a letter is the same as taking the best from edit[i - 1][j - 1] and adding 1.
                edit[i & 1][j] = 1 + min(min(edit[1 - i & 1][j], edit[i & 1][j - 1]), edit[1 - i&1][j - 1]);
            }
        }
    }
    cout << edit[b.length() & 1][a.length()];
    return 0;
}