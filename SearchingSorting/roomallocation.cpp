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

bool cmp(pii a, pii b) {
    // idx, { date, flow }
    if (a.sc.fs == b.sc.fs) {
        return a.sc.sc > b.sc.sc;
    }
    return a.sc.fs < b.sc.fs;
}

int main() {
    fio;
    // Have to do some searching probably for first available room?? Or try a stack of available rooms
    // Will require running through the data twice -- Not an issue
    int n, curRoom = 0, maxRoom = 0, numCustomers = 0;
    cin >> n;
    vector<pii> dateFlows(2 * n);
    vector<int> roomNums(n), roomStack;
    roomStack.reserve(n);
    fora(i, 0, 2 * n, 2) {
        cin >> dateFlows[i].sc.fs;
        dateFlows[i].sc.sc = 1;
        dateFlows[i].fs = i >> 1;
        cin >> dateFlows[i + 1].sc.fs;
        dateFlows[i + 1].sc.sc = -1;
        dateFlows[i + 1].fs = i >> 1;
    }
    sort(dateFlows.begin(), dateFlows.end(), cmp);
    for (int i = 0; i < dateFlows.size(); ++i) {
        curRoom += dateFlows[i].sc.sc;
        maxRoom = max(maxRoom, curRoom);
        if (dateFlows[i].sc.sc > 0) {
            numCustomers++;
        }
        if (numCustomers == n) {
            break;
        }
    }
    for (int i = 1; i <= maxRoom; ++i) {
        roomStack.pb(i);
    }
    for (int i = 0; i < dateFlows.size(); ++i) {
        if (dateFlows[i].sc.sc > 0) {
            roomNums[dateFlows[i].fs] = roomStack.bk;
            roomStack.ppb;
        } else {
            roomStack.pb(roomNums[dateFlows[i].fs]);
        }
    }
    cout << maxRoom << edl;
    for (int i = 0; i < n; ++i) {
        cout << roomNums[i];
        if (i < n - 1) {
            cout << ' ';
        } else {
            cout << edl;
        }
    }
    return 0;
}
