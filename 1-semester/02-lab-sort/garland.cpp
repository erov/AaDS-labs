#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);

	int n;
	double a;
	cin >> n >> a;

	double l = 0, r = 1e9;
	double *h = new double[n];
	h[0] = a;
	for (int p = 0; p < 100; p++) {
		double m = (l + r) / 2;
		double down = min(a, m);
		h[1] = m;
		for (int i = 2; i < n; i++) {
			h[i] = 2 * h[i - 1] - h[i - 2] + 2;
			down = min(down, h[i]);
		}

		if (down > 0) {
			r = m;
		} else {
			l = m;
		}
	}

	cout << fixed << setprecision(2) << h[n - 1];
}
