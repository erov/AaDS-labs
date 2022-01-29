#include <iostream>
#include <vector>

using namespace std;

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);

	while (true) {
		int n;
		cin >> n;

		if (!n) {
			break;
		}

		vector<int> a(n);
		int cnt = 0, ban = -1;
		for (int i = 0; i < n; i++) {
			cin >> a[i];
			cnt += a[i];
			ban = (a[i] && ban == -1 ? i : ban);
		}

		bool sorted = true;
		for (int i = 1; i < n; i++) {
			sorted &= (a[i - 1] <= a[i]);
		}

		if (sorted) {
			cout << -1 << '\n';
			continue;
		}

		vector<pair<int, int>> ans;
		for (int i = 0; i < n; i++) {
			if (a[i] && i != ban) {
				ans.push_back({ban, i});
			}
		}

		for (int i = 0; i < n; i++) {
			if (i == ban) {
				continue;
			}
			for (int j = i + 1; j < n; j++) {
				if (j == ban) {
					continue;
				}
				ans.push_back({i, j});
			}
		}

		for (int j = n - 1 - cnt; j > ban; j--) {
			ans.push_back({ban, j});
		}
		for (int j = 0; j < ban; j++) {
			ans.push_back({j, ban});
		}

		cout << (int) ans.size() << '\n';
		for (auto it : ans) {
			cout << ++it.first << ' ' << ++it.second << '\n';
		}
	}
}
