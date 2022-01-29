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
    string s;
    cin >> s;

    vector<size_t> pref_func(s.size(), 0);
    for (size_t i = 1; i != s.size(); ++i) {
        size_t j = pref_func[i - 1];
        while (j != 0 && s[i] != s[j]) {
            j = pref_func[j - 1];
        }
        pref_func[i] = j + (s[i] == s[j] ? 1 : 0);
    }

    size_t ans = s.size() - pref_func[s.size() - 1];
    cout << (s.size() % ans != 0 ? s.size() : ans);
}
