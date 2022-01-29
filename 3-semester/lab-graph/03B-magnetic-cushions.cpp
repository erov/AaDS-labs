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
    set<size_t>& cutpoints, size_t& timer, size_t v, size_t p) {

    used[v] = true;
    tin[v] = up[v] = timer++;

    size_t kids = 0;
    for (size_t to : g[v]) {
        if (to == p) {
            continue;
        }

        if (used[to]) {
            up[v] = min(up[v], tin[to]);
        } else {
            dfs(g, used, tin, up, cutpoints, timer, to, v);
            up[v] = min(up[v], up[to]);
            if (up[to] >= tin[v] && p != g.size()) {
                cutpoints.insert(v);
            }
            ++kids;
        }
    }

    if (p == g.size() && kids > 1) {
        cutpoints.insert(v);
    }
}


void solve() {
    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> g(n + m);
    size_t fictive = n;
    for (size_t i = 0; i != m; ++i) {
        size_t u, v, z;
        cin >> u >> v >> z;
        --u, --v, --z;
        g[fictive].push_back(u);
        g[fictive].push_back(v);
        g[fictive].push_back(z);
        g[u].push_back(fictive);
        g[v].push_back(fictive);
        g[z].push_back(fictive);
        ++fictive;
    }

    vector<bool> used(g.size());
    vector<size_t> tin(g.size());
    vector<size_t> up(g.size());
    set<size_t> cutpoints;
    size_t timer = 0;

    for (size_t v = n; v != g.size(); ++v) {
        if (!used[v]) {
            dfs(g, used, tin, up, cutpoints, timer, v, g.size());
        }
    }

    vector<size_t> ans;
    for (size_t v : cutpoints) {
        if (v >= n) {
            ans.push_back(v - n);
        }
    }

    cout << ans.size() << '\n';
    for (size_t id : ans) {
        cout << ++id << ' ';
    }
}
