#include <iostream>

using namespace std;

struct vctr {
	int *a, head, tail, n, cnt;
	vctr(int sz) {
		a = new int[sz];
		head = 0, tail = -1, n = sz;
		cnt = 0;
	}
	void push(int x) {
		if (cnt == n) {
			int *b = new int[(n << 1)];
			for (int i = 0; i < cnt; i++) {
				b[i] = a[(head + i) % n];
			}
			head = 0, tail = cnt - 1;
			n = (n << 1);
			swap(a, b);
			delete b;
		}
		tail = (tail + 1) % n;
		a[tail] = x;
		cnt++;
	}

	void pop() {
		head = (head + 1) % n;
		cnt--;
		if (cnt * 2 == n) {
			int *b = new int[(n >> 1)], i = 0;
			while (true) {
				b[i] = a[head];
				head = (head + 1) % n;
				i++;
				if (i == cnt) {
					break;
				}
			}
			head = 0, tail = i - 1;
			n = (n >> 1);
			swap(a, b);
			delete b;
		}
	}

	int& operator[](int id) {
		return a[id];
	}
};

int main() {
    #ifdef HOME
        freopen("home.in", "r", stdin);
        freopen("home.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);

    vctr a = vctr(1);
    int n;
    cin >> n;

    while (n--) {
    	char type;
    	cin >> type;

    	if (type == '+') {
    		int x;
    		cin >> x;
    		a.push(x);
    	} else {
    		cout << a[a.head] << '\n';
    		a.pop();
    	}
    }
}
