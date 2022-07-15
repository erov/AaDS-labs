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


bool dfs_kuhn(vector<vector<size_t>>& g, vector<size_t>& used, vector<size_t>& matching, const size_t non_matched, const size_t used_marker, size_t v) {
    if (used[v] == used_marker) {
        return false;
    }
    used[v] = used_marker;

    for (size_t to : g[v]) {
        if (matching[to] == non_matched || dfs_kuhn(g, used, matching, non_matched, used_marker, matching[to])) {
            matching[to] = v;
            return true;
        }
    }
    return false;
}


void solve() {
    size_t n;
    cin >> n;

    struct task_t {
        task_t() {}

        task_t(size_t start, size_t a, size_t b, size_t c, size_t d)
            : start(start), from({a, b}), to({c, d})
        {}

        size_t start;
        pair<size_t, size_t> from;
        pair<size_t, size_t> to;
    };


    auto diff = [](size_t lhs, size_t rhs) -> size_t {
        return max(lhs, rhs) - min(lhs, rhs);
    };

    auto duration = [&](pair<size_t, size_t>& from, pair<size_t, size_t>& to) -> size_t {
        return diff(from.first, to.first) + diff(from.second, to.second);
    };


    vector<task_t> task(n);
    for (size_t i = 0; i != n; ++i) {
        size_t hh, mm;
        char garbage;
        size_t a, b, c, d;
        cin >> hh >> garbage >> mm >> a >> b >> c >> d;
        task[i] = {hh * 60 + mm, a, b, c, d};
    }

    vector<vector<size_t>> next_task(n);
    for (size_t v = 0; v != n; ++v) {
        for (size_t to = 0; to != n; ++to) {
            if (task[v].start + duration(task[v].from, task[v].to) + duration(task[v].to, task[to].from) < task[to].start) {
                next_task[v].push_back(to);
            }
        }
    }

    vector<size_t> used(n, 0);
    size_t used_marker = 0;
    constexpr size_t non_matched = numeric_limits<size_t>::max();
    vector<size_t> matching(n, non_matched);

    for (size_t v = 0; v != n; ++v) {
        ++used_marker;
        dfs_kuhn(next_task, used, matching, non_matched, used_marker, v);
    }

    size_t matching_size = 0;
    for (size_t to = 0; to != n; ++to) {
        matching_size += (matching[to] != non_matched ? 1 : 0);
    }

    cout << n - matching_size;
}

