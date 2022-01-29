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
    size_t n, k;
    cin >> n >> k;

    vector<size_t> exit(k);
    for (size_t i = 0; i != k; ++i) {
        cin >> exit[i];
        --exit[i];
    }

    size_t m;
    cin >> m;

    vector<vector<size_t>> g(n);
    for (size_t i = 0; i != m; ++i) {
        size_t u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    constexpr size_t INF = numeric_limits<size_t>::max();
    vector<size_t> dist(n, INF);
    vector<size_t> shelter(n, INF);
    queue<size_t> q;

    for (size_t i : exit) {
        q.push(i);
        dist[i] = 0;
        shelter[i] = i;
    }

    while (!q.empty()) {
        size_t v = q.front();
        q.pop();

        for (size_t to : g[v]) {
            if (dist[to] == INF) {
                dist[to] = dist[v] + 1;
                shelter[to] = shelter[v];
                q.push(to);
            }
            if (dist[to] == dist[v] + 1) {
                shelter[to] = min(shelter[to], shelter[v]);
            }
        }
    }

    for (size_t d : dist) {
        cout << d << ' ';
    }
    cout << '\n';
    for (size_t id : shelter) {
        cout << ++id << ' ';
    }
}
