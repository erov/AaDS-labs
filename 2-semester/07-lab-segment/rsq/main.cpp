#include <climits>
#include <iostream>
#include <vector>

using namespace std;

struct SegmentTree {

    void build(vector<long long> &a, int tl, int tr, int v) {
        if (tr - tl == 1) {
            tree[v] = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(a, tl, tm, v * 2 + 1);
        build(a, tm, tr, v * 2 + 2);
        tree[v] = tree[v * 2 + 1] + tree[v * 2 + 2];
    }

    void update(int tl, int tr, int v, int pos, long long value) {
        if (tr - tl == 1) {
            tree[v] = value;
            return;
        }
        int tm = (tl + tr) / 2;
        if (pos < tm) {
            update(tl, tm, v * 2 + 1, pos, value);
        } else {
            update(tm, tr, v * 2 + 2, pos, value);
        }
        tree[v] = tree[v * 2 + 1] + tree[v * 2 + 2];
    }

    long long get_sum(int tl, int tr, int v, int l, int r) {
        if (tr <= l || tl >= r) {
            return 0;
        }
        if (l <= tl && tr <= r) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        return get_sum(tl, tm, v * 2 + 1, l, r) + get_sum(tm, tr, v * 2 + 2, l, r);
    }

private:
    long long* tree = (long long*) malloc(sizeof(long long) * 2000000);
};


int main() {

    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    auto* tree = new SegmentTree();
    tree->build(a, 0, n, 0);

    string op;
    while (cin >> op) {
        if (op == "sum") {
            int l, r;
            cin >> l >> r;
            cout << tree->get_sum(0, n, 0, l - 1, r) << '\n';
        } else {
            int i, x;
            cin >> i >> x;
            tree->update(0, n, 0, i - 1, x);
        }
    }
}
