#include <iostream>
#include <vector>

using namespace std;

int left_bs(vector<int> &a, int x) {
	int l = -1, r = (int)a.size() - 1;
	while (r - l > 1) {
		int m = (l + r) >> 1;
		if (x <= a[m]) {
			r = m;
		} else {
			l = m;
		}
	}
	return (a[r] == x ? r + 1 : -1);
}

int right_bs(vector<int> &a, int x) {
	int l = 0, r = (int)a.size();
	while (r - l > 1) {
		int m = (l + r) >> 1;
		if (x < a[m]) {
			r = m;
		} else {
			l = m;
		}
	}
	return (a[l] == x ? l + 1 : -1);
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

	int q;
	cin >> q;
	while (q--) {
		int x;
		cin >> x;
		cout << left_bs(a, x) << ' ' << right_bs(a, x) << '\n';
	}
}
