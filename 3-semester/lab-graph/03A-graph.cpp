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


void dfs(vector<vector<size_t>>& g, vector<bool>& used, vector<size_t>& tin, vector<size_t>& up,
    size_t& timer, set<pair<size_t, size_t>>& bridges, size_t v, size_t p) {

    used[v] = true;
    tin[v] = up[v] = timer++;

    for (size_t to : g[v]) {
        if (to == p) {
            continue;
        }

        if (used[to]) {
            up[v] = min(up[v], tin[to]);
        } else {
            dfs(g, used, tin, up, timer, bridges, to, v);
            up[v] = min(up[v], up[to]);
            if (up[to] > tin[v]) {
                bridges.insert({v, to});
                bridges.insert({to, v});
            }
        }
    }
}

void calculate_ans(vector<vector<size_t>>& g, vector<bool>& used, set<pair<size_t, size_t>>& bridges, 
    vector<size_t>& bridges_sum, uint64_t& ans, size_t bridges_row, size_t v) {

    used[v] = true;

    for (size_t to : g[v]) {
        if (!used[to]) {
            size_t step_bridges_row;
            if (bridges.count({v, to})) {
                ans += bridges_row;
                step_bridges_row = bridges_row + 1;
            } else {
                step_bridges_row = 0;
            }
            calculate_ans(g, used, bridges, bridges_sum, ans, step_bridges_row, to);
            if (step_bridges_row > 0) {
                bridges_row = step_bridges_row + bridges_sum[to];
            }
        }
    }
}

void calculate_bridges_sum(vector<vector<size_t>>& g, vector<bool>& used, set<pair<size_t, size_t>>& bridges,
    vector<size_t>& bridges_sum, size_t v) {

    used[v] = true;
    for (size_t to : g[v]) {
        if (!used[to]) {
            calculate_bridges_sum(g, used, bridges, bridges_sum, to);
            if (bridges.count({v, to})) {
                bridges_sum[v] += bridges_sum[to] + 1;
            }
        }
    }
}


void solve() {
    size_t n, m;
    cin >> n >> m;

    set<pair<size_t, size_t>> edges;
    vector<vector<size_t>> g(n);
    for (size_t i = 0; i != m; ++i) {
        size_t u, v;
        cin >> u >> v;
        --u, --v;
        if (!edges.count({u, v})) {
            g[u].push_back(v);
            g[v].push_back(u);
            edges.insert({u, v});
            edges.insert({v, u});
        }
    }

    uint64_t ans = 0;
    vector<bool> used(n, false);
    vector<size_t> tin(n);
    vector<size_t> up(n);
    size_t timer = 0;
    
    set<pair<size_t, size_t>> bridges;
    for (size_t v = 0; v != n; ++v) {
        if (!used[v]) {
            dfs(g, used, tin, up, timer, bridges, v, n);
        }
    }

    used.assign(n, 0);
    vector<size_t> bridges_sum(n, 0);
    for (size_t v = 0; v != n; ++v) {
        if (!used[v]) {
            calculate_bridges_sum(g, used, bridges, bridges_sum, v);
        }
    }

    used.assign(n, 0);
    for (size_t v = 0; v != n; ++v) {
        if (!used[v]) {
            calculate_ans(g, used, bridges, bridges_sum, ans, 0, v);
        }
    }

    cout << ans;
}
