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
using ll = long long;

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

int const MOD = 1e6;
int const P = 13;

int get_hash(string &str, int poly = P, int mod = MOD) {
	int result = 0;
	for (char c : str) {
		result = result * poly + c - '0' + 1;
		result %= mod;
	}
	return result;
}

vector<pair<string, int>> store[MOD];

int find_item(string &str) {
	for (auto it : store[get_hash(str)]) {
		if (it.f == str) {
			return it.s;
		}
	}
	return -1;
}

void add_item(string &str, int value) {
	int hash = get_hash(str, P, MOD);
	if (find_item(str) == -1) {
		store[hash].push_back({str, value});
	}
}

void bfs(vector<vector<int>> &g, vector<int> &dist, int start) {
	queue<int> q;
	dist.assign(size(g), -1);

	dist[start] = 0;
	q.push(start);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int u : g[v]) {
			if (dist[u] == -1) {
				dist[u] = dist[v] + 1;
				q.push(u);
			}
		}
	}
}

int get_center(vector<vector<int>> &g) {
	vector<int> dist[2];
	dist[0].resize(size(g));
	dist[1].resize(size(g));

	bfs(g, dist[0], 0);
	int l = 0;
	for (int i = 0; i < size(g); i++) {
		if (dist[0][i] > dist[0][l]) {
			l = i;
		}
	}

	bfs(g, dist[0], l);
	int r = l;
	for (int i = 0; i < size(g); i++) {
		if (dist[0][i] > dist[0][r]) {
			r = i;
		}
	}

	bfs(g, dist[1], r);

	int diameter = dist[1][l];
	if (diameter % 2) {
		return -1;
	}

	for (int i = 0; i < size(g); i++) {
		if (dist[0][i] == diameter / 2 && dist[1][i] == diameter / 2) {
			return i;
		}
	}
	return -1;
}

string to_str(vector<int> &list) {
	sort(rall(list));
	string result;
	for (int it : list) {
		result += to_string(it) + ":";
	}
	return result;
}

int last_used = -1;

vector<int> check(vector<vector<int>> &g, int v, int p) {
	vector<int> current;
	for (int u : g[v]) {
		if (u != p) {
			vector<int> son = check(g, u, v);
			string str = to_str(son);
			int value = find_item(str);
			if (value == -1) {
				add_item(str, (value = ++last_used));
			}
			current.push_back(value);
		}
	}
	return current;
}

void solve() {
	int n;
	cin >> n;

	vector<vector<int>> g(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	if (n % 2 == 0 || n == 1) {
		cout << "NO";
		return;
	}

	int center = get_center(g);

	if (center == -1) {
		cout << "NO";
		return;
	}

	vector<int> ans = check(g, center, -1);
	sort(all(ans));

	int cnt = 1;
	bool ok = true;
	for (int i = 1; i <= size(ans); i++) {
		if (i != size(ans) && ans[i - 1] == ans[i]) {
			cnt++;
		} else {
			if (cnt % 2) {
				ok = false;
			}
			cnt = 1;
		}
	}

	cout << (ok ? "YES" : "NO");
}
