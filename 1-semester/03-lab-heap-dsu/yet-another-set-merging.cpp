#include <iostream>
#include <vector>

using namespace std;

int get(vector<int> &p, int v) {
	return (p[v] == v ? v : p[v] = get(p, p[v]));
}

void unite(vector<int> &p, int u, int v) {
	u = get(p, u);
	v = get(p, v);
	if (u != v) {
		p[u] = v;
	}
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);

	int n, q;
	cin >> n >> q;

	vector<int> p(n), id(n);
	for (int i = 0; i < n; i++) {
		p[i] = i;
		id[i] = i;
	}

	while (q--) {
		int t, x, y;
		cin >> t >> x >> y;
		x--, y--;
		if (x > y) {
			swap(x, y);
		}
		if (t == 1) {
			unite(p, x, y);
		}
		if (t == 2) {
			x = get(id, x);
			while (x < min(y, n)) {
				if (x + 1 <= y) {
					unite(id, x, x + 1);
					unite(p, x, x + 1);
				} else {
					break;
				}
				x = get(id, x);
			}
		}
		if (t == 3) {
			cout << (get(p, x) == get(p, y) ? "YES\n" : "NO\n");
		}
	}
}
