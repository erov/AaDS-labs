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
    size_t test;
    cin >> test;

    constexpr size_t MAX_N = 200;
    for (size_t iter = 0; iter != test; ++iter) {
        size_t n, m;
        cin >> n >> m;

        struct pair_hasher {
            inline size_t operator()(const pair<size_t, size_t>& value) const {
                return value.first * MAX_N + value.second;
            }
        };
        unordered_set<pair<size_t, size_t>, pair_hasher> friends;

        for (size_t v = 0; v != n; ++v) {
            for (;;) {
                size_t to;
                cin >> to;
                if (to == 0) {
                    break;
                }
                friends.insert({v, --to});
            }
        }

        vector<vector<size_t>> non_friends(n);
        for (size_t v = 0; v != n; ++v) {
            for (size_t to = 0; to != m; ++to) {
                if (!friends.count({v, to})) {
                    non_friends[v].push_back(to);
                }
            }
        }

        vector<size_t> used(n, 0);
        size_t used_marker = 0;
        constexpr size_t non_matched = numeric_limits<size_t>::max();
        vector<size_t> matching(m, non_matched);

        for (size_t v = 0; v != n; ++v) {
            ++used_marker;
            dfs_kuhn(non_friends, used, matching, non_matched, used_marker, v);
        }

        vector<bool> in_l_minus(n, true);
        for (size_t to = 0; to != m; ++to) {
            if (matching[to] != non_matched) {
                in_l_minus[matching[to]] = false;
            }
        }

        vector<bool> filtered_r(m, false);

        auto remove_l_minus_to_r = [&](auto& self, size_t v) -> void {
            if (v == non_matched) {
                return;
            }

            used[v] = used_marker;

            for (size_t to : non_friends[v]) {
                if (!filtered_r[to]) {
                    filtered_r[to] = true;
                    self(self, matching[to]);
                }
            }
        };

        ++used_marker;
        for (size_t v = 0; v != n; ++v) {
            if (in_l_minus[v] && used[v] != used_marker) {
                remove_l_minus_to_r(remove_l_minus_to_r, v);
            }
        }

        size_t male = 0, female = 0;
        for (size_t v = 0; v != n; ++v) {
            male += (used[v] == used_marker ? 1 : 0);
        }
        for (size_t to = 0; to != m; ++to) {
            female += (!filtered_r[to] ? 1 : 0);
        }

        cout << male + female << '\n' << male << ' ' << female << '\n';
        for (size_t v = 0; v != n; ++v) {
            if (used[v] == used_marker) {
                cout << v + 1 << ' ';
            }
        }
        cout << '\n';
        for (size_t to = 0; to != m; ++to) {
            if (!filtered_r[to]) {
                cout << to + 1 << ' ';
            }
        }
        cout << '\n' << '\n';
    }
}

