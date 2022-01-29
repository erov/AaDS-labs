#include <iostream>
#include <climits>
#include <cstddef>
#include <cmath>
#include <vector>
#include <iomanip>
#include <cassert>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

void solve();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    #ifdef HOME
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        clock_t start_clock = clock();
    // #else
    //  freopen(".in", "r", stdin);
    //  freopen(".out", "w", stdout);
    #endif
    
    solve();

    #ifdef HOME
        // system("pause");
        printf("\n\nfinished in %.3f sec", static_cast<float>(clock() - start_clock) / CLOCKS_PER_SEC);
    #endif
}


void dfs(vector<vector<size_t>>& g, vector<bool>& used, vector<size_t>& order, size_t v) {
    used[v] = true;
    for (size_t to : g[v]) {
        if (!used[to]) {
            dfs(g, used, order, to);
        }
    }
    order.push_back(v);
}


void solve() {
    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> g(n);
    vector<vector<size_t>> rg(n);
    for (size_t i = 0; i != m; ++i) {
        size_t u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        rg[v].push_back(u);
    }

    vector<size_t> order;
    vector<bool> used(n);

    for (size_t v = 0; v != n; ++v) {
        if (!used[v]) {
            dfs(g, used, order, v);
        }
    }

    reverse(order.begin(), order.end());
    used.assign(n, false);
    vector<size_t> color(n, 0);
    vector<size_t> ambassador;
    size_t current_color = 0;

    for (size_t v : order) {
        if (!used[v]) {
            vector<size_t> component;
            dfs(rg, used, component, v);
            for (size_t u : component) {
                color[u] = current_color;
            }
            ambassador.push_back(component[0]);
            ++current_color;
        }
    }

    vector<vector<size_t>> strong_g(current_color);
    set<pair<size_t, size_t>> strong_edges;
    for (size_t v = 0; v != n; ++v) {
        for (size_t to : g[v]) {
            if (color[v] != color[to] && !strong_edges.count({color[v], color[to]})) {
                strong_g[color[v]].push_back(color[to]);
                strong_edges.insert({color[v], color[to]});
            }
        }
    }

    vector<size_t> ans;
    for (size_t v = 0; v != strong_g.size(); ++v) {
        if (strong_g[v].empty()) {
            ans.push_back(ambassador[v]);
        }
    } //

    cout << ans.size() << '\n';
    for (size_t v : ans) {
        cout << ++v << ' ';
    }

}
