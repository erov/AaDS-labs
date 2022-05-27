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

#include <fstream>

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

bool topsort(vector<vector<size_t>>& g, vector<uint32_t>& used, vector<size_t>& order, size_t v) {
    used[v] = 1;
    bool is_cycle = false;
    for (size_t to : g[v]) {
        if (used[to] == 1) {
            return true;
        }
        if (used[to] == 0) {
            is_cycle |= topsort(g, used, order, to);
        }
    }
    used[v] = 2;
    order.push_back(v);
    return is_cycle;
}

void solve() {
    size_t n, na, nb;
    cin >> n >> na >> nb;

    vector<vector<size_t>> g(n * 2);  // 2 * i, (2 * i)^1 - brick #i

    for (size_t i = 0; i != n * 2; i += 2) {
        g[i].push_back(i ^ 1);
    }

    for (size_t i = 0; i != na; ++i) {
        size_t u, v;
        cin >> u >> v;
        u = (u - 1) * 2;
        v = (v - 1) * 2;
        g[u ^ 1].push_back(v);
    }

    for (size_t i = 0; i != nb; ++i) {
        size_t u, v;
        cin >> u >> v;
        u = (u - 1) * 2;
        v = (v - 1) * 2;
        g[v].push_back(u ^ 1);
        g[u].push_back(v ^ 1);
    }

    vector<uint32_t> used(n * 2, 0);
    vector<size_t> order;

    for (size_t v = 0; v != n * 2; ++v) {
        if (used[v] == 0) {
            if (topsort(g, used, order, v)) {
                cout << "NO";
                return;
            }
        }
    }

    vector<pair<size_t, size_t>> ans(n);
    reverse(order.begin(), order.end());
    for (size_t i = 0; i != n * 2; ++i) {
        if (order[i] & 1) {
            ans[order[i] / 2].second = i;
        } else {
            ans[order[i] / 2].first = i;
        }
    }

    cout << "YES\n";
    for (auto& [l, r] : ans) {
        cout << l << ' ' << r << '\n';
    }

}
