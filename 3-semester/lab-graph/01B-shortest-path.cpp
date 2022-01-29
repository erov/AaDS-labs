#include <iostream>
#include <climits>
#include <cstddef>
#include <cmath>
#include <vector>
#include <iomanip>
#include <cassert>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

void solve();

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	#ifdef HOME
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
		clock_t start_clock = clock();
	// #else
	// 	freopen(".in", "r", stdin);
	// 	freopen(".out", "w", stdout);
	#endif
	
	solve();

	#ifdef HOME
		printf("\n\nfinished in %.3f sec", static_cast<float>(clock() - start_clock) / CLOCKS_PER_SEC);
	#endif
}

void dfs(vector<vector<pair<size_t, int32_t>>> &g, vector<bool> &used, vector<size_t> &order, size_t v) {
	used[v] = true;
	for (auto [to, w] : g[v]) {
		if (!used[to]) {
			dfs(g, used, order, to);
		}
	}
	order.push_back(v);
}

void solve() {
	size_t n, m, s, t;
	cin >> n >> m >> s >> t;
	--s, --t;

	vector<vector<pair<size_t, int32_t>>> g(n);
	for (size_t i = 0; i != m; ++i) {
		size_t v, u;
		int32_t w;
		cin >> v >> u >> w;
		--v, --u;
		g[v].push_back({u, w});
	}

	vector<bool> used(n, false);
	vector<size_t> order;
	for (size_t v = 0; v != n; ++v) {
		if (!used[v]) {
			dfs(g, used, order, v);
		}
	}

	constexpr int32_t INF = numeric_limits<int32_t>::max();
	vector<int32_t> dp(n, INF);
	dp[t] = 0;
	for (size_t v : order) {
		for (auto [to, w] : g[v]) {
			if (dp[to] != INF) {
				dp[v] = min(dp[v], dp[to] + w);
			}
		}
	}

	if (dp[s] == INF) {
		cout << "Unreachable";
	} else {
		cout << dp[s];
	}
}
