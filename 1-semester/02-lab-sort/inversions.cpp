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

void inv(vector<int> &a, long long &ans, int l, int r, int m) {
	long long cnt = 0;
	for (int i = l; i < m; i++) {
		int left = m, right = r;
		while (right - left > 1) {
			int mid = (left + right) >> 1;
			if (a[mid] < a[i]) {
				left = mid;
			} else {
				right = mid;
			}
		}
		if (a[i] == a[left]) left--;
		if (a[left] < a[i]) cnt += left - m + 1;
	}
	ans += cnt;
}

void merge_sort(vector<int> &a, long long &ans, int l, int r) {
	if (r - l != 1) {
		int m = (l + r) >> 1;
		merge_sort(a, ans, l, m);
		merge_sort(a, ans, m, r);
		inv(a, ans, l, r, m);
		merge(a, l, r, m);
	}
}

unsigned int cur = 0;
unsigned int nextRand24(int a, int b) {
	cur = cur * a + b;
	return cur >> 8;
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;

	int a, b;
	cin >> a >> b;

	vector<int> arr(n);
	for (int i = 0; i < n; i++) {
		arr[i] = nextRand24(a, b) % m;
	}

	long long ans = 0;
	res.resize(n);
	merge_sort(arr, ans, 0, n);
	cout << ans;
}
