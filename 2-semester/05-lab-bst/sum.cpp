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
	int rank;
	ll sum;
	node* left;
	node* right;

	node(int _value) {
		value = _value;
		rank = rnd();
		sum = _value;
		left = nullptr;
		right = nullptr;
	}
};

typedef node* treap;

ll get_sum(treap t) {
	return (t ? t->sum : 0LL);
}

void fix(treap t) {
	t->sum = get_sum(t->left) + t->value + get_sum(t->right);
}

treap treap_merge(treap a, treap b) {
	if (!a) {
		return b;
	}
	if (!b) {
		return a;
	}
	if (a->rank < b->rank) {
		a->right = treap_merge(a->right, b);
		fix(a);
		return a;
	} else {
		b->left = treap_merge(a, b->left);
		fix(b);
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
		fix(t);
		return {result.first, t};
	} else {
		auto result = treap_split(t->right, value);
		t->right = result.first;
		fix(t);
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

void solve() {
	int n;
	cin >> n;

	treap root = nullptr;
	ll last_ans = 0;
	const ll MOD = (ll) 1e9;
	for (int i = 0; i < n; i++) {
		char type;
		cin >> type;

		if (type == '+') {
			int value;
			cin >> value;
			root = insert(root, (int)((value + last_ans) % MOD));
			last_ans = 0;
		} else {
			int l, r;
			cin >> l >> r;
			auto a = treap_split(root, r + 1);
			auto b = treap_split(a.first, l);
			cout << (last_ans = get_sum(b.second)) << '\n';
			root = treap_merge(b.first, treap_merge(b.second, a.second));
		}
	}
}
