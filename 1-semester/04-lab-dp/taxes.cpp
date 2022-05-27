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

struct edge {
	int to, a, b, id;
	edge(int _to, int _a, int _b, int _id) {
		to = _to;
		a = _a;
		b = _b;
		id = _id;
	}
};

void dfs(vector<vector<edge>> &g, vector<ll> &cnt, int v, int p) {
	for (auto it : g[v]) {
		int to = it.to;
		if (to != p) {
			dfs(g, cnt, to, v);
			cnt[v] += cnt[to];
		}
	}
	cnt[v]++;
}

void calc(vector<vector<edge>> &g, vector<ll> &cnt, vector<ll> &ans, int v, int p) {
	for (auto it : g[v]) {
		int to = it.to;
		if (to != p) {
			ans[it.id] = cnt[to] * (size(g) - cnt[to]);
			calc(g, cnt, ans, to, v);
		}
	}
}

void solve() {
	int n;
	ll m;
	cin >> n >> m;

	vector<vector<edge>> g(n);
	vector<pair<int, int>> cost(n - 1);
	for (int i = 0; i < n - 1; i++) {
		int u, v, a, b;
		cin >> u >> v >> a >> b;
		u--, v--;
		g[u].push_back(edge(v, a, b, i));
		g[v].push_back(edge(u, a, b, i));
		cost[i] = {a, b};
	}

	vector<ll> cnt(n, 0);
	dfs(g, cnt, 0, -1);

	vector<ll> e(n - 1, 0);
	calc(g, cnt, e, 0, -1);

	if (m & 1) {
		cout << 0;
		return;
	} else {
		m >>= 1;
	}

	for (int i = 0; i < n - 1; i++) {
		m -= e[i] * cost[i].f;
	}

	if (m < 0) {
		cout << 0;
		return;
	}



	const int mod = 1e9 + 7;
	vector<int> dp((int) m + 1, 0);
	dp[0] = 1;

	for (int i = 0; i < n - 1; i++) {
		ll mx = e[i] * (cost[i].s - cost[i].f);
		for (int j = (e[i] <= m ? (int)e[i] : (int)m + 1); j <= (int)m; j++) {
			dp[j] += dp[j - (int)e[i]];
			dp[j] %= mod;
		}

		for (int j = (m >= mx + e[i] ? (int)m : -1); j >= (int)(mx + e[i]); j--) {
			dp[j] -= dp[j - (int)(mx + e[i])];
			dp[j] += mod;
			dp[j] %= mod;
		}
	}

	cout << dp[(int)m];
}
