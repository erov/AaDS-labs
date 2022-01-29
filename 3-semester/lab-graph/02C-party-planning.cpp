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

    vector<string> name(n);
    unordered_map<string, size_t> id_by_name;
    for (size_t i = 0; i != n; ++i) {
        cin >> name[i];
        id_by_name[name[i]] = i * 2;
    }

    vector<vector<size_t>> g(n * 2);
    vector<vector<size_t>> rg(g.size());
    for (size_t i = 0; i != m; ++i) {
        string lhs, rhs;
        cin >> lhs >> rhs >> rhs;
        size_t u = id_by_name[lhs.substr(1)] ^ (lhs[0] == '-' ? 1 : 0);
        size_t v = id_by_name[rhs.substr(1)] ^ (rhs[0] == '-' ? 1 : 0);
        g[u].push_back(v);
        g[v ^ 1].push_back(u ^ 1);
    }

    for (size_t v = 0; v != g.size(); ++v) {
        for (size_t to : g[v]) {
            rg[to].push_back(v);
        }
    }

    vector<size_t> order;
    vector<bool> used(g.size());

    for (size_t v = 0; v != g.size(); ++v) {
        if (!used[v]) {
            dfs(g, used, order, v);
        }
    }

    reverse(order.begin(), order.end());
    used.assign(used.size(), false);
    vector<size_t> color(g.size(), 0);
    size_t current_color = 0;

    for (size_t v : order) {
        if (!used[v]) {
            vector<size_t> component;
            dfs(rg, used, component, v);
            for (size_t u : component) {
                color[u] = current_color;
            }
            ++current_color;
        }
    }

    for (size_t v = 0; v != g.size(); ++v) {
        if (color[v] == color[v ^ 1]) {
            cout << -1;
            return;
        }
    }

    vector<string> ans;
    for (size_t i = 0; i != n; ++i) {
        size_t j = i * 2;
        if (color[j] > color[j ^ 1]) {
            ans.push_back(name[i]);
        }
    }

    cout << ans.size() << '\n';
    for (string& name : ans) {
        cout << name << '\n';
    }
}
