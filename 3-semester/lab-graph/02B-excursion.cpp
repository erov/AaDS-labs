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
    size_t n, m, k;
    cin >> n >> m >> k;

    vector<pair<size_t, bool>> preference_list;
    vector<vector<pair<int32_t, size_t>>> preference(n);
    for (size_t i = 0; i != k; ++i) {
        size_t a;
        int32_t b;
        cin >> a >> b;
        preference[--a].push_back({b, i * 2});
        preference_list.push_back({abs(b) - 1, (b > 0)});
    }


    vector<vector<size_t>> g(k * 2 * 3 + m * 2);
    size_t prefix_id = k * 2;
    for (size_t i = 0; i != n; ++i) {
        for (size_t j = 0; j != preference[i].size(); ++j) {
            size_t to = (preference[i][j].first > 0 ? preference[i][j].second : (preference[i][j].second ^ 1));
            g[prefix_id].push_back(to);
            if (j != 0) {
                g[prefix_id].push_back(prefix_id - 2);
            }
            prefix_id += 2;
        }
    }
    size_t suffix_id = k * 2 * 2;
    for (size_t i = 0; i != n; ++i) {
        for (size_t j = 0; j != preference[i].size(); ++j) {
            size_t to = (preference[i][j].first > 0 ? preference[i][j].second : (preference[i][j].second ^ 1));
            g[suffix_id].push_back(to);
            if (j != preference[i].size() - 1) {
                g[suffix_id].push_back(suffix_id + 2);
            }
            suffix_id += 2;
        }
    }

    prefix_id = k * 2;
    suffix_id = k * 2 * 2;
    size_t const cities = k * 2 * 3;
    for (size_t i = 0; i != n; ++i) {
        for (size_t j = 0; j != preference[i].size(); ++j) {
            size_t satisfied = (preference[i][j].first > 0 ? preference[i][j].second : (preference[i][j].second ^ 1));
            if (j != 0) {
                g[satisfied ^ 1].push_back(prefix_id - 2);
            }
            if (j != preference[i].size() - 1) {
                g[satisfied ^ 1].push_back(suffix_id + 2);
            }
            prefix_id += 2;
            suffix_id += 2;
            size_t city_id = (abs(preference[i][j].first) - 1) * 2 + cities;
            if (preference[i][j].first > 0) {
                g[satisfied].push_back(city_id);
                g[city_id].push_back(satisfied);
                g[satisfied ^ 1].push_back(city_id ^ 1);
                g[city_id ^ 1].push_back(satisfied ^ 1);
            } else {
                g[satisfied].push_back(city_id ^ 1);
                g[city_id ^ 1].push_back(satisfied);
                g[satisfied ^ 1].push_back(city_id);
                g[city_id].push_back(satisfied ^ 1);
            }
        }
    }

    vector<vector<size_t>> rg(g.size());
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

    for (size_t i = 0; i != g.size(); ++i) {
        if (color[i] == color[i ^ 1]) {
            cout << -1;
            return;
        }
    }

    set<size_t> visit;
    for (size_t i = 0; i != k; ++i) {
        size_t j = i * 2;
        if (color[j] > color[j ^ 1]) {
            if (preference_list[i].second) {
                visit.insert(preference_list[i].first);
            }
        }
    }

    cout << visit.size() << '\n';
    for (size_t city : visit) {
        cout << ++city << ' ';
    }
}
