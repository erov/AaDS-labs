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
    size_t n, m;
    cin >> n >> m;

    if (n == 1) {
        cout << 1;
        return;
    }

    vector<uint64_t> a(n);
    for (size_t i = 0; i != n; ++i) {
        cin >> a[i];
    }

    constexpr uint64_t POLY = 47;
    constexpr uint64_t MOD = 1'000'000'000 + 47;

    vector<uint64_t> poly_deg(n, 1);
    for (size_t i = 1; i != n; ++i) {
        poly_deg[i] = poly_deg[i - 1] * POLY % MOD;
    }

    // p^(n - 1), p^(n - 2), ..., p, 1
    vector<uint64_t> hash(n);
    for (size_t i = 0; i != n; ++i) {
        hash[i] = (i != 0 ? hash[i - 1] : 0ULL) * POLY + a[i];
        hash[i] %= MOD;
    }

    reverse(a.begin(), a.end());
    vector<uint64_t> rev_hash(n);
    for (size_t i = 0; i != n; ++i) {
        rev_hash[i] = (i != 0 ? rev_hash[i - 1] : 0ULL) * POLY + a[i];
        rev_hash[i] %= MOD;
    }

    vector<size_t> ans;

    for (size_t i = (n + 1) / 2; i <= n; ++i) {
        size_t real = n - i;
        uint64_t real_hash = (real != 0 ? hash[real - 1] : 0);

        size_t j = i - 1;
        int64_t mirror_hash = rev_hash[j];
        if (j >= real) {
            mirror_hash -= (rev_hash[j - real] * poly_deg[real]) % MOD;
            mirror_hash += MOD;
            mirror_hash %= MOD;
        }
        if (real_hash == mirror_hash) {
            ans.push_back(i);
        }
    }

    for (auto cnt : ans) {
        cout << cnt << ' ';
    }
}
