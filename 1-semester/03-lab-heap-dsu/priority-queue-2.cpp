#include <iostream>
#include <vector>
#include <map>

using namespace std;

void heap_swap(vector<pair<int, int>> &h, map<int, int> &get_id, int i, int j) {
	swap(h[i], h[j]);
	get_id[h[i].second] = i;
	get_id[h[j].second] = j;
}

void sift_up(vector<pair<int, int>> &h, map<int, int> &get_id, int i) {
	while (i > 0) {
		int j = (i - 1) / 2;
		if (h[i] < h[j]) {
			heap_swap(h, get_id, i, j);
			i = j;
		} else {
			break;
		}
	}
}

void sift_down(vector<pair<int, int>> &h, map<int, int> &get_id, int i) {
	while (i * 2 + 1 < (int) h.size()) {
		int l = i * 2 + 1;
		int r = i * 2 + 2;
		if (r >= (int) h.size() || h[l] < h[r]) {
			if (h[i] > h[l]) {
				heap_swap(h, get_id, i, l);
				i = l;
			} else {
				break;
			}
		} else {
			if (h[i] > h[r]) {
				heap_swap(h, get_id, i, r);
				i = r;
			} else {
				break;
			}
		}
	}
}

void push(vector<pair<int, int>> &h, map<int, int> &get_id, pair<int, int> elem) {
	h.push_back(elem);
	get_id[h.back().second] = (int) h.size() - 1;
	sift_up(h, get_id, (int) h.size() - 1);
}

pair<int, int> extract_min(vector<pair<int, int>> &h, map<int, int> &get_id) {
	pair<int, int> ans = h[0];
	get_id.erase(h[0].second);
	h[0] = h.back();
	get_id[h[0].second] = 0;
	h.pop_back();
	sift_down(h, get_id, 0);
	return ans;
}

void decrease_key(vector<pair<int, int>> &h, map<int, int> &get_id, int id, int val) {
	if (!get_id.count(id)) {
		return;
	}
	int i = get_id[id];
	get_id.erase(id);
	h[i].first = val;
	get_id[h[i].second] = i;
	sift_up(h, get_id, i);
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	vector<pair<int, int>> h;
	map<int, int> get_id;

	string type;
	int cnt = 0;

	while (cin >> type) {
		cnt++;
		if (type == "push") {
			int val;
			cin >> val;
			push(h, get_id, {val, cnt});
		}
		if (type == "extract-min") {
			if (h.empty()) {
				cout << '*' << '\n';
			} else {
				pair<int, int> ans = extract_min(h, get_id);
				cout << ans.first << ' ' << ans.second << '\n';
			}
		}
		if (type == "decrease-key") {
			int id, val;
			cin >> id >> val;
			decrease_key(h, get_id, id, val);
		}
	}
}
