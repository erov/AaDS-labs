#include <iostream>
#include <vector>

using namespace std;

vector<int> res;
void merge(vector<int> &a, int l, int r, int m) {
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

void merge_sort(vector<int> &a, int l, int r) {
	if (r - l != 1) {
		int m = (l + r) >> 1;
		merge_sort(a, l, m);
		merge_sort(a, m, r);
		merge(a, l, r, m);
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

	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	res.resize(n);
	merge_sort(a, 0, n);
	for (int i = 0; i < n; i++) {
		cout << a[i] << ' ';
	}
}
