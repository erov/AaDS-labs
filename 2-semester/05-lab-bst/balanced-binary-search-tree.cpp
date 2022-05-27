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

struct node {
	int value;
	int rank;
	node* left;
	node* right;

	node(int _value) {
		value = _value;
		rank = rnd();
		left = nullptr;
		right = nullptr;
	}
};

typedef node* treap;

treap treap_merge(treap a, treap b) {
	if (!a) {
		return b;
	}
	if (!b) {
		return a;
	}
	if (a->rank < b->rank) {
		a->right = treap_merge(a->right, b);
		return a;
	} else {
		b->left = treap_merge(a, b->left);
		return b;
	}
}

pair<treap, treap> treap_split(treap t, int value) {  // (-oo, value) [value, +oo)
	if (!t) {
		return {nullptr, nullptr};
	}
	if (t->value >= value) {
		auto result = treap_split(t->left, value);
		t->left = result.second;
		return {result.first, t};
	} else {
		auto result = treap_split(t->right, value);
		t->right = result.first;
		return {t, result.second};
	}
}

bool find(node* t, int value) {
	auto a = treap_split(t, value);
	auto b = treap_split(a.second, value + 1);
	bool result = (b.first ? 1 : 0);
	t = treap_merge(a.first, treap_merge(b.first, b.second));
	return result;
}

treap insert(treap t, int value) {
	if (!find(t, value)) {
		auto a = treap_split(t, value);
		t = treap_merge(a.first, treap_merge(new node(value), a.second));
	}
	return t;
}

treap get_min(treap t) {
	if (!t || !t->left) {
		return t;
	}
	return get_min(t->left);
}

treap get_max(treap t) {
	if (!t || !t->right) {
		return t;
	}
	return get_max(t->right);
}

treap del(treap t, int value) {
	auto a = treap_split(t, value);
	auto b = treap_split(a.second, value + 1);
	t = treap_merge(a.first, b.second);
	return t;
}

treap next(treap t, int value) {
	auto a = treap_split(t, value + 1);
	treap result = get_min(a.second);
	t = treap_merge(a.first, a.second);
	return result;
}

treap prev(treap t, int value) {
	auto a = treap_split(t, value);
	treap result = get_max(a.first);
	t = treap_merge(a.first, a.second);
	return result;
}


void solve() {
	string type;
	int x;
	treap root = nullptr;

	while (cin >> type >> x) {
		if (type == "exists") {
			bool result = find(root, x);
			cout << (result ? "true" : "false") << '\n';
		}
		if (type == "insert") {
			root = insert(root, x);
		}
		if (type == "delete") {
			root = del(root, x);
		}
		if (type == "next") {
			treap result = next(root, x);
			if (!result) {
				cout << "none\n";
			} else {
				cout << result->value << '\n';
			}
		}
		if (type == "prev") {
			treap result = prev(root, x);
			if (!result) {
				cout << "none\n";
			} else {
				cout << result->value << '\n';
			}
		}
	}
}
