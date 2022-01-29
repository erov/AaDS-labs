#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

vector<ll> arr, orig;
vector<pair<ll, int>> res;
ll ans = 0, k;
void merge(vector<pair<ll, int>> &a, int l, int r, int m) {
	int i = l, j = m, pos;
	for (pos = l; pos < m; pos++) {
		ll val = (a[pos].second ? orig[a[pos].second - 1] : 0);
		val += k;
		int left = m - 1, right = r;
		while (right - left > 1) {
			int mid = (left + right) >> 1;
			if (a[mid].first >= val) {
				right = mid;
			} else {
				left = mid;
			}
		}
		if (right < r && a[right].first >= val) {
			ans += r - right;
		}
	}

	pos = 0;
	while (i < m || j < r) {
		if (j == r || (i != m && a[i] < a[j])) {
			res[pos++] = a[i++];
		} else {
			res[pos++] = a[j++];
		}
	}
	pos = 0;
	while (l < r) {
		a[l++] = res[pos++];
	}
}

void merge_sort(vector<pair<ll, int>> &a, int l, int r) {
	if (r - l != 1) {
		int m = (l + r) >> 1;
		merge_sort(a, l, m);
		merge_sort(a, m, r);
		merge(a, l, r, m);
	} else {
		ans += ((ll) arr[a[l].second] >= k);
	}
}

unsigned int cur = 0;
unsigned int nextRand24(int a, int b) {
	cur = cur * a + b;
	return cur >> 8;
}

unsigned int nextRand32(int a, int b) {
	unsigned int A = nextRand24(a, b), B = nextRand24(a, b);
	return (A << 8) ^ B;
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);

	int n, a, b;
	cin >> n >> k >> a >> b;

	vector<pair<ll, int>> pref(n);
	arr.resize(n);
	orig.resize(n);

	for (int i = 0; i < n; i++) {
		arr[i] = (int) nextRand32(a, b);
		pref[i] = {(i ? pref[i - 1].first : 0LL) + arr[i], i};
		orig[i] = pref[i].first;
	}

	res.resize(n);
	merge_sort(pref, 0, n);

	cout << ans;
}
