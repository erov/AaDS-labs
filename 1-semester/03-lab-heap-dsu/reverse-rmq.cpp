#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

void heap_swap(vector<pair<int, int>> &h, vector<int> &get_id, int i, int j) {
	swap(h[i], h[j]);
	get_id[h[i].second] = i;
	get_id[h[j].second] = j;
}

void sift_up(vector<pair<int, int>> &h, vector<int> &get_id, int i) {
	while (i > 0) {
		int j = (i - 1) / 2;
		if (h[i] > h[j]) {
			heap_swap(h, get_id, i, j);
			i = j;
		} else {
			break;
		}
	}
}

void sift_down(vector<pair<int, int>> &h, vector<int> &get_id, int i) {
	while (i * 2 + 1 < (int) h.size()) {
		int l = i * 2 + 1;
		int r = i * 2 + 2;
		if (r >= (int) h.size() || h[l] > h[r]) {
			if (h[i] < h[l]) {
				heap_swap(h, get_id, i, l);
				i = l;
			} else {
				break;
			}
		} else {
			if (h[i] < h[r]) {
				heap_swap(h, get_id, i, r);
				i = r;
			} else {
				break;
			}
		}
	}
}

void push(vector<pair<int, int>> &h, vector<int> &get_id, pair<int, int> elem) {
	h.push_back(elem);
	get_id[h.back().second] = (int) h.size() - 1;
	sift_up(h, get_id, (int) h.size() - 1);
}

pair<int, int> extract_max(vector<pair<int, int>> &h, vector<int> &get_id) {
	pair<int, int> ans = h[0];
	get_id[h[0].second] = -1;
	h[0] = h.back();
	get_id[h[0].second] = 0;
	h.pop_back();
	sift_down(h, get_id, 0);
	return ans;
}

void decrease_key(vector<pair<int, int>> &h, vector<int> &get_id, int id, int val) {
	if (get_id[id] == -1) {
		return;
	}
	int i = get_id[id];
	get_id[id] = -1;
	h[i].first = val;
	get_id[h[i].second] = i;
	sift_up(h, get_id, i);
}


int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	int n, m;
	cin >> n >> m;

	vector<vector<pair<int, pair<int, int>>>> fact(n + 1);
	int mx = INT_MIN;

	for (int i = 0; i < m; i++) {
		int l, r, val;
		cin >> l >> r >> val;
		l--, r--;
		fact[l].push_back({val, {0, i}});  // add
		fact[r + 1].push_back({val, {1, i}});  // extract
		mx = max(mx, val);
	}

	vector<pair<int, int>> h;
	vector<int> get_id(m);

	const int INF = INT_MAX;
	vector<int> ans(n, mx);
	for (int i = 0; i < n; i++) {
		for (auto it : fact[i]) {
			int val = it.first, type = it.second.first, pos = it.second.second;
			if (type == 0) {
				push(h, get_id, {val, pos});
			}
			if (type == 1) {
				decrease_key(h, get_id, pos, INF);
				extract_max(h, get_id);
			}
		}
		if (!h.empty()) {
			ans[i] = h[0].first;
		}

		cout << ans[i] << ' ';
	}
}
