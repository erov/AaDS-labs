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
	int sz;
	node* left;
	node* right;

	node(int _value) {
		value = _value;
		rank = rnd();
		sz = 1;
		left = nullptr;
		right = nullptr;
	}
};

typedef node* treap;

int get_size(treap t) {
	return (t ? t->sz : 0);
}

void fix(treap t) {
	t->sz = get_size(t->left) + 1 + get_size(t->right);
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

pair<treap, treap> treap_split(treap t, int cnt) {  // {cnt, size - cnt}
	if (!t) {
		return {nullptr, nullptr};
	}
	int left_sz = get_size(t->left);
	if (cnt <= left_sz) {
		auto result = treap_split(t->left, cnt);
		t->left = result.second;
		fix(t);
		return {result.first, t};
	} else {
		auto result = treap_split(t->right, cnt - left_sz - 1);
		t->right = result.first;
		fix(t);
		return {t, result.second};
	}
}

int dsu_get(vector<int> &p, int v) {
	return (v == p[v] ? v : p[v] = dsu_get(p, p[v]));
}

void dsu_unite(vector<int> &p, int a, int b) {  // a -> b
	a = dsu_get(p, a);
	b = dsu_get(p, b);
	p[a] = b;
}

void solve() {
	treap root = nullptr;

	int n, m;
	cin >> n >> m;

	const int MAXN = (int) 3e5;
	for (int i = 0; i < MAXN; i++) {
		root = treap_merge(root, new node(0));
	}

	vector<int> p(MAXN);
	for (int i = 0; i < MAXN; i++) {
		p[i] = i;
	}

	for (int i = 1; i <= n; i++) {
		int pos;
		cin >> pos;

		int actual_pos = dsu_get(p, pos);
		auto a = treap_split(root, actual_pos - 1);
		auto b = treap_split(a.second, 1);
		root = treap_merge(a.first, b.second);
		a = treap_split(root, pos - 1);
		root = treap_merge(a.first, treap_merge(new node(i), a.second));
		dsu_unite(p, actual_pos, actual_pos + 1);

		// cout << actual_pos << '\n';
		// for (int j = 0; j < 10; j++) {
		// 	cout << j << ' ' << p[j] << '\n';
		// }
		// cout << '\n';
	}

	vector<int> ans;
	while (root) {
		auto a = treap_split(root, 1);
		ans.push_back(a.first->value);
		root = a.second;
	}

	int cnt = 0, pos = 0;
	while (pos < MAXN && cnt < n) {
		cnt += (ans[pos] != 0);
		pos++;
	}

	cout << pos << '\n';
	for (int i = 0; i < pos; i++) {
		cout << ans[i] << ' ';
	}
}
