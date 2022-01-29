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

void solve() {
    size_t n, m;
    cin >> n >> m;

    struct edge {
        size_t u;
        size_t v;
        int64_t w;
    };

    vector<edge> g(m);
    for (size_t i = 0; i != m; ++i) {
        size_t u, v;
        int64_t w;
        cin >> u >> v >> w;
        --u, --v;
        g[i] = {u, v, w};
    }

    sort(g.begin(), g.end(), [](edge& a, edge& b) {
        return a.w < b.w;
    });

    vector<size_t> p(n);
    vector<size_t> r(n);

    auto get = [&](auto& self, size_t v) -> size_t {
        return (v == p[v] ? v : p[v] = self(self, p[v]));
    };

    auto unite = [&](size_t a, size_t b) -> bool {
        a = get(get, a);
        b = get(get, b);

        if (a == b) {
            return false;
        }

        if (r[a] < r[b]) {
            swap(a, b);
        }
        p[b] = a;
        if (r[a] == r[b]) {
            ++r[a];
        }

        return true;
    }; 

    constexpr int64_t INF = numeric_limits<int64_t>::max();
    int64_t ans = INF;
    
    for (size_t iter = 0; iter != m; ++iter) {
        for (size_t i = 0; i != n; ++i) {
            p[i] = i;
            r[i] = 0;
        }

        int64_t mx = numeric_limits<int64_t>::min();
        for (size_t j = iter; j != m; ++j) {
            if (unite(g[j].u, g[j].v)) {
                mx = max(mx, g[j].w);
            }
        }

        bool connected = true;
        for (size_t i = 0; i != n; ++i) {
            if (get(get, 0) != get(get, i)) {
                connected = false;
                break;
            }
        }

        if (connected) {
            ans = min(ans, mx - g[iter].w);
        }
    }

    if (ans == INF) {
        cout << "NO";
    } else {
        cout << "YES\n" << ans;
    }
}