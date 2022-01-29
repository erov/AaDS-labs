#include <iostream>
#include <vector>

using namespace std;

void bs(vector<vector<pair<int, int>>> &comp, int d) {
	comp.push_back(vector<pair<int, int>>());
	for (int i = 0; i < 16; i += (1 << d)) {
		for (int j = i, k = i + (1 << d) / 2; j < i + (1 << d) / 2; j++, k++) {
			comp.back().push_back({j, k});
		}
	}
}

void merge(vector<vector<pair<int, int>>> &ans, vector<vector<pair<int, int>>> &comp, int d) {
	ans.push_back(vector<pair<int, int>>());
	for (int i = 0; i < 16; i += (1 << d)) {
		for (int j = i, k = i + (1 << d) - 1; j < i + (1 << d) / 2; j++, k--) {
			ans.back().push_back({j, k});
		}
	}
	for (int i = d - 1; i >= 1; i--) {
		ans.push_back(comp[i - 1]);
	}
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;

	vector<vector<pair<int, int>>> comp;
	for (int i = 1; i <= 4; i++) {
		bs(comp, i);
	}

	vector<vector<pair<int, int>>> ans;
	for (int i = 1; i <= 4; i++) {
		merge(ans, comp, i);
	}

	vector<vector<pair<int, int>>> sorting_network;
	int m = 0;
	for (int i = 0; i < (int) ans.size(); i++) {
		vector<pair<int, int>> cur;
		for (auto it : ans[i]) {
			if (it.first + 1 <= n && it.second + 1 <= n) {
				cur.push_back({it.first + 1, it.second + 1});
				m++;
			}
		}
		if (!cur.empty()) {
			sorting_network.push_back(cur);
		}
	}

	cout << n << ' ' << m << ' ' << sorting_network.size() << '\n';
	for (int i = 0; i < (int) sorting_network.size(); i++) {
		cout << sorting_network[i].size();
		for (int j = 0; j < (int) sorting_network[i].size(); j++) {
			cout << ' ' << sorting_network[i][j].first << ' ' << sorting_network[i][j].second;
		}
		cout << '\n';
	}
}
