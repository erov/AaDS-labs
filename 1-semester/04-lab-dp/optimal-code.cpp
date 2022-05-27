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
const ll oo = 1e15;

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

void recover(vector<short> &code, vector<vector<int>> &opt, int l, int r) {
	if (r - l == 1) {
		for (auto i : code) {
			cout << i;
		}
		cout << '\n';
		return;
	}

	int m = opt[l][r];
	code.push_back(0);
	recover(code, opt, l, m);
	code.back() = 1;
	recover(code, opt, m, r);
	code.pop_back();
}

void solve() {
	int n;
	cin >> n;

	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	vector<vector<ll>> dp(n, vector<ll> (n + 1, oo));  // [ )
	vector<vector<int>> opt(n, vector<int> (n + 1, -1));
	vector<ll> sum(n);
	for (int i = 0; i < n; i++) {
		sum[i] = a[i] + (i ? sum[i - 1] : 0LL);
	}

	for (int l = 0; l < n; l++) {
		dp[l][l + 1] = 0;
		opt[l][l + 1] = l;
	}

	for (int len = 2; len <= n; len++) {
		for (int l = 0; l + len <= n; l++) {
			int r = l + len;
			for (int m = opt[l][r - 1]; m < opt[l + 1][r] + 1; m++) {
				if (dp[l][m] + dp[m][r] <= dp[l][r]) {
					dp[l][r] = dp[l][m] + dp[m][r];
					opt[l][r] = m;
				}
			}
			dp[l][r] += sum[r - 1] - (l ? sum[l - 1] : 0LL);
		}
	}

	cout << dp[0][n] << '\n';

	vector<short> code;
	recover(code, opt, 0, n);
}
