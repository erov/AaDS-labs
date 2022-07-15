#include <algorithm>
#include <array>
#include <cassert>
#include <climits>
#include <cmath>
#include <complex>
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


void fft(vector<complex<double>>& poly, bool is_interpolation = false) {
    if (poly.size() == 1) {
        return;
    }

    vector<complex<double>> even;
    vector<complex<double>> odd;

    for (size_t i = 0; i != poly.size(); ++i) {
        if (i % 2 == 0) {
            even.push_back(poly[i]);
        } else {
            odd.push_back(poly[i]);
        }
    }
 
    fft(even, is_interpolation);
    fft(odd, is_interpolation);

    double r_arg = 2 * acos(-1) / poly.size();
    if (is_interpolation) {
        r_arg *= -1;
    }

    complex<double> r(cos(r_arg), sin(r_arg));
    complex<double> x = 1;

    for (size_t i = 0; i != even.size(); ++i) {
        poly[i] = even[i] + x * odd[i];
        poly[i + even.size()] = even[i] - x * odd[i];
        x *= r;
    }

    if (is_interpolation) {
        for (size_t i = 0; i != poly.size(); ++i) {
            poly[i] /= 2;
        }
    }
}


void solve() {
    string alley;
    cin >> alley;

    size_t n = (1 << (sizeof(size_t) * 8 - __builtin_clz(alley.size()))) << 1;
    vector<complex<double>> a_poly(n, 0);

    for (size_t i = 0; i != alley.size(); ++i) {
        a_poly[i] = complex<double>(static_cast<double>(alley[i] - '0'), 0);
    }

    fft(a_poly);
    for (size_t i = 0; i != a_poly.size(); ++i) {
        a_poly[i] *= a_poly[i];
    }
    fft(a_poly, true);

    vector<uint32_t> mul;
    for (size_t i = 0; i != a_poly.size(); ++i) {
        mul.push_back(static_cast<uint32_t>(a_poly[i].real() + 0.5));
    }

    uint32_t ans = 0;
    for (size_t i = 0; i != alley.size(); ++i) {
        ans += (alley[i] == '1' ? 1 : 0) * (mul[i * 2] - 1) / 2;
    }

    cout << ans;
}

