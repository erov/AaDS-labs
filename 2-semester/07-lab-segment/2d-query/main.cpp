#include <algorithm>
#include <cassert>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;


const int MAXN = (1 << 17);
int tree[20][MAXN];

void build(vector<int> &a, int tl, int tr, int v, int h = 0) {
    if (tr - tl == 1) {
        tree[h][tl] = a[tl];
        return;
    }
    int tm = (tl + tr) / 2;
    build(a, tl, tm, v * 2 + 1, h + 1);
    build(a, tm, tr, v * 2 + 2, h + 1);
    int left = tl, right = tm;
    for (int i = tl; i != tr; ++i) {
        int value;
        if (left == tm) {
            value = tree[h + 1][right++];
        } else if (right == tr) {
            value = tree[h + 1][left++];
        } else if (tree[h + 1][left] < tree[h + 1][right]) {
            value = tree[h + 1][left++];
        } else {
            value = tree[h + 1][right++];
        }
        tree[h][i] = value;
    }
}

int get(int tl, int tr, int v, int l, int r, int x, int y, int h = 0) {
    if (tr <= l || tl >= r) {
        return 0;
    }
    if (l <= tl && tr <= r) {
        return upper_bound(tree[h] + tl, tree[h] + tr, y) -
               upper_bound(tree[h] + tl, tree[h] + tr, x - 1);
    }
    int tm = (tl + tr) / 2;
    return get(tl, tm, v * 2 + 1, l, r, x, y, h + 1) + get(tm, tr, v * 2 + 2, l, r, x, y, h + 1);
}

unsigned int a, b, cur;
unsigned int nextRand17() {
    cur = cur * a + b;
    return cur >> 15;
}

unsigned int nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    clock_t timer = clock();

    int q;
    cin >> q >> a >> b;

    vector<int> arr(MAXN);
    for (int i = 0; i != MAXN; ++i) {
        arr[i] = (int) nextRand24();
    }
    build(arr, 0, MAXN, 0);

    unsigned int ans = 0;
    while (q--) {
        int l = (int) nextRand17();
        int r = (int) nextRand17();
        if (l > r) {
            swap(l, r);
        }
        int x = (int) nextRand24();
        int y = (int) nextRand24();
        if (x > y) {
            swap(x, y);
        }
        int c = get(0, MAXN, 0, l, r + 1, x, y);
        b += c;
        ans += c;
    }

    cout << ans;

//    cout << "\nwork time: " << (float) (clock() - timer) / CLOCKS_PER_SEC << " s";
}
