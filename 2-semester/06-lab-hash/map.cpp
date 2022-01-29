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

const int MOD = (int) 1e6 + 3;
const int MOD_BIG = (int) 1e9 + 7;
const int P = 59;
const int Q = 73;

int get_hash(string x, int poly, int mod);
int find(vector<vector<pair<int, string>>> &store, string &x);

void put(vector<vector<pair<int, string>>> &store, string &x, string &y) {
	int hash = get_hash(x, P, MOD);
	int pos = find(store, x);
	if (pos == -1) {
		int additional_hash = get_hash(x, Q, MOD_BIG);
		store[hash].push_back({additional_hash, y});
	} else {
		store[hash][pos].s = y;
	}
}

void remove(vector<vector<pair<int, string>>> &store, string &x) {
	int pos = find(store, x);
	if (pos != -1) {
		int hash = get_hash(x, P, MOD);
		store[hash][pos] = store[hash].back();
		store[hash].pop_back();
	}
}

string get(vector<vector<pair<int, string>>> &store, string &x) {
	int pos = find(store, x);
	if (pos != -1) {
		int hash = get_hash(x, P, MOD);
		return store[hash][pos].s;
	}
	return "none";
}


int get_hash(string x, int poly, int mod) {
	ll hash = 0;
	for (auto it : x) {
		// cout << hash * poly + it - 'A' - 1 << ' ';
		hash = (hash * poly + it - 'A' + 1) % (1LL * mod);
		// cout << hash << ' ';
	}
	// cout << '\n';
	return (int) hash;
}

int find(vector<vector<pair<int, string>>> &store, string &x) {
	int hash = get_hash(x, P, MOD);
	int additional_hash = get_hash(x, Q, MOD_BIG);
	int i = 0;
	while (i < size(store[hash]) && store[hash][i].f != additional_hash) {
		i++;
	}
	return (i == size(store[hash]) ? -1 : i);
}


void solve() {
	vector<vector<pair<int, string>>> store(MOD);
	string type;

	while (cin >> type) {
		if (type == "put") {
			string x, y;
			cin >> x >> y;
			put(store, x, y);
		}
		if (type == "delete") {
			string x;
			cin >> x;
			remove(store, x);
		}
		if (type == "get") {
			string x;
			cin >> x;
			cout << get(store, x) << '\n';
		}
	}
}
