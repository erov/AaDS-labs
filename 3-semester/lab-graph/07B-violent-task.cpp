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
    size_t n;
    cin >> n;
 
    vector<uint32_t> g(n + 1, 0);
    for (size_t ppl = 2; ppl <= n; ++ppl) {
        set<uint32_t> already;
        already.insert(g[ppl - 1]);
        for (size_t i = 1; i <= ppl / 2; ++i) {
            already.insert(g[i] ^ g[ppl - i - 1]);
        }
        for (uint32_t mex = 0; ; ++mex) {
            if (!already.count(mex)) {
                g[ppl] = mex;
                break;
            }
        }
    }

    // for (uint32_t i : g) {
    //     cout << i << ' ';
    // }
    // cout << '\n';
 
    if (g[n] != 0) {
        cout << "Schtirlitz\n";
        for (size_t i = 0; i != n; ++i) {
            uint32_t cur = (g[i] ^ g[n - 1 - i]);
            if (cur == 0) {
                cout << i + 1 << ' ';
            }
        }
    } else {
        cout << "Mueller";
    }
}
