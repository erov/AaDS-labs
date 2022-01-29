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

void dfs(vector<vector<pair<int, int>>> &g, vector<pair<ll, ll>> &cnt, int v, int p) {
	for (auto it : g[v]) {
		int to = it.f;
		if (to != p) {
			dfs(g, cnt, to, v);
			cnt[v] = {cnt[v].f + cnt[to].f, cnt[v].s + cnt[to].s + cnt[to].f};
		}
	}
	cnt[v].f++;
}

void calc(vector<vector<pair<int, int>>> &g, vector<pair<ll, ll>> &cnt,
	vector<ll> &ans, pair<ll, ll> up, int v, int p) {
	for (auto it : g[v]) {
		int to = it.f;
		if (to != p) {
			up.f += cnt[to].f;
			up.s += cnt[to].s + cnt[to].f;
		}
	}
	up.f++;

	// cout << v << ' ' << up.f << ' ' << up.s << '\n';

	for (auto it : g[v]) {
		int to = it.f, id = it.s;
		if (to != p) {
			pair<ll, ll> tmp = up;
			tmp.f -= cnt[to].f;
			tmp.s -= (cnt[to].f + cnt[to].s);
			ans[id] = tmp.f * cnt[to].s + tmp.s * cnt[to].f + tmp.f * cnt[to].f;
			tmp.s += tmp.f;
			calc(g, cnt, ans, tmp, to, v);
		}
	}
}

void solve() {
	int n;
	cin >> n;

	vector<vector<pair<int, int>>> g(n);  // to - edge id
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].push_back({v, i});
		g[v].push_back({u, i});
	}

	vector<pair<ll, ll>> cnt(n, {0, 0});  // vert cnt - edge len
	vector<ll> ans(n - 1, 0);

	dfs(g, cnt, 0, -1);
	calc(g, cnt, ans, {0, 0}, 0, -1);

	// for (auto it : cnt) {
	// 	cout << it.f << ' ' << it.s << '\n';
	// }

	for (int i = 0; i < n - 1; i++) {
		cout << ans[i] << '\n';
	}
}
