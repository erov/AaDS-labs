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

struct input {
	int value, rank, id;

	input() {}
	input(int _value, int _rank, int _id) {
		value = _value;
		rank = _rank;
		id = _id;
	}

	bool operator<(input &other) {
		return value < other.value;
	}
};

struct node {
	int value;
	int rank;
	int id;
	node* left;
	node* right;
	node* parent;

	node(input it) {
		value = it.value;
		rank = it.rank;
		id = it.id;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
};

typedef node* treap;

treap build(treap root, vector<input> &a) {
	treap last = nullptr;
	for (int i = 0; i < size(a); i++) {
		while (last && last->rank > a[i].rank) {
			last = last->parent;
		}

		treap current = new node(a[i]);
		if (last) {
			treap parent_right = last->right;
			last->right = current;
			current->parent = last;
			current->left = parent_right;
			if (parent_right) {
				parent_right->parent = current;
			}
		} else {
			if (root) {
				root->parent = current;
				current->left = root;
				root = current;
			} else {
				root = current;
			}
		}
		last = current;
	}
	return root;
}

void recovery(treap t, vector<vector<int>> &info) {
	if (!t) {
		return;
	}

	recovery(t->left, info);

	int id = t->id;
	info[id][0] = (t->parent ? t->parent->id : -1);
	info[id][1] = (t->left ? t->left->id : -1);
	info[id][2] = (t->right ? t->right->id : -1);

	recovery(t->right, info);
}

void solve() {
	int n;
	cin >> n;

	vector<input> a(n);
	for (int i = 0; i < n; i++) {
		int value, rank;
		cin >> value >> rank;
		a[i] = input(value, rank, i);
	}

	sort(all(a));

	treap root = nullptr;
	root = build(root, a);

	vector<vector<int>> info(n, vector<int> (3, -1));  // parent, left, right
	recovery(root, info);

	cout << "YES\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			cout << ++info[i][j] << ' ';
		}
		cout << '\n';
	}
}
