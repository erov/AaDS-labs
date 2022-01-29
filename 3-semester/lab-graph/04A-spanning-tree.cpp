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
    size_t n;
    cin >> n;

    vector<pair<int32_t, int32_t>> dot(n);
    for (size_t i = 0; i != n; ++i) {
        cin >> dot[i].first >> dot[i].second;
    }

    set<size_t> added;
    added.insert(0);

    auto dist = [&](size_t i, size_t j) -> uint64_t {
        int64_t x = dot[i].first - dot[j].first;
        int64_t y = dot[i].second - dot[j].second;
        return x * x + y * y;
    };

    constexpr int64_t INF = numeric_limits<int64_t>::max();
    vector<uint64_t> dist_to(n);
    dist_to[0] = 0;
    for (size_t i = 1; i != n; ++i) {
        dist_to[i] = dist(0, i);
    }

    double ans = 0;
    for (;;) {
        uint64_t min_cost = INF;
        size_t v;

        for (size_t i = 0; i != n; ++i) {
            if (dist_to[i] > 0 && dist_to[i] < min_cost) {
                min_cost = dist_to[i];
                v = i;
            }
        }

        if (min_cost == INF) {
            break;
        }

        ans += sqrt(min_cost);
        for (size_t i = 0; i != n; ++i) {
            if (dist_to[i] != 0) {
                dist_to[i] = min(dist_to[i], dist(i, v));
            }
        }
    }

    cout << fixed << setprecision(20) << ans;
}