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

using namespace std;
using ll = long long;

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

unsigned int get_hash(unsigned int value, unsigned int poly, unsigned int add, unsigned int mod) {
	value = value * poly + add;
	value %= mod;
	return value;
}

void check_acyclic(vector<vector<pair<int, int>>> &g, vector<int> &used, bool &ok, int v, int p) {
	used[v] = 1;
	for (pair<int, int> u : g[v]) {
		if (u.f != p) {
			if (used[u.f] == 1) {
				ok = false;
			}
			if (used[u.f] == 0) {
				check_acyclic(g, used, ok, u.f, v);
			}
		}
	}
	used[v] = 2;
}

void dfs(vector<vector<pair<int, int>>> &g, vector<bool> &used, vector<unsigned int> &value, int v) {
	used[v] = true;
	for (pair<int, int> u : g[v]) {
		if (!used[u.f]) {
			value[u.f] = (value[v] ^ u.s);
			dfs(g, used, value, u.f);
		}
	}
}

string get_hex(unsigned int value) {
	string result;
	for (int i = 0; i < 4; i++) {
		unsigned int last = value % 256;
		result += (char) (last / 16 < 10 ? '0' + last / 16 : 'a' + last / 16 - 10);
		result += (char) (last % 16 < 10 ? '0' + last % 16 : 'a' + last % 16 - 10);
		value /= 256;
	}
	return result;
}

void solve() {
	unsigned int n;
	cin >> n;

	// mt19937 gen(3001);
	// set<unsigned int> b;
	vector<unsigned int> a(n);
	for (int i = 0; i < (int) n; i++) {
		cin >> a[i];
		// do {
		// 	a[i] = gen();
		// 	a[i] %= (int) 1e9 + 1;
		// } while (b.count(a[i]));
		// b.insert(a[i]);
	}

	unsigned int m = 10 * n;
	vector<vector<pair<int, int>>> g;
	unsigned int p1, p2, add1, add2;
	mt19937 rnd(10 * n);
	// int cnt = 0;
	
	while (true) {
		// cnt++;
		// cerr << cnt << '\n';
		p1 = 1;
		p2 = rnd();
		add1 = rnd() % n;
		add2 = rnd() % m;
		set<pair<unsigned int, unsigned int>> edges;
		g.clear();
		g.resize(m);
		bool ok = true;
		for (int i = 0; i < (int) n; i++) {
			unsigned int h1 = get_hash(a[i], p1, add1, m);
			unsigned int h2 = get_hash(a[i], p2, add2, m);
			if (h1 == h2) {
				ok = false;
			}
			edges.insert({min(h1, h2), max(h1, h2)});
			g[h1].push_back({h2, i});
			g[h2].push_back({h1, i});
		}
		if (size(edges) != (int) n) {
			ok = false;
		}
		vector<int> used(m, 0);
		for (int i = 0; i < (int) m && ok; i++) {
			if (used[i] == 0) {
				check_acyclic(g, used, ok, i, -1);
			}
		}
		if (ok) {
			break;
		}
	}
	// cout << "ok! " << cnt << " repeats\n";
	vector<unsigned int> value(m, 0);
	vector<bool> used(m, false);
	for (int i = 0; i < (int) m; i++) {
		if (!used[i]) {
			value[i] = 0;
			dfs(g, used, value, i);
		}
	}

	// bool ok = true;
	set<unsigned int> result;
	for (int i = 0; i < (int) n; i++) {
		unsigned int h1 = get_hash(a[i], p1, add1, m);
		unsigned int h2 = get_hash(a[i], p2, add2, m);
		unsigned int val = (value[h1] ^ value[h2]);
		// if (val != i) {
		// 	ok = false;
		// }
		result.insert(val);
	}

	// for (int i = 0; i < m; i++) {
	// 	cout << value[i] << '\n';
	// }

	// cout << p1 << ' ' << p2 << ' ' << m << '\n';
	// cout << n << ' ' << size(result) << ' ' << (ok ? "ok" : ":(") << '\n';

	/*
		r0 - input 

		r1 = p1  ~  31 01 _ _ _ _ (hex value p1) - put =6
		r2 = p2  ~  31 02 _ _ _ _ (hex value p2) - put =6
		r3 = m  ~  31 03 _ _ _ _ (hex value m) - put =6
		r8 = add1  ~ 31 08 _ _ _ _  - put = 6
		r9 = add2  ~ 31 09 _ _ _ _ =6
		
		r4 = h1 = (input * p1 + add1) % (ui) % m  ~  03 00 01 04 05 - mul [04;05] = 00*01 =5
													01 04 08 04 = 4
											  05 04 03 04 06 - mod [04] = [04;06] mod 03 =5

		r5 = h2 = (input * p2 + add2) % (ui) % m  ~  03 00 02 05 06 - mul =5
													01 05 09 05 = 4
											  05 05 03 05 07 - mod =5

		r7 = offset = 31 07 _ _ _ _ (hex value offset) - put =6

		r4 = r4 * 4 + offset  ~  01 04 04 04 - add =4
								 01 04 04 04 - add =4
								 01 04 07 04 - add =4

		r5 = r5 * 4 + offset  ~  01 05 05 05 - add =4
								 01 05 05 05 - add =4
								 01 05 07 05 - add =4
		
		r4 = value[r4]  ~  30 04 04 - load =3

		r5 = value[r5]  ~  30 05 05 - load =3

		r0 = r4 ^ r5  ~  12 04 05 00 =4

		ff =1
	*/

	// cout << "offset: " << 6 * 3 + 5 * 4 + 6 + 4 * 6 + 3 * 2 + 4 + 1 << '\n';

	string init = "3101" + get_hex(p1) +
				"3102" + get_hex(p2) +
				"3103" + get_hex(m) +
				"3108" + get_hex(add1) +
				"3109" + get_hex(add2) +
				"0300010405" + "01040804" + "0504030406" +
				"0300020506" + "01050905" + "0505030507" +
				"3107" + get_hex(99) +
				"01040404" + "01040404" + "01040704" +
				"01050505" + "01050505" + "01050705" +
				"300404" + "300505" + "12040500" + "ff";

	cout << init;
	for (int i = 0; i < (int) m; i++) {
		cout << get_hex(value[i]);
	}
}
