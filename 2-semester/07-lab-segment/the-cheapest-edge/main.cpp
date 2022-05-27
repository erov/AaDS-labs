#include <climits>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

const int MAXLOG = 20;
const int MAXN = 200'000 + 47;
int ancestor[MAXN][MAXLOG];
int path_cost[MAXN][MAXLOG];
int h[MAXN];

void hanging(int a, int b, int cost) {
    ancestor[b][0] = a;
    path_cost[b][0] = cost;
    h[b] = h[a] + 1;
    fill(path_cost[b] + 1, path_cost[b] + MAXLOG, INT_MAX);
    for (int i = 1; i != MAXLOG; ++i) {
        ancestor[b][i] = ancestor[ancestor[b][i - 1]][i - 1];
        path_cost[b][i] = min(path_cost[b][i - 1], path_cost[ancestor[b][i - 1]][i - 1]);
    }
}

int get_min_cost(int a, int b) {
    if (h[a] > h[b]) {
        swap(a, b);
    }

    int min_cost = INT_MAX;
    int diff = h[b] - h[a];
    for (int i = MAXLOG - 1; i != -1; --i) {
        if (diff & (1 << i)) {
            min_cost = min(min_cost, path_cost[b][i]);
            b = ancestor[b][i];
        }
    }

    if (a == b) {
        return min_cost;
    }

    for (int i = MAXLOG - 1; i != -1; --i) {
        if (ancestor[a][i] != ancestor[b][i]) {
            min_cost = min(min_cost, min(path_cost[a][i], path_cost[b][i]));
            a = ancestor[a][i];
            b = ancestor[b][i];
        }
    }
    return min(min_cost, min(path_cost[a][0], path_cost[b][0]));
}

int main() {

    int n;
    cin >> n;

    for (int i = 1; i != n; ++i) {
        int p, cost;
        cin >> p >> cost;
        --p;
        hanging(p, i, cost);
    }

    int m;
    cin >> m;

    while (m--) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        cout << get_min_cost(u, v) << '\n';
    }
}
