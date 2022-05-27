#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

const int MAXN = 100000 + 47;

struct SegmentTree {

    void build(vector<int> &a, int tl, int tr, int v) {
        if (tr - tl == 1) {
            tree[v] = {a[tl], tl};
            return;
        }
        int tm = (tl + tr) / 2;
        build(a, tl, tm, v * 2 + 1);
        build(a, tm, tr, v * 2 + 2);
        tree[v] = max(tree[v * 2 + 1], tree[v * 2 + 2]);
    }

    void push(int tl, int tr, int v) {
        if (to_add[v]) {
            if (tr - tl == 1) {
                tree[v].first += to_add[v];
                to_add[v] = 0;
                return;
            }
            tree[v].first += to_add[v];
            to_add[v * 2 + 1] += to_add[v];
            to_add[v * 2 + 2] += to_add[v];
            to_add[v] = 0;
        }
    }

    void update(int tl, int tr, int v, int l, int r, int value) {
        if (tr <= l || tl >= r) {
            return;
        }

        push(tl, tr, v);
        if (l <= tl && tr <= r) {
            to_add[v] += value;
            return;
        }
        int tm = (tl + tr) / 2;
        update(tl, tm, v * 2 + 1, l, r, value);
        update(tm, tr, v * 2 + 2, l, r, value);

        pair<int, int> left = {tree[v * 2 + 1].first + to_add[v * 2 + 1], tree[v * 2 + 1].second};
        pair<int, int> right = {tree[v * 2 + 2].first + to_add[v * 2 + 2], tree[v * 2 + 2].second};
        tree[v] = max(left, right);
    }

    pair<int, int> get_max(int tl, int tr, int v, int l, int r) {
        if (tr <= l || tl >= r) {
            return {INT_MIN, -1};
        }

        push(tl, tr, v);
        if (l <= tl && tr <= r) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        auto left = get_max(tl, tm, v * 2 + 1, l, r);
        auto right = get_max(tm, tr, v * 2 + 2, l, r);
        return max(left, right);
    }

    void show(int tl, int tr, int v) {
        cout << "[" << tl << ", " << tr << "]: " << tree[v].first << " - " << tree[v].second;
        cout << ", to_add: " << to_add[v] << '\n';

        if (tr - tl == 1) {
            return;
        }
        int tm = (tl + tr) / 2;
        show(tl, tm, v * 2 + 1);
        show(tm, tr, v * 2 + 2);
    }

private:
    pair<int, int>* tree = (pair<int, int>*) malloc(sizeof(pair<int, int>) * MAXN * 4);
    int* to_add = (int*) calloc(MAXN * 4, sizeof(int));
};

struct events {
    int x, y1, y2, type;
    events(int _x, int _y1, int _y2, int _type) : x(_x), y1(_y1), y2(_y2), type(_type) {}

    bool operator< (events& other) const {
        return x < other.x || (x == other.x && type < other.type);
    }
};

struct rectangle {
    int x1, y1, x2, y2;
};

void fill_compress_map(unordered_map<int, int> &result, set<int> &source) {
    int cnt = 0;
    for (auto it : source) {
        result[it] = cnt++;
    }
}

int recover_coordinate(unordered_map<int, int> &source, int coord) {
    for (auto it : source) {
        if (it.second == coord) {
            return it.first;
        }
    }
    assert(false);
    return 47;
}

int main() {
    
    int n;
    cin >> n;

    vector<rectangle> a(n);
    set<int> to_compress_x, to_compress_y;
    for (int i = 0; i < n; i++) {
        cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;
        to_compress_x.insert(a[i].x1);
        to_compress_x.insert(a[i].x2);
        to_compress_y.insert(a[i].y1);
        to_compress_y.insert(a[i].y2);
    }

    unordered_map<int, int> get_compress_x, get_compress_y;
    fill_compress_map(get_compress_x, to_compress_x);
    fill_compress_map(get_compress_y, to_compress_y);

    vector<events> scanline;
    for (auto rect : a) {
        scanline.emplace_back(get_compress_x[rect.x1], get_compress_y[rect.y1], get_compress_y[rect.y2], 0);
        scanline.emplace_back(get_compress_x[rect.x2], get_compress_y[rect.y1], get_compress_y[rect.y2], 1);
    }

    int sz = (int) to_compress_y.size();
    auto* tree = new SegmentTree();
    vector<int> temporary(sz, 0);
    tree->build(temporary, 0, sz, 0);

    sort(scanline.begin(), scanline.end());
    int max_cover = -1;
    pair<int, int> answer_point = {47, 47};
    for (auto [x, y1, y2, type] : scanline) {
        if (type == 0) {
            tree->update(0, sz, 0, y1, y2 + 1, 1);
        } else {
            auto current_max = tree->get_max(0, sz, 0, 0, sz);
            if (current_max.first > max_cover) {
                max_cover = current_max.first;
                answer_point = {x, current_max.second};
            }
            tree->update(0, sz, 0, y1, y2 + 1, -1);
        }
    }

    cout << max_cover << '\n' << recover_coordinate(get_compress_x, answer_point.first)
         << ' ' << recover_coordinate(get_compress_y, answer_point.second);
}
