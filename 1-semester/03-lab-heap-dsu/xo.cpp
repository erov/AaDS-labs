#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;
typedef long long ll;

struct element {
	int p, r, total_messages, read;

	element() {}
	element(int _p) {
		p = _p;
		r = total_messages = read = 0;
	}
};

pair<int, int> get(vector<element> &a, int v) {
	if (v == a[v].p) {
		return {v, a[v].total_messages};
	}
	pair<int, int> parent = get(a, a[v].p);
	parent.second += a[v].total_messages;
	return parent;
}

void unite(vector<element> &a, int l, int r) {
	l = get(a, l).first;
	r = get(a, r).first;
	if (l != r) {
		if (a[l].r > a[r].r) {
			swap(l, r);
		}
		a[l].p = r;
		a[l].total_messages -= a[r].total_messages;
		if (a[l].r == a[r].r) {
			a[r].r++;
		}
	}
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	int n, m;
	cin >> n >> m;

	vector<element> a(n);
	for (int i = 0; i < n; i++) {
		a[i] = element(i);
	}

	vector<int> read(n, 0);
	int zerg = 0;
	const int p = (int) 1e6 + 3;

	for (int i = 0; i < m; i++) {
		int type;
		cin >> type;

		if (type == 1) {
			int x;
			cin >> x;
			x = (x + zerg) % n;
			x = get(a, x).first;
			a[x].total_messages++;
			zerg = (30 * zerg + 239) % p;
		}

		if (type == 2) {
			int x, y;
			cin >> x >> y;
			x = (x + zerg) % n;
			y = (y + zerg) % n;
			x = get(a, x).first;
			y = get(a, y).first;
			if (x != y) {
				unite(a, x, y);
				zerg = (13 * zerg + 11) % p;
			}
		}

		if (type == 3) {
			int x;
			cin >> x;
			x = (x + zerg) % n;
			int new_mes = get(a, x).second - read[x];
			cout << new_mes << '\n';
			read[x] += new_mes;
			zerg = (int) ((100500LL * zerg + new_mes) % (ll) p);
		}
	}
}
