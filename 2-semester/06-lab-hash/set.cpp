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

const int P = (int) 1e6 + 3;
const int MAX_VAL = (int) 1e9;

bool exists(vector<vector<int>> &store, int x);
int get_hash(int x);
int find(vector<vector<int>> &store, int x);

void insert(vector<vector<int>> &store, int x) {
	if (!exists(store, x)) {
		store[get_hash(x)].push_back(x);
	}
}

void remove(vector<vector<int>> &store, int x) {
	int pos = find(store, x);
	if (pos != -1) {
		int hash = get_hash(x);
		store[hash][pos] = store[hash].back();
		store[hash].pop_back();
	}
}

bool exists(vector<vector<int>> &store, int x) {
	return (find(store, x) != -1);
}


int get_hash(int x) {
	return (x + MAX_VAL) % P;
}

int find(vector<vector<int>> &store, int x) {
	int hash = get_hash(x);
	int i = 0;
	while (i < size(store[hash]) && store[hash][i] != x) {
		i++;
	}
	return (i == size(store[hash]) ? -1 : i);
}


void solve() {
	vector<vector<int>> store(P);
	string type;
	int x;

	while (cin >> type >> x) {
		if (type == "insert") {
			insert(store, x);
		}
		if (type == "delete") {
			remove(store, x);
		}
		if (type == "exists") {
			cout << (exists(store, x) ? "true\n" : "false\n");
		}
	}
}
