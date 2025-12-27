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

bool comp(const pi &a, const pi &b) {
    return a.fs > b.fs;
}

int process_batch(const vector<pi> &batch, vector<int> &dp, set<int> &seen_idxs) {
    int mx = 0;
    foraz(j, 0, batch.size()) {
        // left
        const int idx = batch[j].sc;
        auto it = seen_idxs.lower_bound(idx);
        int left_idx = -1, right_idx = -1;
        if (it != seen_idxs.begin()) {
            --it;
            left_idx = *it;
        }
        it = seen_idxs.upper_bound(idx);
        if (it != seen_idxs.end()) {
            right_idx = *it;
        }
        int l = left_idx == -1 ? 0 : dp[left_idx];
        int r = right_idx == -1 ? 0 : dp[right_idx];
        dp[idx] = 1 + max(l, r);
        mx = max(mx, dp[idx]);
    }
    return mx;
}

int main() {
    /**
     * Process the mountains in order of decreasing height. At each mountain, find the next mountain immediately
     * larger to it on the left and right, and the answer is 1 + max(dp[L], dp[R]). Since we are processing the
     * mountains in order of decreasing height, then the mountain immediately larger on the left from the mountains
     * processed is the largest index < the current index, and the one to the right is the smallest index > the
     * current index. The index can be tracked in a set.
     *
     * To maintain the property that the indices to the left and right contain mountains who are taller than the
     * current mountain, we must add all tied mountain heights to this seen set *only after* all the mountains at
     * that height have been processed. Add all equal height mountains into a list (batch), process all mountains in
     * the batch, then add the indexes seen to the set after the batch has been processed. Clear the batch afterwards.
     */
    fio;
    size_t n;
    cin >> n;
    vector<pi> mtn_idx(n), batch;
    vector<int> dp(n, 0);
    int mx = 0;
    set<int> seen_idxs;
    foraz(i, 0, n) {
        cin >> mtn_idx[i].fs;
        mtn_idx[i].sc = static_cast<int>(i);
    }
    sort(mtn_idx.begin(), mtn_idx.end(), comp);
    batch.pb(mtn_idx[0]);
    foraz(i, 1, n) {
        // Same height
        if (mtn_idx[i].fs == mtn_idx[i - 1].fs) {
            batch.pb(mtn_idx[i]);
            continue;
        }
        // Diff height, process batch and add current
        mx = max(mx, process_batch(batch, dp, seen_idxs));
        while (!batch.empty()) {
            seen_idxs.insert(batch.bk.sc);
            batch.ppb;
        }
        batch.pb(mtn_idx[i]);
    }
    mx = max(mx, process_batch(batch, dp, seen_idxs));
    cout << mx << edl;
    return 0;
}
