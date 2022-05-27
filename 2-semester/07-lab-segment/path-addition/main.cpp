#include <climits>
#include <iostream>
#include <vector>

using namespace std;

struct FenwickTree {

    explicit FenwickTree(size_t sz) : tree(vector<long long> (sz, 0LL)) {};

    void add(int pos, int value) {
        for (; pos < (int) tree.size(); pos = (pos | (pos + 1))) {
            tree[pos] += value;
        }
    }

    long long get(int pos) {
        long long result = 0;
        for (; pos >= 0; pos = (pos & (pos + 1)) - 1) {
            result += tree[pos];
        }
        return result;
    }

    void show() {
        cout << "tree:\n";
        for (int i = 0; i != (int) tree.size(); ++i) {
            cout << get(i) << ' ';
        }
        cout << "\n\n";
    }

private:
    vector<long long> tree;
};

const int MAXLOG = 20;
const int MAXN = 300'000 + 47;
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

void dfs(vector<vector<int>> &g, vector<int> &order, int v, int p = -1) {
    if (p != -1) {
        hanging(p, v);
    }
    order.push_back(v);
    for (int u : g[v]) {
        if (u != p) {
            dfs(g, order, u, v);
        }
    }
    order.push_back(v);
}

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    vector<vector<int>> g(n);
    for (int i = 0; i != n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> order;
    dfs(g, order, 0);

    const int NONE = INT_MIN;
    vector<pair<int, int>> pos(n, {NONE, NONE});
    for (int i = 0; i != (int) order.size(); ++i) {
        if (pos[order[i]].first == NONE) {
            pos[order[i]].first = i;
        } else {
            pos[order[i]].second = i;
        }
    }

    for (int i : order) {
        cout << i << ' ';
    }
    cout << '\n';

    auto* t = new FenwickTree(2 * n);

    int m;
    cin >> m;

    while (m--) {
        char type;
        cin >> type;

        if (type == '+') {
            int v, u, d;
            cin >> v >> u >> d;
            --u, --v;
            int anc = lca(u, v);
            t->add(pos[anc].second, -d);
            t->add(pos[u].first, d);
            t->add(pos[anc].second, -d);
            t->add(pos[v].first, d);
        } else {
            int v;
            cin >> v;
            --v;
            cout << '+' << pos[v].first << ' ' << pos[v].second << '\n';
            cout << t->get(pos[v].second) << ' ' <<  t->get(pos[v].first) << '\n';
            cout << t->get(pos[v].second) - t->get(pos[v].first) << '\n';
        }
        t->show();
    }
}
