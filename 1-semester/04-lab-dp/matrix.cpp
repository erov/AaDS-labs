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

string recovery(vector<vector<ll>> &dp, vector<pair<int, int>> &a, int l, int r) {
	if (r - l == 1) {
		return "A";
	}

	for (int i = l + 1; i < r; i++) {
		if (dp[l][r] == dp[l][i] + dp[i][r] + a[l].f * a[r - 1].s * a[i].f) {
			return "(" + recovery(dp, a, l, i) + recovery(dp, a, i, r) + ")";
		}
	}
	assert(false);
	return ":(";
}

void solve() {
	int n;
	cin >> n;

	vector<pair<int, int>> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].f >> a[i].s;
	}

	vector<vector<ll>> dp(n, vector<ll> (n + 1, oo));  // [a, b)
	for (int i = 0; i < n; i++) {
		dp[i][i + 1] = 0;
	}

	for (int len = 2; len <= n; len++) {
		for (int l = 0; l + len <= n; l++) {
			int r = l + len;
			for (int i = l + 1; i < r; i++) {
				dp[l][r] = min(dp[l][r], dp[l][i] + dp[i][r] + a[l].f * a[r - 1].s * a[i].f);
			}
		}
	}

	cout << recovery(dp, a, 0, n);

	// cout << "\n\n\n";
	// for (int i = 0; i < n; i++) {
	// 	for (int len = 1; len <= n; len++) {
	// 		if (i + len > n) {
	// 			break;
	// 		}
	// 		cout << i << ' ' << i + len << ": " << dp[i][i + len] << '\n';
	// 	}
	// }
	// cout << dp[0][n];
}
