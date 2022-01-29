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

	int *a = new int[n];
	for (int i = 0; i < n; i++) {
		a[i] = i + 1;
		swap(a[i], a[i / 2]);
	}

	for (int i = 0; i < n; i++) {
		cout << a[i] << ' ';
	}
}
