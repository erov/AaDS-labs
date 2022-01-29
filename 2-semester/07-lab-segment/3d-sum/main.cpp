#include <iostream>
#include <vector>

using namespace std;


int a, b, c;
void add(vector<vector<vector<unsigned int>>> &tree, int i_, int j_, int k_, unsigned int value) {
    for (int i = i_; i < a; i = (i | (i + 1))) {
        for (int j = j_; j < b; j = (j | (j + 1))) {
            for (int k = k_; k < c; k = (k | (k + 1))) {
                tree[i][j][k] += value;
            }
        }
    }
}

unsigned int get(vector<vector<vector<unsigned int>>> &tree, int i_, int j_, int k_) {
    unsigned int result = 0;
    for (int i = i_; i >= 0; i = (i & (i + 1)) - 1) {
        for (int j = j_; j >= 0; j = (j & (j + 1)) - 1) {
            for (int k = k_; k >= 0; k = (k & (k + 1)) - 1) {
                result += tree[i][j][k];
            }
        }
    }
    return result;
}

void add_suffix(vector<vector<vector<unsigned int>>> &t,
                vector<vector<vector<unsigned int>>> &ti,
                vector<vector<vector<unsigned int>>> &tj,
                vector<vector<vector<unsigned int>>> &tk, int i_, int j_, int k_, int value) {
    add(t, i_, j_, k_, value * (3 - i_ - j_ - k_));
    add(ti, i_, j_, k_, value);
    add(tj, i_, j_, k_, value);
    add(tk, i_, j_, k_, value);
}

void add(FenwickTree* t, FenwickTree* ti, int l, int r, int value) {
    add_suffix(t, ti, l, value);
    add_suffix(t, ti, r + 1, -value);
}

int get_sum_prefix(FenwickTree* t, FenwickTree* ti, int pos) {
    return t->get(pos) + ti->get(pos) * pos;
}

int get_sum(FenwickTree* t, FenwickTree *ti, int l, int r) {
    return get_sum_prefix(t, ti, r) - get_sum_prefix(t, ti, l - 1);
}

int main() {
    cin >> a >> b >> c;

    vector<vector<vector<unsigned int>>> t(a, vector<vector<unsigned int>> (b, vector<unsigned int> (c, 0)));
    vector<vector<vector<unsigned int>>> ti(a, vector<vector<unsigned int>> (b, vector<unsigned int> (c, 0)));
    vector<vector<vector<unsigned int>>> tj(a, vector<vector<unsigned int>> (b, vector<unsigned int> (c, 0)));
    vector<vector<vector<unsigned int>>> tk(a, vector<vector<unsigned int>> (b, vector<unsigned int> (c, 0)));

    int q;
    cin >> q;

}
