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

void solve() {
	int n, k;
	cin >> n >> k;

	vector<int> a(n), b(n), c(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i] >> b[i] >> c[i];
	}

	vector<vector<int>> dp((1 << n), vector<int> (n + 1, -oo));
	for (int i = 0; i < n; i++) {
		if (a[i] <= k && k <= b[i]) {
			dp[1 << i][i] = k + c[i];
		}
	}

	for (int mask = 0; mask < (1 << n); mask++) {
		for (int last = 0; last < n; last++) {
			if (dp[mask][last] != -oo) {
				for (int i = 0; i < n; i++) {
					if (((mask >> i) & 1) == 0 && a[i] <= dp[mask][last] && dp[mask][last] <= b[i]) {
						dp[mask | (1 << i)][i] = max(dp[mask | (1 << i)][i], dp[mask][last] + c[i]);
					}
				}
			}
		}
	}

	pair<int, int> best = mp(0, 0);

	for (int mask = 0; mask < (1 << n); mask++) {
		for (int i = 0; i < n; i++) {
			if (dp[mask][i] != -oo && __builtin_popcount(mask) > __builtin_popcount(best.f)) {
				best = {mask, i};
			}
			// cout << dp[mask][i] << ' ';
		}
		// cout << '\n';
	}

	vector<int> ans;
	while (best.f != 0) {
		ans.push_back(best.s);
		int prev = dp[best.f][best.s] - c[best.s];
		best.f ^= (1 << best.s);
		for (best.s = 0; best.s < n; best.s++) {
			if (dp[best.f][best.s] == prev) {
				break;
			}
		}
	}

	cout << size(ans) << '\n';
	reverse(all(ans));
	for (int i : ans) {
		cout << ++i << ' ';
	}
}
