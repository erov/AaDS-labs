#include <iostream>
#include <vector>
#include <climits>
#include <assert.h>

using namespace std;

#define size(a) (int) a.size()

void print(int x, int y, int z, int &m) {
	cout << x << ' ' << y << ' ' << z << '\n';
	if (--m == 0) {
		exit(0);
	}
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	int n, m;
	cin >> n >> m;

	print(0, 1, 1, m);

	int i;
	for (i = 2; i <= 9; i += 2) {
		print(1, 1, i, m);
		print(1, 1, i + 1, m);
		print(0, i, i + 1, m);
	}

	for (; i <= n; i++) {
		print(1, i, (i == 10 ? 1 : i - 1), m);
		for (int j = 2; j <= 9; j += 2) {
			print(0, j, j + 1, m);
		}
	}
}
