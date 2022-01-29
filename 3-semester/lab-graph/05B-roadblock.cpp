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

constexpr uint64_t INF = numeric_limits<uint64_t>::max();

void dijkstra(vector<vector<pair<size_t, size_t>>>& g, vector<uint64_t>& edge_cost, vector<uint64_t>& dist) {
    set<pair<uint64_t, size_t>> q;
    dist.assign(dist.size(), INF);

    dist[0] = 0;
    q.insert({0LL, 0});

    while (!q.empty()) {
        size_t v = q.begin()->second;
        q.erase(q.begin());

        for (auto [to, id] : g[v]) {
            if (dist[to] > dist[v] + edge_cost[id]) {
                q.erase({dist[to], to});
                dist[to] = dist[v] + edge_cost[id];
                q.insert({dist[to], to});
            }
        }
    }
}

void pathes_recovery(vector<vector<pair<size_t, size_t>>>& g, vector<uint64_t>& edge_cost, vector<uint64_t>& dist, 
    vector<size_t>& ids) {

    vector<bool> used(g.size(), false);
    queue<size_t> q;

    q.push(g.size() - 1);
    used.back() = true;

    while (!q.empty()) {
        size_t v = q.front();
        q.pop();

        for (auto [from, id] : g[v]) {
            if (dist[from] + edge_cost[id] == dist[v]) {
                if (!used[from]) {
                    used[from] = true;
                    q.push(from);
                }
                ids.push_back(id);
            }
        }
    }
}

void solve() {
    size_t n, m;
    cin >> n >> m;

    vector<vector<pair<size_t, size_t>>> g(n);  // {vert, edge_id}
    vector<uint64_t> edge_cost(m);
    for (size_t i = 0; i != m; ++i) {
        size_t u, v;
        cin >> u >> v >> edge_cost[i];
        --u, --v;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }

    vector<uint64_t> dist(n);
    dijkstra(g, edge_cost, dist);

    uint64_t min_len = dist.back();
    vector<size_t> ids;

    pathes_recovery(g, edge_cost, dist, ids);

    uint64_t max_len = min_len;
    for (size_t i : ids) {
        edge_cost[i] *= 2;
        dijkstra(g, edge_cost, dist);
        max_len = max(max_len, dist.back());
        edge_cost[i] /= 2;
    }

    cout << max_len - min_len;
}
