#include <iostream>
#include <algorithm>

using namespace std;

int my_rand() {
	return abs((rand() << 15) + rand());
}

int partition(pair<int, int> *a, int l, int r) {
	int i = l, j = l;
	int p = my_rand() % (r - l) + l;
	swap(a[p], a[r - 1]);
	while (j < r - 1) {
		if (a[j] <= a[r - 1]) {
			swap(a[j], a[i++]);
		}
		j++;
	}
	swap(a[i], a[j]);
	return i;
}

int kth_element(pair<int, int> *a, int l, int r, int k) {
	if (l + 1 >= r) {
		return a[l].first;
	}
	int m = partition(a, l, r);

	if (k <= m - l) {
		return kth_element(a, l, m, k);
	}
	if (k == m - l + 1) {
		return a[m].first;
	}
	return kth_element(a, m + 1, r, k - (m - l + 1));
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);

	int n, k;
	cin >> n >> k;

	pair<int, int> *a = new pair<int, int>[n];
	unsigned int A, B, C;
	cin >> A >> B >> C >> a[0].first >> a[1].first;
	a[0].second = 0;
	a[1].second = 1;
	for (int i = 2; i < n; i++) {
		a[i].first = (int) ((unsigned int) A * a[i - 2].first + B * a[i - 1].first + C);
		a[i].second = i;
	}
	random_shuffle(a, a + n);
	cout << kth_element(a, 0, n, k);
}
