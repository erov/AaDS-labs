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
    string p, t;
    cin >> p >> t;

    string work = p + "#" + t;
    vector<size_t> pref_func(work.size(), 0);
    for (size_t i = 1; i != work.size(); ++i) {
        size_t j = pref_func[i - 1];
        while (j != 0 && work[i] != work[j]) {
            j = pref_func[j - 1];
        }
        pref_func[i] = j + (work[i] == work[j] ? 1 : 0);
    }

    vector<size_t> ans;
    for (size_t i = p.size() + 1; i != work.size(); ++i) {
        if (pref_func[i] == p.size()) {
            ans.push_back(i - p.size() * 2);
        }
    }

    cout << ans.size() << '\n';
    for (size_t i : ans) {
        cout << ++i << ' ';
    }
}
