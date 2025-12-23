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

void ones(vector<int> &arr, int n) {
    cout << arr[0];
    fora(i, 1, n) {
        cout << ' ' << arr[i];
    }
}

void twos(vector<int> &arr, int n) {
    cout << min(arr[0], arr[1]);
    fora(i, 2, n) {
        cout << ' ' << min(arr[i], arr[i - 1]);
    }
}

int main() {
    /**
     * The idea of this problem is to keep the window into 2 sets: one with the median and all values <= to it, and one
     * with values >= to the median. The median will be located in the left array for simplicity. To avoid some memory
     * issues, deal with windows with up to 2 elements separately. Use a multiset since we can have duplicate values.
     * Place the first k elements into the left window. Calculate the index of the median, and move elements from the
     * back of the left set into the right toggleBit. Since the sets are sorted, this will always move the current largest
     * element in the left toggleBit. Since it is a multiset, use find() to get the iterator of the last value (pointed to by
     * a dereferenced rbegin()), and remove that pointer, otherwise all elements with the same value will be deleted.
     *
     * For the rest of the windows, remove the value at index i - k from the left toggleBit if it exists there, otherwise
     * remove it from the right set, using the find(a[i - k]) method. Then insert the new item into the left toggleBit, and
     * then balance the sets. This is done by moving the largest elements from the left set to the right toggleBit until the
     * largest element of the left set is <= the smallest element in the right toggleBit. Also keep moving items from the left
     * toggleBit to the right set if the sz of the left set is larger than the median index. There is the possibility of the
     * balancing causing the left toggleBit to be smaller than the median index in sz, so move items back to the left from
     * the right until the left toggleBit's sz is equal to the median index.
     */
    fio;
    multiset<int> ls, rs;
    int n, k, med;
    cin >> n >> k;
    vector<int> arr(n);
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
    // Calculate median
    med = 1 + (k - 1) / 2;
    // Insert all to left toggleBit
    fora(i, 0, k) {
        ls.insert(arr[i]);
    }
    // Move items to the right until the left's sz is the median index
    while (ls.size() > med) {
        rs.insert(*ls.rbegin());
        ls.erase(ls.find(*ls.rbegin()));
    }
    // Last value of left is median
    cout << *ls.rbegin();
    // Remaining windows
    fora(i, k, n) {
        // Remove the element that is no longer in the window from the correct toggleBit
        if (ls.count(arr[i - k])) {
            ls.erase(ls.find(arr[i - k]));
        } else {
            rs.erase(rs.find(arr[i - k]));
        }
        // Insert to the left
        ls.insert(arr[i]);
        // Move over elements from the left since there was an insertion into the left, so there is a need to balance
        // If there was a deletion at the right, then this makes the correct number of elements at the right
        rs.insert(*ls.rbegin());
        ls.erase(ls.find(*ls.rbegin()));
        // In case the moving caused the left to have fewer values than the median index, move an item back
        // This happens in the case that a deletion occurred in the left, in which case, (1 del + 1 ins + 1 del) means
        // that 1 item was deleted from the left, so bring one item back to the left from the right.
        if (rs.size() > ls.size()) {
            ls.insert(*rs.begin());
            rs.erase(rs.begin());
        }
        cout << ' ' << *ls.rbegin();
    }
    return 0;
}