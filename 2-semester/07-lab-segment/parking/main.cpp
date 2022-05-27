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

    void show(int tl, int tr, int v) {
        cout << "[" << tl << ", " << tr << "]: " << tree[v] << '\n';
        if (tr - tl == 1) {
            return;
        }
        int tm = (tl + tr) / 2;
        show(tl, tm, v * 2 + 1);
        show(tm, tr, v * 2 + 2);
    }

private:
    int* tree = (int*) malloc(sizeof(int) * 2000000);
};

int main() {

    int n, m;
    cin >> n >> m;

    vector<int> a(n, INT_MIN);
    auto* tree = new SegmentTree();
    tree->build(a, 0, n, 0);

    for (int i = 0; i < m; i++) {
        string op;
        int pos;
        cin >> op >> pos;
        --pos;
        if (op == "exit") {
            tree->update(0, n, 0, pos, INT_MIN);
        } else {
            int l = -1, r = n;
            while (r - l > 1) {
                int mid = (l + r) / 2;
                int actual_pos = (pos + mid) % n;
                int result;

                if (pos <= actual_pos) {
                    result = tree->get_min(0, n, 0, pos, actual_pos + 1);
                } else {
                    result = min(tree->get_min(0, n, 0, pos, n), tree->get_min(0, n, 0, 0, actual_pos + 1));
                }
                if (result == INT_MIN) {
                    r = mid;
                } else {
                    l = mid;
                }
            }
            pos = (pos + r) % n;
            cout << pos + 1 << '\n';
            tree->update(0, n, 0, pos, 47);
        }
    }
}
