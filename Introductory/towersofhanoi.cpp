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
    fio;
    int n, c = 0;
    vector<stk<int>> towers(3);
    cin >> n;
    // 2^n - 1 moves needed
    cout << ((1 << n) - 1) << edl;
    // Create a stack to simulate the game, since towers of Hanoi is played with each tower acting like a stack
    for (int i = n; i >= 1; i--) {
        towers[0].ps(i);
    }
    while (!towers[0].empty() || !towers[1].empty()) {
        // Labeling leftmost tower as A and rightmost tower as C, from playing the game optimally this pattern of swaps
        // emerges. If for each swap sequence X/Y an item cannot be moved from X and placed on Y, then it is moved from
        // Y to X.
        // Even: A/B -> A/C -> B/C
        // Odd: A/C -> A/B -> B/C
        // A/B if even number rings and move 0 (mod 3) or odd number rings and move 1 (mod 3)
        if (((n - 1) & 1 && c % 3 == 0) || (n & 1 && c % 3 == 1)) {
            if (towers[1].empty() || (!towers[0].empty() && towers[1].tp > towers[0].tp)) {
                towers[1].ps(towers[0].tp);
                towers[0].pp;
                cout << 1 << ' ' << 2 << edl;
            } else {
                towers[0].ps(towers[1].tp);
                towers[1].pp;
                cout << 2 << ' ' << 1 << edl;
            }
            // A/C if even number rings and move 1 (mod 3) or odd number rings and move 0 (mod 3)
        } else if (((n - 1) & 1 && c % 3 == 1) || (n & 1 && c % 3 == 0)) {
            if (towers[2].empty() || (!towers[0].empty() && towers[2].tp > towers[0].tp)) {
                towers[2].ps(towers[0].tp);
                towers[0].pp;
                cout << 1 << ' ' << 3 << edl;
            } else {
                towers[0].ps(towers[2].tp);
                towers[2].pp;
                cout << 3 << ' ' << 1 << edl;
            }
            // The last move (mod 3) is always going to be B/C
        } else if (c % 3 == 2) {
            if (towers[2].empty() || (!towers[1].empty() && towers[2].tp > towers[1].tp)) {
                towers[2].ps(towers[1].tp);
                towers[1].pp;
                cout << 2 << ' ' << 3 << edl;
            } else {
                towers[1].ps(towers[2].tp);
                towers[2].pp;
                cout << 3 << ' ' << 2 << edl;
            }
        }
        c++;
    }
    return 0;
}