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

struct node {
	int value;
	node* left;
	node* right;

	node(int _value) {
		value = _value;
		left = nullptr;
		right = nullptr;
	}
};

node* find(node* t, int value) {
	if (!t || t->value == value) {
		return t;
	}
	return (t->value > value ? find(t->left, value) : find(t->right, value));
}

node* insert(node* t, int value) {
	if (!t) {
		return new node(value);
	}
	if (t->value > value) {
		t->left = insert(t->left, value);
	} else {
		t->right = insert(t->right, value);
	}
	return t;
}

node* get_min(node* t) {
	if (!t || !t->left) {
		return t;
	}
	return get_min(t->left);
}

node* get_max(node* t) {
	if (!t || !t->right) {
		return t;
	}
	return get_max(t->right);
}

node* del(node* t, int value) {
	if (!t) {
		return t;
	}
	if (t->value == value) {
		if (!t->left) {
			return t->right;
		}
		if (!t->right) {
			return t->left;
		}
		node* min_value = get_min(t->right);  // always exists
		t->value = min_value->value;
		t->right = del(t->right, t->value);
		return t;
	}
	if (t->value > value) {
		t->left = del(t->left, value);
	} else {
		t->right = del(t->right, value);
	}
	return t;
}

node* next(node* t, int value) {
	if (!t) {
		return t;
	}
	node* result = get_max(t->left);
	if (result && result->value > value) {
		return next(t->left, value);
	}
	if (t->value > value) {
		return t;
	}
	return next(t->right, value);
}

node* prev(node* t, int value) {
	if (!t) {
		return t;
	}
	node* result = get_min(t->right);
	if (result && result->value < value) {
		return prev(t->right, value);
	}
	if (t->value < value) {
		return t;
	}
	return prev(t->left, value);
}


void solve() {
	string type;
	int x;
	node* root = nullptr;

	while (cin >> type >> x) {
		if (type == "exists") {
			node* result = find(root, x);
			cout << (result ? "true" : "false") << '\n';
		}
		if (type == "insert") {
			node* result = find(root, x);
			if (!result) {
				root = insert(root, x);
			}
		}
		if (type == "delete") {
			node* result = find(root, x);
			if (result) {
				root = del(root, x);
			}
		}
		if (type == "next") {
			node* result = next(root, x);
			if (!result) {
				cout << "none\n";
			} else {
				cout << result->value << '\n';
			}
		}
		if (type == "prev") {
			node* result = prev(root, x);
			if (!result) {
				cout << "none\n";
			} else {
				cout << result->value << '\n';
			}
		}
	}

	// cout << root->value << ' ';
	// cout << root->right->parent->value << ' ';
	// cout << root->right->left->parent->parent->value;
}
