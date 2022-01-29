#include <iostream>

using namespace std;

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;

	int *a = new int[n + 1];
	bool ok = true;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		if (i != i / 2 && i > 1) {
			ok &= (a[i / 2] <= a[i]);
		}
	}

	cout << (ok ? "YES" : "NO");
}
