#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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
    size_t n, m, s, t;
    cin >> n >> m >> s >> t;
    --s, --t;

    struct edge_t {
        size_t to;
        uint64_t a, b, d;
    };

    vector<vector<edge_t>> g(n);
    for (size_t i = 0; i != m; ++i) {
        size_t u, v;
        uint64_t a, b, d;
        cin >> u >> v >> a >> b >> d;
        --u, --v;
        g[u].push_back({v, a, b, d});
        g[v].push_back({u, a, b, d});
    }

    constexpr uint64_t INF = numeric_limits<uint64_t>::max();
    vector<uint64_t> dist(n, INF);
    set<pair<uint64_t, size_t>> q;

    dist[s] = 0;
    q.insert({0, s});

    while (!q.empty()) {
        size_t v = q.begin()->second;
        q.erase(q.begin());

        for (auto [to, a, b, d] : g[v]) {
            uint64_t k = dist[v] / (a + b);
            uint64_t upper = (a + b) * k + a;
            uint64_t lower = (a + b) * k;
            // cout << v << ' ' << to << ' ' << lower << ' ' << upper << '\n';
            if (upper - lower < d) {
                continue;
            }
            uint64_t arrival = dist[v] + d;
            if (lower <= dist[v] && dist[v] + d <= upper && dist[to] > arrival) {
                q.erase({dist[to], to});
                dist[to] = arrival;
                q.insert({dist[to], to});
            } else {
                arrival = lower + a + b + d;
                if (dist[to] > arrival) {
                    q.erase({dist[to], to});
                    dist[to] = arrival;
                    q.insert({dist[to], to});
                }
            }
        }
    }

    if (dist[t] == INF) {
        cout << -1;
    } else {
        cout << dist[t];
    }
}
