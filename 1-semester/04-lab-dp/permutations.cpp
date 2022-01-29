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
const int oo = INT_MAX;

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

ll calculate(vector<int> &a, vector<vector<int>> &g, vector<bool> &banned, int start) {
	int n = size(a);
	vector<vector<ll>> dp((1 << n), vector<ll> (n, 0));
	dp[(1 << start)][start] = 1;

	for (int mask = 0; mask < (1 << n); mask++) {
		for (int last = 0; last < n; last++) {
			if (banned[last] || dp[mask][last] == 0) {
				continue;
			}
			for (int nxt : g[last]) {
				if (banned[nxt] || (mask & (1 << nxt))) {
					continue;
				}
				dp[mask | (1 << nxt)][nxt] += dp[mask][last];
			}
		}
	}

	int full = 0;
	for (int i = 0; i < n; i++) {
		full += (banned[i] ? 0 : (1 << i));
	}

	ll res = 0;
	for (int i = 0; i < n; i++) {
		res += dp[full][i];
	}

	// for (int mask = 0; mask < (1 << n); mask++) {
	// 	cout << mask << ": ";
	// 	for (int last = 0; last < n; last++) {
	// 		cout << dp[mask][last] << ' ';
	// 	}
	// 	cout << '\n';
	// }
	// cout << '\n';

	return res;
}

void solve() {
	int n, k;
	ll m;
	cin >> n >> m >> k;

	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(all(a));

	vector<vector<int>> g(n);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (__gcd(a[i], a[j]) >= k) {
				g[i].push_back(j);
				g[j].push_back(i);
			}
		}
	}

	// for (int i = 0; i < n; i++) {
	// 	cout << a[i] << ": ";
	// 	for (int j : g[i]) {
	// 		cout << a[j] << ' ';
	// 	}
	// 	cout << '\n';
	// }
	// cout << '\n';

	vector<bool> banned(n, false);
	vector<int> ans(n, -1);
	for (int i = 0; i < n; i++) {
		for (int cur = 0; cur < n; cur++) {
			if (banned[cur] || (i && __gcd(ans[i - 1], a[cur]) < k)) {
				continue;
			}
			ll cnt = calculate(a, g, banned, cur);
			// cout << i << ' ' << a[cur] << ' ' << cnt << ' ' << m << '\n';
			if (cnt >= m) {
				ans[i] = a[cur];
				banned[cur] = true;
				break;
			} else {
				m -= cnt;
			}
		}
		if (ans[i] == -1) {
			cout << -1;
			return;
		}
	}

	// for (auto i : ans) {
	// 	cout << i << ' ';
	// }
	// cout << '\n';

	// cout << m << '\n';

	for (auto i : ans) {
		cout << i << ' ';
	}
}
