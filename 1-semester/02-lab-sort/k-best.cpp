#include <iostream>

using namespace std;

const int MAXN = (int) 1e5;
pair<double, int> *a = new pair<double, int>[MAXN];
pair<double, int> *res = new pair<double, int>[MAXN];
void merge(int l, int r, int m) {
	int i = l, j = m, k = 0;
	while (i < m || j < r) {
		if (j == r || (i != m && a[i] < a[j])) {
			res[k++] = a[i++];
		} else {
			res[k++] = a[j++];
		}
	}
	k = 0;
	while (l < r) {
		a[l++] = res[k++];
	}
}

void merge_sort(int l, int r) {
	if (r - l != 1) {
		int m = (l + r) >> 1;
		merge_sort(l, m);
		merge_sort(m, r);
		merge(l, r, m);
	}
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);

	int n, k;
	cin >> n >> k;

	int *v = new int[n];
	int *w = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> v[i] >> w[i];
	}

	double l = 0, r = 1e9;
	for (int p = 0; p < 100; p++) {
		double m = (l + r) / 2;
		for (int i = 0; i < n; i++) {
			a[i] = {v[i] - w[i] * m, i};
		}
		merge_sort(0, n);
		double check = 0;
		for (int i = n - 1; i > n - 1 - k; i--) {
			check += a[i].first;
		}

		if (check > 0) {
			l = m;
		} else {
			r = m;
		}
	}

	for (int i = 0; i < n; i++) {
		a[i] = {v[i] - w[i] * l, i};
	}
	merge_sort(0, n);
	for (int i = n - 1; i > n - 1 - k; i--) {
		cout << ++a[i].second << ' ';
	}
}
