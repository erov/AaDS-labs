#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);

	int n, m, k;
	cin >> n >> m >> k;

	string *s = new string[n];
	string *str = new string[n];
	for (int i = 0; i < n; i++) {
		cin >> s[i];
	}

	const int ALP = 26;
	for (int p = m - 1; k > 0; k--, p--) {
		vector<int> id[ALP];
		for (int i = 0; i < n; i++) {
			id[s[i][p] - 'a'].push_back(i);
		}
		int pos = 0;
		for (int i = 0; i < ALP; i++) {
			for (int t : id[i]) {
				str[pos++] = s[t];
			}
		}
		swap(s, str);
	}

	for (int i = 0; i < n; i++) {
		cout << s[i] << '\n';
	}
}
