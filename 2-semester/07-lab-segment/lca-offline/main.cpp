#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

const int MAXLOG = 20;
void hanging(vector<vector<int>> &ancestor, vector<int> &h, int a, int b) {
    ancestor[b] = vector<int> (MAXLOG);
    ancestor[b][0] = a;
    h[b] = h[a] + 1;
    for (int i = 1; i != MAXLOG; ++i) {
        ancestor[b][i] = ancestor[ancestor[b][i - 1]][i - 1];
    }
}

int lca(vector<vector<int>> &ancestor, vector<int> &h, int a, int b) {
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

int main() {

    const int MAXN = 500'000 + 47;
    vector<vector<int>> ancestor(MAXN, vector<int> (MAXLOG));
    vector<int> h(MAXN);

    fill(ancestor[0].begin(), ancestor[0].end(), 0);
    h[0] = 0;

    int k;
    cin >> k;

    for (int i = 0; i != k; ++i) {
        string type;
        int a, b;
        cin >> type >> a >> b;
        --a, --b;

        if (type == "ADD") {
            hanging(ancestor, h, a, b);
        } else {
            cout << lca(ancestor, h, a, b) + 1 << '\n';
        }
    }
}
