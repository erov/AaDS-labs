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


bool dfs_kuhn(map<size_t, vector<size_t>>& g, unordered_map<size_t, size_t>& used, unordered_map<size_t, size_t>& matching,
              const size_t non_matched, const size_t used_marker, size_t v) {

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
    string text;
    cin >> text;

    text = static_cast<char>(('a' <= text[0] && text[0] <= 'z' ? 'Z' : 'z') + 1) + text;
    text = text + static_cast<char>(('a' <= text.back() && text.back() <= 'z' ? 'Z' : 'z') + 1);

    constexpr size_t MAX_CHAR = 27;
    auto get_index = [](char ch) -> size_t {
        return 'a' <= ch && ch <= 'z' + 1 ? ch - 'a' : ch - 'A';
    };

    auto encode = [&](char first, char second) -> size_t {
        return get_index(first) * MAX_CHAR + get_index(second) + ('a' <= first && first <= 'z' + 1 ? MAX_CHAR * MAX_CHAR : 0);
    };

    map<size_t, vector<size_t>> compatibility;
    for (size_t i = 0; i + 2 != text.size(); ++i) {
        size_t lhs = encode(text[i], text[i + 1]);
        size_t rhs = encode(text[i + 1], text[i + 2]);
        compatibility[lhs].push_back(rhs);
        compatibility[rhs].push_back(lhs);
    }

    char first = 'a';
    char second = 'A';
    if (text[0] == 'Z' + 1) {
        swap(first, second);
    }

    unordered_map<size_t, size_t> used;
    size_t used_marker = 0;
    constexpr size_t non_matched = numeric_limits<size_t>::max();
    unordered_map<size_t, size_t> matching;

    for (char i = second; i != second + MAX_CHAR; ++i) {
        for (char j = first; j != first + MAX_CHAR; ++j) {
            matching[encode(i, j)] = non_matched;
        }
    }

    for (char i = first; i != first + MAX_CHAR; ++i) {
        for (char j = second; j != second + MAX_CHAR; ++j) {
            ++used_marker;
            dfs_kuhn(compatibility, used, matching, non_matched, used_marker, encode(i, j));
        }
    }

    size_t matching_size = 0;
    for (char i = second; i != second + MAX_CHAR; ++i) {
        for (char j = first; j != first + MAX_CHAR; ++j) {
            matching_size += (matching[encode(i, j)] != non_matched ? 1 : 0);
        }
    }

    cout << matching_size;
}