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
    // Storing data
    int n, m, k, ans = 0, p = 0;
    array<int, (int) (2e5 + 5)> applicants{}, apartments{};
    cin >> n >> m >> k;
    fora(i, 0, n, 1) {
        cin >> applicants[i];
    }
    fora(i, 0, m, 1) {
        cin >> apartments[i];
    }
    /* Idea: Sort all the applicants and apartments and greedily give them out. This is guaranteed to give the best
     * results. To prevent O(n^2) time, note that the size for the current person is always >= to the size of the person
     * before, so if an apartment is too small for index i, and j > i, then the apartment is too small for index j.
     * As such, keep a pointer to the current apartment, and iterate through apartments by incrementing the pointer from
     * the current position. If the difference is too large, check if it is too small or too big for the person. If it
     * is too small, only then increment. Otherwise, flag complete mismatch and go to the next person. If the pointer
     * reaches the end early while it is still looking for bigger apartments, flag this as well and break from the loop.
     * Only increment answer if no flags have been reached, and break when p == m.
     */
    // Flag for cases
    bool f;
    sort(applicants.begin(), applicants.begin() + n);
    sort(apartments.begin(), apartments.begin() + m);
    fora(i, 0, n, 1) {
        if (p == m) break;
        f = 0;
        while (abs(apartments[p] - applicants[i]) > k) {
            if (apartments[p] < applicants[i]) {
                p++;
                if (p == m) {
                    f = 1;
                    break;
                }
            } else if (apartments[p] > k) {
                f = 1;
                break;
            }
        }
        if (f) continue;
        ans++;
        p++;
    }
    cout << ans << edl;
    return 0;
}