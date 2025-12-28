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
typedef signed char schar;
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

bool is_valid(const vector<string> &grid, const int row, const int col) {
    if (row < 0 || col < 0 || row >= grid.size() || col >= grid[0].length()) return false;
    return grid[row][col] != '#';
}

void monsterBFS(const vector<string> &grid, vector<vector<uint> > &dist, qu<pi> &q, const array<pi, 4> &moves) {
    while (!q.empty()) {
        const auto r = q.fr.fs, c = q.fr.sc;
        q.pp;
        fora(i, 0, 4) {
            const auto x = r + moves[i].fs, y = c + moves[i].sc;
            if (!is_valid(grid, x, y)) continue;
            if (dist[x][y] <= dist[r][c] + 1) continue;
            dist[x][y] = dist[r][c] + 1;
            q.emplace(x, y);
        }
    }
}

void userBFS(const vector<string> &grid, const vector<vector<uint> > &monster_dist, vector<vector<uint> > &dist,
             vector<vector<schar> > &trace, qu<pi> &q, const array<pi, 4> &moves) {
    while (!q.empty()) {
        const auto r = q.fr.fs, c = q.fr.sc;
        q.pp;
        fora(i, 0, 4) {
            const auto x = r + moves[i].fs, y = c + moves[i].sc;
            if (!is_valid(grid, x, y)) continue;
            if (monster_dist[x][y] <= dist[r][c] + 1) continue;
            if (dist[x][y] <= dist[r][c] + 1) continue;
            dist[x][y] = dist[r][c] + 1;
            trace[x][y] = static_cast<schar>(i);
            q.emplace(x, y);
        }
    }
}

string tracePath(const int start_row, const int start_col, const vector<vector<schar> > &trace, const
                 unordered_map<schar, char> &trace_map, const array<pi, 4> &moves) {
    string path;
    int r = start_row, c = start_col;
    while (trace[r][c] <= 3) {
        const auto trc = trace[r][c];
        const auto turn = trace_map.at(trc);
        path.pb(turn);
        // moves array is organized such that (i + 2) % 4 gives the reverse direction of the initial move
        const int move_idx = (static_cast<int>(trc) + 2) % 4;
        r += moves[move_idx].fs, c += moves[move_idx].sc;
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    /**
     * Note that in the problem statement, the monsters act as if they already know what path we can take. This means
     * that we must be able to beat any monster to any valid grid point. From this we can infer that we must conduct
     * some BFS, since we can beat any monster to a grid point if the user's shortest path to that point is <
     * monster's shortest path to the grid point. First find monster's shortest path to all grid points using
     * multi-source BFS (i.e. set all monster start locations to 0, add the points to the queue, and do BFS like
     * normal). Then do user BFS comparing against distances from the monster at each candidate position. If the
     * distance to reach the candidate position from the user start point < distance to reach candidate positions for
     * the monsters, then the user can step to that position.
     *
     * Record for each stepped position the move used to get to that position to trace backwards later. Start the
     * trace from the end point and follow back using the reverse move until the initial user starting position is
     * found. The efficient way to track the path is by pushing to the back of a string, which would generate the
     * path in reverse. Reverse it again to get the path from the starting point.
     *
     * To find the end point, linear search the first and last rows and columns of the user distance. If any distance is
     * not invalid (i.e. not infinity), then there is a path from the starting point to that cell. Record the value
     * and position of the shortest such path, and use that position for the trace.
     */
    fio;
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    vector<vector<uint> > monster_dist(n, vector<uint>(m, UINT_MAX)), user_dist(n, vector<uint>(m, UINT_MAX));
    vector<vector<schar> > trace(n, vector<schar>(m, -1)); // -1: invalid 4: source 0: U 1: R 2: D 3: L
    static constexpr array<pi, 4> moves = {pi{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    static const unordered_map<schar, char> trace_map{{0, 'U'}, {1, 'R'}, {2, 'D'}, {3, 'L'}};
    qu<pi> monster_queue, user_queue;
    fora(i, 0, n) {
        cin >> grid[i];
        fora(j, 0, m) {
            if (grid[i][j] == 'M') {
                monster_queue.emplace(i, j);
                monster_dist[i][j] = 0;
            } else if (grid[i][j] == 'A') {
                user_queue.emplace(i, j);
                user_dist[i][j] = 0;
                trace[i][j] = 4;
            }
        }
    }
    monsterBFS(grid, monster_dist, monster_queue, moves);
    userBFS(grid, monster_dist, user_dist, trace, user_queue, moves);
    uint min_sol = UINT_MAX;
    int mr = -1, mc = -1;
    fora(i, 0, m) {
        if (user_dist[0][i] < min_sol) {
            min_sol = user_dist[0][i];
            mr = 0, mc = i;
        }
        if (user_dist[n - 1][i] < min_sol) {
            min_sol = user_dist[n - 1][i];
            mr = n - 1, mc = i;
        }
    }
    fora(i, 0, n) {
        if (user_dist[i][0] < min_sol) {
            min_sol = user_dist[i][0];
            mr = i, mc = 0;
        }
        if (user_dist[i][m - 1] < min_sol) {
            min_sol = user_dist[i][m - 1];
            mr = i, mc = m - 1;
        }
    }
    if (min_sol == UINT_MAX) {
        cout << "NO" << edl;
        return 0;
    }
    cout << "YES" << edl << min_sol << edl;
    cout << tracePath(mr, mc, trace, trace_map, moves) << edl;
    return 0;
}
