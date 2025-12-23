#include <bits/stdc++.h>

using namespace std;

#define fs first
#define fio ios::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL)
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
#define fora(i, a, b, c) for (int (i) = (a); (i) < (b); (i) += (c))
#define forae(i, a, b, c) for (int (i) = (a); (i) <= (b); (i) += (c))
#define ford(i, a, b, c) for (int (i) = (a); (i) > (b); (i) -= (c))
#define forde(i, a, b, c) for (int (i) = (a); (i) >= (b); (i) -= (c))
#define dblinf numeric_limits<double>::infinity()

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, ll> pil;
typedef pair<ll, ll> pl;
typedef pair<ull, ull> pull;
typedef pair<int, pi> pii;
typedef pair<ll, pl> pll;
typedef pair<pi, pi> ppi;
typedef pair<double, double> pd;
typedef pair<char, int> pci;

int main() {
    fio;
    ll n, s = 0, a;
    cin >> n;
    fora (i, 0, n - 1, 1) {
        cin >> a;
        s += a;
    }
    cout << ((n) * (n + 1LL) / 2LL) - s;
    return 0;
}