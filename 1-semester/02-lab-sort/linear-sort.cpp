#include <iostream>

using namespace std;

unsigned int cur = 0;
unsigned int nextRand24(const int a, const int b) {
	cur = cur * a + b;
	return cur >> 8;
}
unsigned int nextRand32(const int a, const int b) {
	unsigned int A = nextRand24(a, b), B = nextRand24(a, b);
	return (A << 8) ^ B;
}

struct my_vector {
	int *a, n, tail = 0;
	my_vector(int sz) {
		a = new int[sz];
		n = sz;
	}
	my_vector() {
		a = new int[1];
		n = 1;
	}
	void push_back(int x) {
		if (n == tail) {
			int* b = new int[n << 1];
			for (int i = 0; i < n; i++) {
				b[i] = a[i];
			}
			n <<= 1;
			swap(a, b);
			delete b;
		}
		a[tail++] = x;
	}
	void clear() {
		delete a;
		a = new int[1];
		n = 1, tail = 0;
	}
	int size() {
		return tail;
	}
	int& operator[](int id) {
		return a[id];
	}
};

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);

	int t, n;
	cin >> t >> n;

	const int MAXN = 100000, P = 256;  // then number length = 32 / 8 = 4
	unsigned int *arr = new unsigned int[MAXN];
	unsigned int *tmp = new unsigned int[MAXN];
	my_vector *id = new my_vector[P];

	while (t--) {
		int a, b;
		cin >> a >> b;

		for (int i = 0; i < n; i++) {
			arr[i] = nextRand32(a, b);
		}

		for (int p = 0; p < 4; p++) {
			for (int i = 0; i < n; i++) {
				id[(arr[i] >> (8 * p)) & 255].push_back(i);
			}
			int pos = 0;
			for (int i = 0; i < P; i++) {
				for (int t = 0; t < id[i].size(); t++) {
					int l = id[i][t];
					tmp[pos++] = arr[l];
				}
				id[i].clear();
			}
			for (int i = 0; i < n; i++) {
				arr[i] = tmp[i];
			}
		}
		unsigned long long ans = 0, val;
		for (int i = 0; i < n; i++) {
			val = arr[i];
			ans += val * (i + 1);
		}
		cout << ans << '\n';
	}
}
