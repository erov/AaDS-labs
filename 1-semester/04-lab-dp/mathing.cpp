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

void dfs(vector<vector<pair<int, ll>>> &g, vector<pair<ll, ll>> &dp, int v, int p) {
	for (auto nxt : g[v]) {
		int to = nxt.f;
		if (to != p) {  // f - v has edge, s - has not
			dfs(g, dp, to, v);
			dp[v].s += max(dp[to].f, dp[to].s);
		}
	}

	for (auto nxt : g[v]) {
		int to = nxt.f;
		ll w = nxt.s;
		if (to != p) {
			dp[v].f = max(dp[v].f, dp[v].s - max(dp[to].f, dp[to].s) + w + dp[to].s);
		}
	}
}

void solve() {
	int n;
	cin >> n;

	vector<vector<pair<int, ll>>> g(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		ll w;
		cin >> u >> v >> w;
		u--, v--;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}

	vector<pair<ll, ll>> dp(n, {0, 0});

	dfs(g, dp, 0, -1);

	cout << max(dp[0].f, dp[0].s);
}
