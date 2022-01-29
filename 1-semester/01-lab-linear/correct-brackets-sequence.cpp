#include <iostream>

using namespace std;

struct vctr {
	int *a, n, tail;
	vctr(int sz) {
		a = new int[sz];
		n = sz;
		tail = 0;
	}
	void push_back(int x) {
		if (n == tail) {
			int* b = new int[n << 1];
			for (int i = 0; i < n; i++) {
				b[i] = a[i];
			}
			n <<= 1;
			swap(a, b);
			delete b;
		}
		a[tail++] = x;
	}
	void pop_back() {
		tail--;
		if (tail * 2 == n) {
			int* b = new int[n >> 1];
			for (int i = 0; i < tail; i++) {
				b[i] = a[i];
			}
			n >>= 1;
			swap(a, b);
			delete b;
		}
	}
	int& operator[](int id) {
		return a[id];
	}
};

struct stack {
	vctr a = vctr(1);

	void push(int x) {
		a.push_back(x);
	}
	void pop() {
		a.pop_back();
	}
	int top() {
		return a[a.tail - 1];
	}
	bool empty() {
		return (a.tail ? 0 : 1);
	}
};

int main() {
    #ifdef HOME
        freopen("home.in", "r", stdin);
        freopen("home.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);

    string s;

    while (getline(cin, s)) {
    	stack a;
    	bool ok = 1;
    	int n = s.size();
    	for (int i = 0; i < n; i++) {
    		if (s[i] == '(') {
    			a.push(0);
    		}
    		if (s[i] == '[') {
    			a.push(1);
    		}
    		if (s[i] == ')') {
    			if (a.empty() || a.top() != 0) {
    				ok = 0;
    				break;
    			}
    			a.pop();
    		}
    		if (s[i] == ']') {
    			if (a.empty() || a.top() != 1) {
    				ok = 0;
    				break;
    			}
    			a.pop();
    		}
    	}
    	if (!a.empty()) {
    		ok = 0;
    	}
    	cout << (ok ? "YES\n" : "NO\n");
    }
}
