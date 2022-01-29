#include <climits>
#include <iostream>
#include <vector>

using namespace std;

struct SegmentTree {

    void build(vector<int> &a, int tl, int tr, int v) {
        if (tr - tl == 1) {
            tree[v] = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(a, tl, tm, v * 2 + 1);
        build(a, tm, tr, v * 2 + 2);
        tree[v] = min(tree[v * 2 + 1], tree[v * 2 + 2]);
    }

    void update(int tl, int tr, int v, int pos, int value) {
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
        tree[v] = min(tree[v * 2 + 1], tree[v * 2 + 2]);
    }

    int get_min(int tl, int tr, int v, int l, int r) {
        if (tr <= l || tl >= r) {
            return INT_MAX;
        }
        if (l <= tl && tr <= r) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        return min(get_min(tl, tm, v * 2 + 1, l, r), get_min(tm, tr, v * 2 + 2, l, r));
    }

private:
    int* tree = (int*) malloc(sizeof(int) * 2000000);
};

int main() {

//    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    auto* tree = new SegmentTree();
    tree->build(a, 0, n, 0);

    string op;
    while (cin >> op) {
        if (op == "min") {
            int l, r;
            cin >> l >> r;
            cout << tree->get_min(0, n, 0, l - 1, r) << '\n';
        } else {
            int i, x;
            cin >> i >> x;
            tree->update(0, n, 0, i - 1, x);
        }
    }
}
