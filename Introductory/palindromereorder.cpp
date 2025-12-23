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
    string s;
    cin >> s;
    vector<int> fq(26);
    for (int i = 0; i < s.length(); i++) {
        fq[s[i] - 'A']++;
    }
    int nOdd = 0, oddIdx = -1;
    for (int i = 0; i < 26; i++) {
        if (fq[i]&1) {
            nOdd++;
            oddIdx = i;
        }
        if (nOdd > 1) {
            cout << "NO SOLUTION" << edl;
            return 0;
        }
    }
    for (int i = 0; i < 26; i++) {
        if (i == oddIdx) {
            continue;
        }
        for (int j = 0; j < fq[i] / 2; j++) {
            cout << char ('A' + i);
        }
    }
    for (int i = 0; i < fq[oddIdx] && oddIdx >= 0; i++) {
        cout << char ('A' + oddIdx);
    }
    for (int i = 25; i >= 0; i--) {
        if (i == oddIdx) {
            continue;
        }
        for (int j = 0; j < fq[i] / 2; j++) {
            cout << char ('A' + i);
        }
    }
    cout << edl;
    return 0;
}
