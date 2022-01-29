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
 
const double PI = acos(-1);
const long long INF = LLONG_MAX;
 
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
 
void dfs(vector<string> &g, size_t i, size_t j) {
	if (g[i][j] == '.') {
		return;
	}
	g[i][j] = '.';
	if (i) {
		dfs(g, i - 1, j);
	}
	if (i + 1 != g.size()) {
		dfs(g, i + 1, j);
	}
	if (j) {
		dfs(g, i, j - 1);
	}
	if (j + 1 != g.back().size()) {
		dfs(g, i, j + 1);
	}
}
 
void solve() {
	size_t n, m;
	cin >> n >> m;
 
	vector<string> g(n);
	for (size_t i = 0; i != n; ++i) {
		cin >> g[i];
	}
 
	size_t ans = 0;
	for (size_t i = 0; i != n; ++i) {
		for (size_t j = 0; j != m; ++j) {
			if (g[i][j] == 'O') {
				++ans;
				dfs(g, i, j);
			}
		}
	}
 
	cout << ans;
}
