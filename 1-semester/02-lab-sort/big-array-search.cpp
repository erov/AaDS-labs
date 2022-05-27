#include <iostream>

using namespace std;

typedef long long ll;

ll ask(ll x) {
	cout << "? " << x << endl;
	cin >> x;
	return x;
}

void ans(ll x) {
	cout << "! " << x << endl;
}

int main() {
	ios_base::sync_with_stdio(false);

	ll x, m;
	cin >> x >> m;

	const ll MAX_VALUE = (ll) 1e18;
	ll first = ask(1);
	x = x - first + 1 + (x < first ? MAX_VALUE : 0LL);

	bool found = 0;
	ll l = max(x - m - 1, 0LL), r = min(x + 1, MAX_VALUE - m + 1);
	while (r - l > 1) {
		ll mid = (l + r) >> 1;
		ll val = ask(mid);
		val = val - first + 1 + (val < first ? MAX_VALUE : 0LL);

		if (val == x) {
			ans(mid);
			found = 1;
			break;
		}
		if (val < x) {
			l = mid;
		} else {
			r = mid;
		}
	}

	if (!found) {
		ans(-1);
	}

	#ifdef HOME
		system("pause");
	#endif
}
