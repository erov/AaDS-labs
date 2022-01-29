#include <iostream>
#include <vector>

using namespace std;

unsigned int a, b;
unsigned int cur;
unsigned int nextRand() {
    cur = cur * a + b;
    return cur >> 8;
}

int main() {
    const int n = (1 << 24) + 47;
    int m, q;
    cin >> m >> q >> a >> b;

    auto tree = (unsigned int*) calloc(n, sizeof(unsigned int));

    while (m--) {
        unsigned int value, l, r;
        value = nextRand();
        l = nextRand();
        r = nextRand();
        if (l > r) {
            swap(l, r);
        }
        tree[l] += value;
        tree[r + 1] -= value;
    }

    for (int i = 1; i < n; i++) {
        tree[i] += tree[i - 1];
    }
    for (int i = 1; i < n; i++) {
        tree[i] += tree[i - 1];
    }

    unsigned int ans = 0;
    while (q--) {
        unsigned int l, r;
        l = nextRand();
        r = nextRand();
        if (l > r) {
            swap(l, r);
        }
        ans += tree[r];
        ans -= (l ? tree[l - 1] : 0);
    }

    cout << ans;
}
