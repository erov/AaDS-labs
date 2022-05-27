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

int const MAXN = (int) 1e6 + 3;
int const MOD = (int) 1e9 + 3;
int const P = 73;
int const Q = 91;

struct node {
	int key_hash;
	string value;
	node* prev;
	node* nxt;

	node(int _key_hash, string _value) {
		key_hash = _key_hash;
		value = _value;
		prev = nullptr;
		nxt = nullptr;
	}
};
node* last_added = nullptr;
vector<node*> store[MAXN];

int get_hash(string &str, int poly, int mod) {
	ll result = 0;
	for (char c : str) {
		result = result * (ll) poly + (ll) (c - 'A' + 1);
		result = result % (ll) mod;
	}
	return (int) result;
}

int find_key(int id, int key_hash) {
	for (int i = 0; i < size(store[id]); i++) {
		if (store[id][i]->key_hash == key_hash) {
			return i;
		}
	}
	return -1;
}

void put(int id, int key_hash, string &value) {
	int i = find_key(id, key_hash);
	if (i != -1) {
		store[id][i]->value = value;
	} else {
		node* item = new node(key_hash, value);
		item->prev = last_added;
		if (last_added) {
			last_added->nxt = item;
		}
		store[id].push_back((last_added = item));
	}
}

void remove_item(int id, int key_hash) {
	int i = find_key(id, key_hash);
	if (i != -1) {
		swap(store[id][i], store[id].back());
		if (last_added == store[id].back()) {
			last_added = store[id].back()->prev;
		}
		if (store[id].back()->prev) {
			store[id].back()->prev->nxt = store[id].back()->nxt;
		}
		if (store[id].back()->nxt) {
			store[id].back()->nxt->prev = store[id].back()->prev;
		}
		store[id].pop_back();
	}
}

void print(int id, int key_hash) {
	int i = find_key(id, key_hash);
	cout << (i != -1 ? store[id][i]->value : "none") << '\n';
}

void print_prev(int id, int key_hash) {
	int i = find_key(id, key_hash);
	cout << (i != -1 && store[id][i]->prev ? store[id][i]->prev->value : "none") << '\n';
}

void print_next(int id, int key_hash) {
	int i = find_key(id, key_hash);
	cout << (i != -1 && store[id][i]->nxt ? store[id][i]->nxt->value : "none") << '\n';
}


void solve() {
	string type;

	while (cin >> type) {
		string key;
		cin >> key;

		int id = get_hash(key, P, MAXN);
		int key_hash = get_hash(key, Q, MOD);

		if (type == "put") {
			string value;
			cin >> value;
			put(id, key_hash, value);
		}
		if (type == "delete") {
			remove_item(id, key_hash);
		}
		if (type == "get") {
			print(id, key_hash);
		}
		if (type == "prev") {
			print_prev(id, key_hash);
		}
		if (type == "next") {
			print_next(id, key_hash);
		}
	}
}
