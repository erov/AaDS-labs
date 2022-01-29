#include <iostream>

using namespace std;

struct dque {
	pair<int, int> *a;
	int head, tail, n, cnt;
	dque(int sz) {
		a = new pair<int, int>[sz];
		head = 0, tail = -1, n = sz;
		cnt = 0;
	}
	void push(pair<int, int> x) {
		if (cnt == n) {
			pair<int, int> *b = new pair<int, int>[(n << 1)];
			for (int i = 0; i < cnt; i++) {
				b[i] = a[(head + i) % n];
			}
			head = 0, tail = cnt - 1;
			n = (n << 1);
			swap(a, b);
			delete b;
		}
		tail = (tail + 1) % n;
		a[tail] = x;
		cnt++;
	}

	void resize() {
		pair<int, int> *b = new pair<int, int>[(n >> 1)];
		int i = 0;
		while (true) {
			b[i] = a[head];
			head = (head + 1) % n;
			i++;
			if (i == cnt) {
				break;
			}
		}
		head = 0, tail = i - 1;
		n = (n >> 1);
		swap(a, b);
		delete b;
	}

	void pop_front() {
		head = (head + 1) % n;
		cnt--;
		if (cnt * 2 == n) {
			this->resize();
		}
	}

	void pop_back() {
		tail = (tail - 1 + n) % n;
		cnt--;
		if (cnt * 2 == n) {
			this->resize();
		}
	}

	pair<int, int> front() {
		return a[head];
	}

	pair<int, int> back() {
		return a[tail];
	}

	bool empty() {
		return cnt == 0;
	}
};

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);

	int n, m, k;
	cin >> n >> m >> k;

	long long a, b, c;
	cin >> a >> b >> c;

	long long *x = new long long[n];
	for (int i = 0; i < k; i++) {
		cin >> x[i];
	}

	long long const MAX_VALUE = ((1LL << 31) - 1), P = (1LL << 32);
	for (int i = k; i < n; i++) {
		long long y = a * x[i - 2] + b * x[i - 1] + c;
		long long mod = y % P;
		if (mod <= MAX_VALUE) {
			x[i] = mod;
		} else {
			x[i] = mod - P;
		}
	}
	dque q = dque(1);
	for (int i = 0; i < m; i++) {
		pair<int, int> val = {x[i], i};
		while (!q.empty() && q.back().first > val.first) {
			q.pop_back();
		}
		q.push(val);
	}

	long long ans = q.front().first;
	for (int i = m; i < n; i++) {
		pair<int, int> val = {x[i], i};
		while (!q.empty() && q.back().first > val.first) {
			q.pop_back();
		}
		q.push(val);
		while (q.front().second <= i - m) {
			q.pop_front();
		}
		ans += q.front().first;
	}

	cout << ans;
}
