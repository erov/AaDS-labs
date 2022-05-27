#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int get_min(vector<vector<int>> &table, int l, int r) {
    int len = r - l + 1;
    int k = (int) log2(len);
    return min(table[k][r], table[k][l + (1 << k) - 1]);
}

int main() {
    int const MAXN = (int) 1e5 + 47;
    int const MAXL = 17;
    vector<vector<int>> table = vector<vector<int>> (MAXL, vector<int> (MAXN));

    int n, m;
    cin >> n >> m >> table[0][0];

    for (int i = 1; i < n; i++) {
        table[0][i] = (23 * table[0][i - 1] + 21563) % 16714589;
    }

    for (int j = 1; j < MAXL; j++) {
        for (int i = 0; i < n; i++) {
            table[j][i] = table[j - 1][i];
            int k = i - (1 << (j - 1));
            if (k >= 0) {
                table[j][i] = min(table[j][i], table[j - 1][k]);
            }
        }
    }


    int u, v;
    cin >> u >> v;

    int ans = 47;
    for (int i = 1; i <= m; i++) {
        ans = get_min(table, min(u, v) - 1, max(u, v) - 1);
        if (i != m) {
            u = ((17 * u + 751 + ans + 2 * i) % n) + 1;
            v = ((13 * v + 593 + ans + 5 * i) % n) + 1;
        }
    }

    cout << u << ' ' << v << ' ' << ans;
}
