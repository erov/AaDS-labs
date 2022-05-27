#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

const int MAXLOG = 20;
const int MAXN = 100'000 + 47;
int ancestor[MAXN][MAXLOG];
int h[MAXN];

void hanging(int a, int b) {
    ancestor[b][0] = a;
    h[b] = h[a] + 1;
    for (int i = 1; i != MAXLOG; ++i) {
        ancestor[b][i] = ancestor[ancestor[b][i - 1]][i - 1];
    }
}

int lca(int a, int b) {
    if (h[a] > h[b]) {
        swap(a, b);
    }

    int diff = h[b] - h[a];
    for (int i = MAXLOG - 1; i != -1; --i) {
        if (diff & (1 << i)) {
            b = ancestor[b][i];
        }
    }

    if (a == b) {
        return a;
    }

    for (int i = MAXLOG - 1; i != -1; --i) {
        if (ancestor[a][i] != ancestor[b][i]) {
            a = ancestor[a][i];
            b = ancestor[b][i];
        }
    }
    return ancestor[a][0];
}

void dfs(vector<vector<int>> &g, int v, int p = -1) {
    if (p != -1) {
        hanging(p, v);
    }
    for (int to : g[v]) {
        dfs(g, to, v);
    }
}

int main() {

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(MAXN);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }

    dfs(g, 0);

    long long a1, a2, x, y, z;
    cin >> a1 >> a2 >> x >> y >> z;

    long long ans = 0;
    int v = 0;
    for (int i = 0; i != m; ++i) {
        v = lca((int) (a1 + v) % n, (int) a2);
        ans += v;
        long long a3 = (x * a1 + y * a2 + z) % n;
        long long a4 = (x * a2 + y * a3 + z) % n;
        a1 = a3;
        a2 = a4;
    }

    cout << ans;

}
