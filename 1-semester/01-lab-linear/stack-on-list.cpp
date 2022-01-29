#include <iostream>

using namespace std;

struct lst {
	int val;
	lst *prev;
	lst() { }
	lst(int x) {
		val = x;
		prev = nullptr;
	}
};

int main() {
	#ifdef HOME
	    freopen("home.in", "r", stdin);
	    freopen("home.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);

	lst *tail = new lst(0);
	int n;
	cin >> n;

	while (n--) {
		char type;
		cin >> type;

		if (type == '+') {
			int x;
			cin >> x;
			lst *current = new lst(x);
			current->prev = tail->prev;
			tail->prev = current;
		} else {
			cout << tail->prev->val << '\n';
			lst *last = tail->prev;
			tail->prev = last->prev;
			delete last;
		}
	}
}
