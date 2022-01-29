#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

struct element {
	int p, r;
	bool swapped;

	element() {}
	element(int _p) {
		p = _p;
		r = 0;
		swapped = false;
	}
};

pair<int, int> get(vector<element> &a, int v) {
	if (v == a[v].p) {
		return {v, a[v].swapped};
	}
	pair<int, int> parent = get(a, a[v].p);
	parent.second ^= a[v].swapped;
	return parent;
}

void unite(vector<element> &a, int l, int r) {
	pair<int, int> pl = get(a, l);
	pair<int, int> pr = get(a, r);
	if (pl.first != pr.first) {
		if (a[pl.first].r > a[pr.first].r) {
			swap(pl, pr);
		}
		a[pl.first].p = pr.first;
		if (a[pl.first].r == a[pr.first].r) {
			a[pr.first].r++;
		}
		if (pl.second == pr.second) {
			a[pl.first].swapped ^= 1;
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

	int shift = 0;
	for (int i = 0; i < m; i++) {
		int t, l, r;
		cin >> t >> l >> r;
		l--, r--;
		l = (l + shift) % n;
		r = (r + shift) % n;

		if (t == 0) {
			unite(a, l, r);
		} else {
			pair<int, int> pl = get(a, l);
			pair<int, int> pr = get(a, r);
			int res = (pl.second == pr.second);
			cout << (res ? "YES\n" : "NO\n");
			shift = (shift + res) % n;
		}
	}
}
