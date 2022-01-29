#include <iostream>
#include <vector>

using namespace std;

int get(vector<int> &p, int v) {
	return (p[v] == v ? v : p[v] = get(p, p[v]));
}

void unite(vector<int> &p, vector<int> &r, int a, int b) {
	a = get(p, a);
	b = get(p, b);
	if (a != b) {
		if (r[a] < r[b]) {
			swap(a, b);
		}
		p[b] = a;
		if (r[a] == r[b]) {
			r[a]++;
		}
	}
}

struct query {
	int type, a, b;
	query() {}
	query(int _type, int _a, int _b) {
		type = _type, a = _a, b = _b;
	}
};

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);

	int n, m, k;
	cin >> n >> m >> k;

	vector<int> p(n), r(n);
	for (int i = 0; i < n; i++) {
		p[i] = i;
		r[i] = 0;
	}

	for (int i = 0; i < m; i++) {
		int v;
		cin >> v >> v;
	}

	vector<query> q(k);
	for (int i = 0; i < k; i++) {
		string s;
		int a, b;
		cin >> s >> a >> b;
		q[i] = query(s == "ask", --a, --b);
	}

	vector<bool> ans;
	for (int i = k - 1; i >= 0; i--) {
		if (q[i].type == 1) {
			ans.push_back(get(p, q[i].a) == get(p, q[i].b));
		} else {
			unite(p, r, q[i].a, q[i].b);
		}
	}

	for (int i = (int) ans.size() - 1; i >= 0; i--) {
		cout << (ans[i] ? "YES\n" : "NO\n");
	}
}
