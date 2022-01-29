// #pragma GCC optimize("Ofast")
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <random>
#include <deque>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <bitset>
#include <stack>
#include <climits>

// continue push_back setprecision __builtin_popcount

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

mt19937 rnd(228);

const double EPS = 1e-7;
const double PI = acos(-1);
const ll oo = LLONG_MAX;

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define mp(a, b) make_pair(a, b)
#define size(a) (int)a.size()
#define f first
#define s second

void solve();

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		// freopen("censored.in", "r", stdin);
		// freopen("censored.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(false);
	#ifdef HOME
		clock_t start = clock();
	#endif

	solve();

	#ifdef HOME
		cout <<  "\n\n\nTIME: " << float(clock() - start) / CLOCKS_PER_SEC << endl;
		// system("pause");
	#endif

	exit(0);
}

void solve() {
	int n, m;
	cin >> n >> m;

	vector<vector<pair<int, ll>>> g(n);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}

	vector<vector<ll>> dp((1 << n), vector<ll> (n, oo));
	for (int i = 0; i < n; i++) {
		dp[1 << i][i] = 0;
	}

	for (int mask = 1; mask < (1 << n); mask++) {
		for (int last = 0; last < n; last++) {
			if ((mask & (1 << last)) && dp[mask][last] != oo) {
				for (auto nxt : g[last]) {
					int to = nxt.f;
					ll w = nxt.s;
					if ((mask & (1 << to)) == 0) {
						dp[mask | (1 << to)][to] = min(dp[mask | (1 << to)][to], dp[mask][last] + w);
					}
				}
			}
		}
	}

	// for (int mask = 0; mask < (1 << n); mask++) {
	// 	cout << mask << ": ";
	// 	for (int i = 0; i < n; i++) {
	// 		cout << dp[mask][i] << ' ';
	// 	}
	// 	cout << '\n';
	// }

	ll ans = oo;
	for (int i = 0; i < n; i++) {
		ans = min(ans, dp[(1 << n) - 1][i]);
	}

	cout << (ans == oo ? -1 : ans);
}
