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
	int n, m;
	cin >> n >> m;

	vector<int> w(n), c(n);
	for (int i = 0; i < n; i++) {
		cin >> w[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> c[i];
	}

	vector<vector<int>> dp(n + 1, vector<int> (m + 1, -oo));

	for (int i = 0; i <= n; i++) {
		dp[i][0] = 0;
	}
	for (int j = 0; j <= m; j++) {
		dp[0][j] = 0;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			dp[i][j] = max(dp[i - 1][j],  (j - w[i - 1] < 0 ? -oo : dp[i - 1][j - w[i - 1]] + c[i - 1]));
		}
	}

	vector<int> ans;
	int i = n, j = m;
	while (i > 0 && j > 0) {
		if (dp[i][j] == (j - w[i - 1] < 0 ? -oo : dp[i - 1][j - w[i - 1]] + c[i - 1])) {
			ans.push_back(i);
			j-= w[i - 1], i--;
		} else {
			i--;
		}
	}

	cout << size(ans) << '\n';
	for (int i = size(ans) - 1; i >= 0; i--) {
		cout << ans[i] << ' ';
	}
}
