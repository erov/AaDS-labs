#include <climits>
#include <iostream>
#include <vector>

using namespace std;

struct Matrix {
    int m[2][2];
};

Matrix matrix_mul(Matrix a, Matrix b, const int MOD) {
    Matrix ans{};
    ans.m[0][0] = ans.m[0][1] = ans.m[1][0] = ans.m[1][1] = 0;
    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                ans.m[i][j] += a.m[i][k] * b.m[k][j];
                ans.m[i][j] %= MOD;
            }
        }
    }
    return ans;
}

struct SegmentTree {

    void build(vector<Matrix> &a, const int MOD, int tl, int tr, int v) {
        if (tr - tl == 1) {
            tree[v] = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(a, MOD, tl, tm, v * 2 + 1);
        build(a, MOD, tm, tr, v * 2 + 2);
        tree[v] = matrix_mul(tree[v * 2 + 1], tree[v * 2 + 2], MOD);
    }

    Matrix get_matrix_mul(int tl, int tr, int v, int l, int r, const int MOD) {
        if (tr <= l || tl >= r) {
            Matrix ans{};
            ans.m[0][0] = ans.m[1][1] = 1;
            ans.m[0][1] = ans.m[1][0] = 0;
            return ans;
        }
        if (l <= tl && tr <= r) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        return matrix_mul(get_matrix_mul(tl, tm, v * 2 + 1, l, r, MOD), get_matrix_mul(tm, tr, v * 2 + 2, l, r, MOD), MOD);
    }

private:
    Matrix* tree = (Matrix*) malloc(sizeof(Matrix) * 800000);
};

int main() {

    int MOD, n, m;
    cin >> MOD >> n >> m;

    vector<Matrix> a(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                cin >> a[i].m[j][k];
            }
        }
    }

    auto* tree = new SegmentTree();
    tree->build(a, MOD, 0, n, 0);

    while (m--) {
        int l, r;
        cin >> l >> r;

        Matrix ans = tree->get_matrix_mul(0, n, 0, l - 1, r, MOD);
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                cout << ans.m[i][j] << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
    }
}
