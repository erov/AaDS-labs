#include <iostream>
#include <string>
#include <map>

using namespace std;

typedef unsigned int ll;

struct que {
	ll *a;
	int head, tail, n, cnt;
	que(int sz) {
		a = new ll[sz];
		head = 0, tail = -1, n = sz;
		cnt = 0;
	}
	void push(ll x) {
		if (cnt == n) {
			ll *b = new ll[(n << 1)];
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
		a[head] = 0;
		head = (head + 1) % n;
		cnt--;
		if (cnt * 2 == n) {
			ll *b = new ll[(n >> 1)];
			int i = 0;
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

	ll front() {
		return a[head];
	}

	bool empty() {
		return cnt == 0;
	}
};

struct vctr {
	string *a;
	int head, tail, n, cnt;
	vctr(int sz) {
		a = new string[sz];
		head = 0, tail = -1, n = sz;
		cnt = 0;
	}
	void push_back(string x) {
		if (cnt == n) {
			string *b = new string[(n << 1)];
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

	string& operator[](int id) {
		return a[id];
	}

	int size() {
		return cnt;
	}
};

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);

	vctr command = vctr(1);
	que q = que(1);
	map<string, int> go_to;
	const ll MOD = 65536LL;
	const int MAXN = 30;

	ll reg[MAXN];
	for (int i = 0; i < MAXN; i++) {
		reg[i] = MOD + i + 47;
	}
	string s;
	for (int i = 0; getline(cin, s); i++) {
		command.push_back(s);
		if (s[0] == ':') {
			go_to[s.substr(1)] = i;
		}
	}

	int i = 0;
	while (i < command.size()) {
		s = command[i];
		if (s == "+") {
			ll x = q.front();
			q.pop();
			ll y = q.front();
			q.pop();
			q.push((x + y) % MOD);
			i++;
			continue;
		}
		if (s == "-") {
			ll x = q.front();
			q.pop();
			ll y = q.front();
			q.pop();
			q.push((x - y) % MOD);
			i++;
			continue;
		}
		if (s == "*") {
			ll x = q.front();
			q.pop();
			ll y = q.front();
			q.pop();
			q.push((x * y) % MOD);
			i++;
			continue;
		}
		if (s == "/") {
			ll x = q.front();
			q.pop();
			ll y = q.front();
			q.pop();
			q.push((y ? x / y : 0));
			i++;
			continue;
		}
		if (s == "%") {
			ll x = q.front();
			q.pop();
			ll y = q.front();
			q.pop();
			q.push((y ? x % y : 0));
			i++;
			continue;
		}
		if (s[0] == '>') {
			ll x = q.front();
			q.pop();
			reg[s[1] - 'a'] = x;
			i++;
			continue;
		}
		if (s[0] == '<') {
			q.push(reg[s[1] - 'a']);
			i++;
			continue;
		}
		if (s == "P") {
			ll x = q.front();
			q.pop();
			cout << x << '\n';
			i++;
			continue;
		}
		if (s[0] == 'P') {
			cout << reg[s[1] - 'a'] << '\n';
			i++;
			continue;
		}
		if (s == "C") {
			ll x = q.front();
			q.pop();
			cout << char(x % 256LL);
			i++;
			continue;
		}
		if (s[0] == 'C') {
			cout << char(reg[s[1] - 'a'] % 256LL);
			i++;
			continue;
		}
		if (s[0] == ':') {
			i++;
			continue;
		}
		if (s[0] == 'J') {
			i = go_to[s.substr(1)];
			continue;
		}
		if (s[0] == 'Z') {
			if (reg[s[1] - 'a'] == 0) {
				i = go_to[s.substr(2)];
			} else {
				i++;
			}
			continue;
		}
		if (s[0] == 'E') {
			if (reg[s[1] - 'a'] == reg[s[2] - 'a']) {
				i = go_to[s.substr(3)];
			} else {
				i++;
			}
			continue;
		}
		if (s[0] == 'G') {
			if (reg[s[1] - 'a'] > reg[s[2] - 'a']) {
				i = go_to[s.substr(3)];
			} else {
				i++;
			}
			continue;
		}
		if (s == "Q") {
			break;
		}
		ll x = stoi(s);
		q.push(x);
		i++;
	}
}
