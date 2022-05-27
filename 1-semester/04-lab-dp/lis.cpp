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
const ll oo = INT_MAX;

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

	vector<pair<int, int>> dp(n + 1, {oo, -1});
	vector<int> prev(n + 1, -1);
	dp[0].f = -oo;

	for (int i = 0; i < n; i++) {
		int pos = lower_bound(all(dp), mp(a[i], -1)) - dp.begin();
		dp[pos] = {a[i], i};
		prev[i] = dp[pos - 1].s;
	}

	int j = -1;
	for (int i = n; i > 0; i--) {
		if (dp[i].f != oo) {
			j = dp[i].s;
			cout << i << '\n';
			break;
		}
	}

	vector<int> ans;
	while (j != -1) {
		ans.push_back(a[j]);
		j = prev[j];
	}

	for (int i = size(ans) - 1; i >= 0; i--) {
		cout << ans[i] << ' ';
	}
}
