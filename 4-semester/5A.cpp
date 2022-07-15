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
    string a, b;
    cin >> a >> b;

    bool positive = true;
    auto update_sign = [&](string& str) -> void {
        if (str[0] == '-') {
            positive ^= 1;
            str.erase(0, 1);
        }
    };
    update_sign(a);
    update_sign(b);
    

    size_t n = (1 << (sizeof(size_t) * 8 - __builtin_clz(max(a.size(), b.size())))) << 1;
    vector<complex<double>> a_poly(n, 0);
    vector<complex<double>> b_poly(n, 0);

    auto to_poly = [](vector<complex<double>>& poly, string number) -> void {
        reverse(number.begin(), number.end());

        for (size_t i = 0; i != number.size(); ++i) {
            poly[i] = complex<double>(static_cast<double>(number[i] - '0'), 0);
        }
    };

    to_poly(a_poly, a);
    to_poly(b_poly, b);

    fft(a_poly);
    fft(b_poly);
    for (size_t i = 0; i != a_poly.size(); ++i) {
        a_poly[i] *= b_poly[i];
    }
    fft(a_poly, true);

    vector<uint32_t> mul;
    for (size_t i = 0; i != a_poly.size(); ++i) {
        mul.push_back(static_cast<uint32_t>(a_poly[i].real() + 0.5));
    }

    size_t carry = 0;
    for (size_t i = 0; i != mul.size(); ++i) {
        mul[i] += carry;
        carry = mul[i] / 10;
        mul[i] %= 10;
    }

    while (mul.size() > 1 && mul.back() == 0) {
        mul.pop_back();
    }

    if (!positive && !(mul.size() == 1 && mul.back() == 0)) {
        cout << '-';
    }
    for (size_t i = 0; i != mul.size(); ++i) {
        cout << mul[mul.size() - 1 -  i];
    }
}

