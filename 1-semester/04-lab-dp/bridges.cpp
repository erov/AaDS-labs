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
const int oo = INT_MAX;

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

void solve() {
	int x, a, y, b, len;
	cin >> x >> a >> y >> b >> len;

	int l = 0, r = x * a + y * b + 1;
	while (r - l > 1) {
		int m = (l + r) >> 1;

		int longest = 0;
		vector<vector<int>> dp(x + 1, vector<int> (y + 1, 0));
		for (int i = 0; i <= x; i++) {
			for (int j = 0; j <= y; j++) {
				for (int k = 0; k <= i; k++) {
					int left = m - k * a;
					left = max(0, left);
					left = (left + b - 1) / b;
					if (left <= j) {
						dp[i][j] = max(dp[i][j], 1 + dp[i - k][j - left]);
					}
				}
				longest = max(longest, dp[i][j]);
			}
		}

		if (longest >= len) {
			l = m;
		} else {
			r = m;
		}
	}

	cout << l;
}
