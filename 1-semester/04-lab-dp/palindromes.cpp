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
	int n;
	cin >> n;

	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	vector<vector<int>> dp(n, vector<int> (n, 0));
	const int MOD = (int) 1e9;

	for (int i = 0; i < n; i++) {
		dp[i][i] = 1;
	}

	for (int len = 2; len <= n; len++) {
		for (int l = 0; l + len <= n; l++) {
			int r = l + len - 1;
			dp[l][r] = dp[l + 1][r] + dp[l][r - 1];
			dp[l][r] %= MOD;
			dp[l][r] += (a[l] == a[r] ? 1 : MOD - dp[l + 1][r - 1]);
			dp[l][r] %= MOD;
		}
	}

	cout << dp[0][n - 1];
}
