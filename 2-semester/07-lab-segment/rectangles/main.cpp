#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 128;
const int MAXL = 8;
int X1[MAXN][MAXN][MAXL][MAXL];
int Y1[MAXN][MAXN][MAXL][MAXL];
int X2[MAXN][MAXN][MAXL][MAXL];
int Y2[MAXN][MAXN][MAXL][MAXL];

void init_table(int table_num, int n, int m, int mode) {
    int (&table)[MAXN][MAXN][MAXL][MAXL] = (table_num == 0 ? X1 : (table_num == 1 ? Y1 : (table_num == 2 ? X2 : Y2)));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 1; k < MAXL; k++) {
                table[i][j][0][k] = table[i][j][0][k - 1];
                int pos = j - (1 << (k - 1));
                if (pos >= 0) {
                    int tmp = table[i][pos][0][k - 1];
                    table[i][j][0][k] = (mode == 0 ? min(table[i][j][0][k], tmp) : max(table[i][j][0][k], tmp));
                }
            }
        }
    }
    for (int k1 = 1; k1 < MAXL; k1++) {
        for (int i = 0; i < n; i++) {
            for (int k2 = 0; k2 < MAXL; k2++) {
                for (int j = 0; j < m; j++) {
                    table[i][j][k1][k2] = table[i][j][k1 - 1][k2];
                    int pos = i - (1 << (k1 - 1));
                    if (pos >= 0) {
                        int tmp = table[pos][j][k1 - 1][k2];
                        table[i][j][k1][k2] = (mode == 0 ? min(table[i][j][k1][k2], tmp) : max(table[i][j][k1][k2], tmp));
                    }
                }
            }
        }
    }
}

int get_value(int table_num, int r1, int c1, int r2, int c2, int mode) {
    int (&table)[MAXN][MAXN][MAXL][MAXL] = (table_num == 0 ? X1 : (table_num == 1 ? Y1 : (table_num == 2 ? X2 : Y2)));
    int k1 = (int) log2(r2 - r1 + 1);
    int k2 = (int) log2(c2 - c1 + 1);
    int rect[4] = {table[r1 + (1 << k1) - 1][c1 + (1 << k2) - 1][k1][k2], table[r1 + (1 << k1) - 1][c2][k1][k2],
                   table[r2][c1 + (1 << k2) - 1][k1][k2], table[r2][c2][k1][k2]};
    return (mode == 0 ?
            min(min(rect[0], rect[1]), min(rect[2], rect[3])) :
            max(max(rect[0], rect[1]), max(rect[2], rect[3])));
}

const long long MOD = (long long) 1e9 + 7;
int next_query(long long a, long long b, long long v0) {
    return (int) ((a * v0 + b) % MOD);
}

int main() {

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int _x1, _y1, _x2, _y2;
            cin >> _x1 >> _y1 >> _x2 >> _y2;
            if (_x1 > _x2) {
                swap(_x1, _x2);
            }
            if (_y1 > _y2) {
                swap(_y1, _y2);
            }

            X1[i][j][0][0] = _x1;
            X2[i][j][0][0] = _x2;
            Y1[i][j][0][0] = _y1;
            Y2[i][j][0][0] = _y2;
        }
    }

    init_table(0, n, m, 1);
    init_table(1, n, m, 1);
    init_table(2, n, m, 0);
    init_table(3, n, m, 0);

    int q;
    cin >> q;

    long long a, b, v0;
    cin >> a >> b >> v0;

    long long ans = 0;
    for (int k = 1; k <= q; k++) {
        long long r1, c1, r2, c2;
        r1 = v0 = next_query(a, b, v0);
        c1 = v0 = next_query(a, b, v0);
        r2 = v0 = next_query(a, b, v0);
        c2 = v0 = next_query(a, b, v0);
        r1 %= n, r2 %= n;
        c1 %= m, c2 %= m;

        if (r1 > r2) {
            swap(r1, r2);
        }
        if (c1 > c2) {
            swap(c1, c2);
        }

        int _x1 = get_value(0, (int) r1, (int) c1, (int) r2, (int) c2, 1);
        int _y1 = get_value(1, (int) r1, (int) c1, (int) r2, (int) c2, 1);
        int _x2 = get_value(2, (int) r1, (int) c1, (int) r2, (int) c2, 0);
        int _y2 = get_value(3, (int) r1, (int) c1, (int) r2, (int) c2, 0);

        long long current = (long long) (max(_x2 - _x1, 0)) * (long long) (max(_y2 - _y1, 0));
        ans = (ans + current) % MOD;
    }

    cout << ans;
}
