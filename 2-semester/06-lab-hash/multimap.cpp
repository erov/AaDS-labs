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

int const MOD = (int) 1e6;
int const SET_MOD = 200;
int const P = 31;

int get_hash(string &str, int poly, int mod) {
	int result = 0;
	for (char c : str) {
		result = result * poly + c;
		result %= mod;
	}
	return result;
}

struct Node
{
	string value;
	Node* prev = nullptr;
	Node* nxt = nullptr;

	Node(string _value) {
		value = _value;
	}
};

struct HashSet
{
	string key;
	int size = 0;
	Node* last_added = nullptr;
	vector<Node*> store[SET_MOD];

	HashSet(string _key) {
		key = _key;
	}

	void add_item(string &value) {
		int id = get_hash(value, P, SET_MOD);
		for (auto it : store[id]) {
			if (it->value == value) {
				return;
			}
		}
		Node* item = new Node(value);
		item->prev = last_added;
		if (last_added) {
			last_added->nxt = item;
		}
		store[id].push_back((last_added = item));
		size++;
	}

	void remove_item(string &value) {
		int id = get_hash(value, P, SET_MOD);
		for (auto &it : store[id]) {
			if (it->value == value) {
				if (it->prev) {
					it->prev->nxt = it->nxt;
				}
				if (it->nxt) {
					it->nxt->prev = it->prev;
				}
				if (last_added == it) {
					last_added = it->prev;
				}
				swap(it, store[id].back());
				store[id].pop_back();
				size--;
				return;
			}
		}
	}
};

struct HashMultiMap
{
	vector<HashSet*> store[MOD];

	HashMultiMap() {}

	void put_item(string &key, string &value) {
		int id = get_hash(key, P, MOD);
		for (auto &it : store[id]) {
			if (it->key == key) {
				it->add_item(value);
				return;
			}
		}
		store[id].push_back(new HashSet(key));
		store[id].back()->add_item(value);
	}

	void remove_item(string &key, string &value) {
		int id = get_hash(key, P, MOD);
		for (auto &it : store[id]) {
			if (it->key == key) {
				it->remove_item(value);
				return;
			}
		}
	}

	void remove_all(string &key) {
		int id = get_hash(key, P, MOD);
		for (auto &it : store[id]) {
			if (it->key == key) {
				swap(it, store[id].back());
				store[id].pop_back();
				return;
			}
		}
	}

	void print_all(string &key) {
		int id = get_hash(key, P, MOD);
		for (auto it : store[id]) {
			if (it->key == key) {
				cout << it->size;
				Node* ptr = it->last_added;
				while (ptr) {
					cout << ' ' << ptr->value;
					ptr = ptr->prev;
				}
				cout << '\n';
				return;
			}
		}
		cout << 0 << '\n';
	}
};

void solve() {
	HashMultiMap* store = new HashMultiMap();
	string type;
	while (cin >> type) {
		string key;
		cin >> key;
		if (type == "put") {
			string value;
			cin >> value;
			store->put_item(key, value);
		}
		if (type == "delete") {
			string value;
			cin >> value;
			store->remove_item(key, value);
		}
		if (type == "deleteall") {
			store->remove_all(key);
		}
		if (type == "get") {
			store->print_all(key);
		}
	}
}
