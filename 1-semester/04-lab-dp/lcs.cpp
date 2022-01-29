// #pragma GCC optimize("Ofast")
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

// continue push_back setprecision __builtin_popcount

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

void calculate(vector<int> &prev, string &a, string &b, int al, int ar, int bl, int br, bool type) {
	string a1, b1;
	a1 = a.substr(al, ar - al);
	b1 = b.substr(bl, br - bl);

	if (type) {
		reverse(all(a1));
		reverse(all(b1));
	}

	prev.resize(size(b) + 1, 0);
	vector<int> nxt(size(b) + 1, 0);

	for (int i = 1; i <= size(a1); i++) {
		for (int j = 1; j <= size(b1); j++) {
			nxt[j] = (a1[i - 1] == b1[j - 1] ? prev[j - 1] + 1 : max(prev[j], nxt[j - 1]));
		}
		prev.swap(nxt);
	}
}

void recover(string &a, string &b, string &ans, int al, int ar, int bl, int br) {
	if (al == ar || bl == br) {
		return;
	}
	if (ar - al == 1) {
		bool found = false;
		while (bl < br && !found) {
			found |= (a[al] == b[bl++]);
		}
		if (found) {
			ans += a[al];
		}
		return;
	}

	int m = br - bl;
	int am = (al + ar) >> 1;
	vector<int> left, right;

	calculate(left, a, b, al, am, bl, br, 0);
	calculate(right, a, b, am, ar, bl, br, 1);

	// cout << al << ' ' << am << '\n' << bl << ' ' << br << '\n';
	// cout << a.substr(al, ar - am) << '\n';
	// cout << << b.substr(bl, br - bl) << '\n';
	// for (int i = 0; i < size(b); i++) {
	// 	cout << left[i] << ' ';
	// }
	// cout << "\n\n";

	int mx = -oo, bm = -1;
	for (int i = 1; i < m; i++) {
		if (left[i] + right[m - i] > mx) {
			mx = left[i] + right[m - i];
			bm = bl + i;
		}
	}

	if (left[m] > mx) {
		mx = left[m];
		bm = br;
	}
	if (right[m] > mx) {
		mx = right[m];
		bm = bl;
	}

	// cout << "border: " << bm << " max: " << mx << '\n';

	recover(a, b, ans, al, am, bl, bm);
	recover(a, b, ans, am, ar, bm, br);
}

void solve() {
	string a, b;
	cin >> a >> b;

	string ans = "";
	recover(a, b, ans, 0, size(a), 0, size(b));

	cout << ans;
}
