#include <iostream>

using namespace std;

struct lst {
	int val;
	lst *nxt;
	lst() { }
	lst(int x) {
		val = x;
		nxt = nullptr;
	}
};

int main() {
	#ifdef HOME
	    freopen("home.in", "r", stdin);
	    freopen("home.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);

	lst *head = new lst(0);
	lst *tail = head;
	int n;
	cin >> n;

	while (n--) {
		char type;
		cin >> type;

		if (type == '+') {
			int x;
			cin >> x;
			lst *current = new lst(x);
			tail->nxt = current;
			tail = current;
		} else {
			cout << head->nxt->val << '\n';
			lst *first = head;
			head = first->nxt;
			delete first;
		}
	}
}
