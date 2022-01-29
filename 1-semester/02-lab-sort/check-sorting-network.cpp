#include <iostream>

using namespace std;

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);

	int n, m, k;
	cin >> n >> m >> k;

	pair<int, int> *comp = new pair<int, int>[m];
	int j = 0;
	for (int i = 0; i < k; i++) {
		int r;
		cin >> r;
		while (r--) {
			int x, y;
			cin >> x >> y;
			if (x > y) {
				swap(x, y);
			}
			comp[j++] = {x - 1, y - 1};
		}
	}

	bool sorted = 1;
	bool *a = new bool[n];
	for (int mask = 0; mask < (1 << n); mask++) {
		for (int i = 0; i < n; i++) {
			a[i] = (((mask >> i) & 1) != 0 ? 1 : 0);
		}
		for (int i = 0; i < m; i++) {
			int l = comp[i].first, r = comp[i].second;
			if (a[l] > a[r]) {
				swap(a[l], a[r]);
			}
		}

		for (int i = 1; i < n; i++) {
			sorted &= (a[i - 1] <= a[i]);
		}
	}

	cout << (sorted ? "Yes" : "No");
}
