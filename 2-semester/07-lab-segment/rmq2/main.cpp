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
        tree[v] = min(tree[v * 2 + 1], tree[v * 2 + 2]);
    }

    void push(int tl, int tr, int v) {
        if (tr - tl == 1) {
            if (to_set[v].second) {
                tree[v] = to_set[v].first;
            }
            if (to_add[v].second) {
                tree[v] += to_add[v].first;
            }
            to_add[v].second = to_set[v].second = false;
            return;
        }

        if (to_set[v].second) {
            tree[v] = to_set[v].first;
            to_add[v * 2 + 1].second = to_add[v * 2 + 2].second = false;
            to_set[v * 2 + 1] = to_set[v * 2 + 2] = to_set[v];
            to_set[v].second = false;
        }
        if (to_add[v].second) {
            tree[v] += to_add[v].first;
            if (to_set[v * 2 + 1].second) {
                to_set[v * 2 + 1].first += to_add[v].first;
            } else {
                if (to_add[v * 2 + 1].second) {
                    to_add[v * 2 + 1].first += to_add[v].first;
                } else {
                    to_add[v * 2 + 1] = to_add[v];
                }
            }
            if (to_set[v * 2 + 2].second) {
                to_set[v * 2 + 2].first += to_add[v].first;
            } else {
                if (to_add[v * 2 + 2].second) {
                    to_add[v * 2 + 2].first += to_add[v].first;
                } else {
                    to_add[v * 2 + 2] = to_add[v];
                }
            }
            to_add[v].second = false;
        }
    }

    void update(int tl, int tr, int v, int l, int r, long long value, bool add) {
        if (tr <= l || tl >= r) {
            return;
        }

        push(tl, tr, v);
        if (l <= tl && tr <= r) {
            if (add) {
                to_add[v] = {value, true};
            } else {
                to_set[v] = {value, true};
            }
            return;
        }
        int tm = (tl + tr) / 2;
        update(tl, tm, v * 2 + 1, l, r, value, add);
        update(tm, tr, v * 2 + 2, l, r, value, add);
        tree[v] = min((to_set[v * 2 + 1].second ? to_set[v * 2 + 1].first :
            tree[v * 2 + 1] + (to_add[v * 2 + 1].second ? to_add[v * 2 + 1].first : 0)),
            (to_set[v * 2 + 2].second ? to_set[v * 2 + 2].first :
            tree[v * 2 + 2] + (to_add[v * 2 + 2].second ? to_add[v * 2 + 2].first : 0)));
    }

    long long get_min(int tl, int tr, int v, int l, int r) {
        if (tr <= l || tl >= r) {
            return LLONG_MAX;
        }

        push(tl, tr, v);
        if (l <= tl && tr <= r) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        return min(get_min(tl, tm, v * 2 + 1, l, r), get_min(tm, tr, v * 2 + 2, l, r));
    }

    void dump(int tl, int tr, int v) {
        cout << "[" << tl << ", " << tr << "]: " << tree[v] << ", to_set: ";
        if (to_set[v].second) {
            cout << to_set[v].first;
        } else {
            cout << "no";
        }
        cout << ", to_add: ";
        if (to_add[v].second) {
            cout << to_add[v].first;
        } else {
            cout << "no";
        }
        cout << '\n';

        if (tr - tl == 1) {
            return;
        }
        int tm = (tl + tr) / 2;
        dump(tl, tm, v * 2 + 1);
        dump(tm, tr, v * 2 + 2);
    }

private:
    long long* tree = (long long*) malloc(sizeof(long long) * 100000 * 4);
    pair<long long, bool>* to_set = (pair<long long, bool>*) malloc(sizeof(pair<long long, bool>) * 100000 * 4);
    pair<long long, bool>* to_add = (pair<long long, bool>*) malloc(sizeof(pair<long long, bool>) * 100000 * 4);
};

int main() {

//    freopen("input.txt", "r", stdin);

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
        if (op == "min") {
            int l, r;
            cin >> l >> r;
            cout << tree->get_min(0, n, 0, l - 1, r) << '\n';
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            tree->update(0, n, 0, l - 1, r, x, (op == "add"));
//            tree->dump(0, n, 0);
//            cout << '\n';
        }
    }
}
