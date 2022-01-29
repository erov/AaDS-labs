#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

vector<ll> res;
void merge(vector<ll> &a, int l, int r, int m) {
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

void merge_sort(vector<ll> &a, int l, int r) {
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

	int m;
	cin >> m;

	ll *a = new ll[m];
	ll *b = new ll[m];
	ll *t = new ll[m];
	for (int i = 0; i < m; i++) {
		cin >> a[i] >> b[i] >> t[i];
	}

	ll p;
	int n;
	cin >> n >> p;

	n = min(n, m);
	vector<ll> arr(m);
	res.resize(m);

	ll l = -1, r = (ll) 1e11;
	while (r - l > 1) {
		ll mid = (l + r) >> 1;
		for (int i = 0; i < m; i++) {
			if (mid - t[i] - b[i] >= a[i]) {
				arr[i] = (a[i] ? (mid - t[i] - b[i]) / a[i] : p);
			} else {
				arr[i] = 0;
			}
		}
		merge_sort(arr, 0, m);
		ll can = 0;
		for (int i = m - 1, j = n; i >= 0 && j > 0; i--, j--) {
			can += arr[i];
		}
		if (can >= p) {
			r = mid;
		} else {
			l = mid;
		}
	}

	cout << r;
}
