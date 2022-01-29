#include <iostream>
#include <vector>

using namespace std;

struct element {
	int p, r, mn, mx, cnt;
	element() {}
	element(int id) {
		p = id;
		r = 0;
		mn = mx = id + 1;
		cnt = 1;
	}
};

int get(vector<element> &a, int v) {
	return (a[v].p == v ? v : a[v].p = get(a, a[v].p));
}

void unite(vector<element> &a, int u, int v) {
	u = get(a, u);
	v = get(a, v);
	if (u != v) {
		if (a[u].r < a[v].r) {
			swap(u, v);
		}
		a[v].p = u;
		if (a[u].r == a[v].r) {
			a[u].r++;
		}
		a[u].mn = min(a[u].mn, a[v].mn);
		a[u].mx = max(a[u].mx, a[v].mx);
		a[u].cnt += a[v].cnt;
	}
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;

	vector<element> a(n);
	for (int i = 0; i < n; i++) {
		a[i] = element(i);
	}

	string s;
	while (cin >> s) {
		if (s == "get") {
			int v;
			cin >> v;
			v--;
			v = get(a, v);
			cout << a[v].mn << ' ' << a[v].mx << ' ' << a[v].cnt << '\n';
		} else {
			int u, v;
			cin >> u >> v;
			u--, v--;
			unite(a, u, v);
		}
	}
}
