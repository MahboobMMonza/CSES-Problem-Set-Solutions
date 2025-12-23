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

void ones(vector<ll> &arr, int n) {
    cout << 0;
    fora(i, 1, n) {
        cout << ' ' << 0;
    }
}

void twos(vector<ll> &arr, int n) {
    cout << max(arr[0], arr[1]) - min(arr[0], arr[1]);
    fora(i, 2, n) {
        cout << ' ' << max(arr[i], arr[i - 1]) - min(arr[i], arr[i - 1]);
    }
}

int main() {
    /**
     * Same base idea as sliding window median, with the idea from the stick lengths problem to minimize the cost of
     * the subarray by making all items equal to the median. Keep track of the median for each window, as well as the
     * sum of the left and right sets. The cost of the left toggleBit is median_index * median_value - left_sum. The cost of
     * the right toggleBit is right_sum - (k - median_index) * median_value. Add the costs together to get the window cost.
     */
    fio;
    multiset<ll> left, right;
    int n, k, med;
    ll ls = 0, rs = 0, cost;
    cin >> n >> k;
    vector<ll> arr(n);
    fora(i, 0, n) {
        cin >> arr[i];
    }
    if (k == 1) {
        ones(arr, n);
        return 0;
    } else if (k == 2) {
        twos(arr, n);
        return 0;
    }
    med = 1 + (k - 1) / 2;
    fora(i, 0, k) {
        left.insert(arr[i]);
        ls += arr[i];
    }
    while (left.size() > med) {
        right.insert(*left.rbegin());
        ls -= *left.rbegin();
        rs += *left.rbegin();
        left.erase(left.find(*left.rbegin()));
    }
    cost = ((*left.rbegin() * med) - ls) + (rs - (*left.rbegin() * (k - med)));
    cout << cost;
    fora(i, k, n) {
        if (left.count(arr[i - k])) {
            ls -= arr[i - k];
            left.erase(left.find(arr[i - k]));
        } else {
            rs -= arr[i - k];
            right.erase(right.find(arr[i - k]));
        }
        left.insert(arr[i]);
        ls += arr[i];
        ls -= *left.rbegin();
        rs += *left.rbegin();
        right.insert(*left.rbegin());
        left.erase(left.find(*left.rbegin()));
        if (right.size() > left.size()) {
            ls += *right.begin();
            rs -= *right.begin();
            left.insert(*right.begin());
            right.erase(right.begin());
        }
        cost = ((*left.rbegin() * med) - ls) + (rs - (*left.rbegin() * (k - med)));
        cout << ' ' << cost;
    }
    return 0;
}