#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <random>
#include <deque>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <bitset>
#include <stack>
#include <climits>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

mt19937 rnd(228);

const double EPS = 1e-7;
const double PI = acos(-1);
const ll oo = LLONG_MAX;

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define mp(a, b) make_pair(a, b)
#define size(a) (int)a.size()
#define f first
#define s second

void solve();

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		// freopen("censored.in", "r", stdin);
		// freopen("censored.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(false);
	#ifdef HOME
		clock_t start = clock();
	#endif

	solve();

	#ifdef HOME
		cout <<  "\n\n\nTIME: " << float(clock() - start) / CLOCKS_PER_SEC << endl;
		// system("pause");
	#endif

	exit(0);
}

vector<vector<ll>> mul(vector<vector<ll>> &a, vector<vector<ll>> &b, const ll MOD) {
	int n = size(a);
	int m = size(b[0]);
	vector<vector<ll>> res(n, vector<ll> (m, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < size(a[0]); k++) {
				res[i][j] += a[i][k] * b[k][j];
				res[i][j] %= MOD;
			}
		}
	}
	return res;
}

vector<vector<ll>> binpow(vector<vector<ll>> a, ll n, const ll MOD) {
	vector<vector<ll>> res = a;
	for (int i = 0; i < size(a); i++) {
		for (int j = 0; j < size(a[0]); j++) {
			res[i][j] = (i == j);
		}
	}
	n--;
	while (n) {
		if (n & 1) {
			res = mul(res, a, MOD);
			n--;
		}
		a = mul(a, a, MOD);
		n >>= 1;
	}
	return res;
}

void solve() {
	vector<vector<ll>> m(5, vector<ll> (5));
	m = {{1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 0, 0}, {1, 1, 1, 1, 1}, {1, 1, 1, 0, 0}};

	const ll MOD = 999999937;

	while (true) {
		ll n;
		cin >> n;

		if (n == 0) {
			break;
		}

		vector<vector<ll>> res = binpow(m, n, MOD);
		vector<vector<ll>> base(1, vector<ll> (5, 1));
		res = mul(base, res, MOD);

		ll ans = 0;
		for (auto i : res) {
			for (auto j : i) {
				ans += j;
				ans %= MOD;
			}
		}

		cout << ans << '\n';
	}
}
