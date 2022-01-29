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

int convert(string s) {
	int result = 0;
	for (auto it : s) {
		result = result * 10 + (it - '0');
	}
	return result;
}

int main() {
    #ifdef HOME
        freopen("home.in", "r", stdin);
        freopen("home.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    stack a;
    string s;

    while (cin >> s) {
		if (s == "+" || s == "-" || s == "*") {
			int second = a.top();
			a.pop();
			int first = a.top();
			a.pop();
			if (s == "+") {
				a.push(first + second);
			} else if (s == "-") {
				a.push(first - second);
			} else {
				a.push(first * second);
			}
		} else {
			a.push(convert(s));
		}
	}

	cout << a.top();
}
