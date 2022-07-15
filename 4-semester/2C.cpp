#include <algorithm>
#include <array>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
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
    #else
        // freopen(".in", "r", stdin);
        // freopen(".out", "w", stdout);
    #endif
    
    solve();

    #ifdef HOME
        printf("\n\nfinished in %.3f sec", static_cast<float>(clock() - start_clock) / CLOCKS_PER_SEC);
        // system("pause");
    #endif
}


namespace dinica {

struct edge_t {
    edge_t() {}

    edge_t(size_t from, size_t to, size_t id, int64_t capacity, int64_t flow)
        : from(from), to(to), id(id), capacity(capacity), flow(flow)
    {}

    size_t from, to;
    size_t id;
    int64_t capacity, flow;
};


void add_edge(vector<edge_t>& edge, vector<vector<size_t>>& g, size_t from, size_t to, size_t id, int64_t capacity, bool is_directed = true) {
    edge.push_back({from, to, id, capacity, 0});
    g[from].push_back(edge.size() - 1);
    edge.push_back({to, from, numeric_limits<size_t>::max(), (is_directed ? 0 : capacity), 0});
    g[to].push_back(edge.size() - 1);
}


bool build_network(vector<edge_t>& edge, vector<vector<size_t>>& g, vector<size_t>& dist, size_t from, size_t to) {
    constexpr size_t INF = numeric_limits<size_t>::max();
    fill(dist.begin(), dist.end(), INF);

    dist[from] = 0;
    queue<size_t> que;
    que.push(from);

    while (!que.empty() && dist[to] == INF) {
        size_t v = que.front();
        que.pop();

        for (size_t to_id : g[v]) {
            size_t nxt = edge[to_id].to;
            if (dist[nxt] == INF && edge[to_id].capacity != edge[to_id].flow) {
                dist[nxt] = dist[v] + 1;
                que.push(nxt);
            }
        }
    }

    return dist[to] != INF;
}


int64_t push_flow(vector<edge_t>& edge, vector<vector<size_t>>& g, vector<size_t>& dist, vector<size_t>& v_ptr, const size_t finish, size_t v, int64_t flow) {
    if (v == finish || flow == 0) {
        return flow;
    }

    for (; v_ptr[v] != g[v].size(); ++v_ptr[v]) {
        size_t to_id = g[v][v_ptr[v]];
        if (dist[edge[to_id].to] == dist[v] + 1) {
            int64_t pushed_flow = push_flow(edge, g, dist, v_ptr, finish, edge[to_id].to, min(flow, edge[to_id].capacity - edge[to_id].flow));
            if (pushed_flow != 0) {
                edge[to_id].flow += pushed_flow;
                edge[to_id ^ 1].flow -= pushed_flow;
                return pushed_flow;
            }
        }
    }

    return 0;
}


int64_t find_flow(vector<edge_t>& edge, vector<vector<size_t>>& g, size_t from, size_t to) {
    int64_t flow = 0;

    for (;;) {
        vector<size_t> dist(g.size());
        if (build_network(edge, g, dist, from, to) == false) {
            break;
        }

        vector<size_t> v_ptr(g.size(), 0);
        for (;;) {
            int64_t pushed_flow = push_flow(edge, g, dist, v_ptr, to, from, numeric_limits<int64_t>::max());
            flow += pushed_flow;
            if (pushed_flow == 0) {
                break;
            }
        }
    }
    return flow;
}


} // dinica


void solve() {
    size_t n, m;
    cin >> n >> m;

    const size_t shift = n * m;
    vector<dinica::edge_t> edge;
    vector<vector<size_t>> g(shift * 2);

    auto get_index = [&](size_t i, size_t j) -> size_t {
        return i * m + j;
    };

    size_t from, to;
    vector<string> field(n);
    for (size_t i = 0; i != n; ++i) {
        cin >> field[i];
    }

    set<pair<size_t, size_t>> added;

    auto add_edge = [&](size_t u, size_t v, int64_t capacity) -> void {
        dinica::add_edge(edge, g, u, v, 0, capacity, true);
    };

    constexpr int64_t INF = numeric_limits<int32_t>::max();

    for (size_t i = 0; i != n; ++i) {
        for (size_t j = 0; j != m; ++j) {
            if (field[i][j] == 'A') {
                from = get_index(i, j);
                add_edge(get_index(i, j), get_index(i, j) + shift, INF);
            }
            if (field[i][j] == 'B') {
                to = get_index(i, j) + shift;
                add_edge(get_index(i, j), get_index(i, j) + shift, INF);
            }
            if (field[i][j] == '#') {
                continue;
            }
            if (field[i][j] == '.') {
                add_edge(get_index(i, j), get_index(i, j) + shift, 1);
            }
            if (field[i][j] == '-') {
                add_edge(get_index(i, j), get_index(i, j) + shift, INF);
            }
            if (i != 0 && field[i - 1][j] != '#') {
                add_edge(get_index(i, j) + shift, get_index(i - 1, j), INF);
            }
            if (i != n - 1 && field[i + 1][j] != '#') {
                add_edge(get_index(i, j) + shift, get_index(i + 1, j), INF);
            }
            if (j != 0 && field[i][j - 1] != '#') {
                add_edge(get_index(i, j) + shift, get_index(i, j - 1), INF);
            }
            if (j != m - 1 && field[i][j + 1] != '#') {
                add_edge(get_index(i, j) + shift, get_index(i, j + 1), INF);
            }
        }
    }

    int64_t flow = dinica::find_flow(edge, g, from, to);

    if (flow > g.size()) {
        cout << -1;
        return;
    }

    vector<size_t> dist(g.size());
    dinica::build_network(edge, g, dist, from, to);
    
    vector<size_t> in_cut;
    for (auto& e : edge) {
        if (e.id < edge.size() / 2 && ((dist[e.from] < g.size()) ^ (dist[e.to] >= g.size())) == false && e.capacity == 1) {
            in_cut.push_back(e.from);
        }
    }

    for (size_t id : in_cut) {
        field[id / m][id % m] = '+';
    }

    cout << in_cut.size() << '\n';
    for (size_t i = 0; i != n; ++i) {
        cout << field[i] << '\n';
    }
}

