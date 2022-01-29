#include <iostream>
#include <vector>

using namespace std;

struct element {
	int p, free;
	element() {}
	element(int id) {
		p = id;
		free = id;
	}
};

int get(vector<element> &a, int v) {
	return (a[v].p == v ? v : a[v].p = get(a, a[v].p));
}

void unite(vector<element> &a, int u, int v) {
	u = get(a, u);
	v = get(a, v);
	if (u != v) {
		a[u].p = v;
		a[u].free = a[v].free;
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

	for (int i = 0; i < n; i++) {
		int p;
		cin >> p;
		p--;
		p = get(a, p);
		cout << a[p].free + 1 << ' ';
		unite(a, p, (p + 1) % n);
	}
}
