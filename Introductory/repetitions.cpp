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
    ll a = 0, b = 0;
    string s;
    cin >> s;
    if (s[0] == s[1]) {
        b = 1;
        a = 1;
    }
    fora (i, 2, s.length(), 1) {
        if (s[i] == s[i - 1]) {
            b++;
            a = max(a, b);
        } else {
            b = 0;
        }
    }
    cout << a + 1;
    return 0;
}
