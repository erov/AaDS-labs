#include <algorithm>
#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

const int MAXSQRT = 1500;

struct query {
    int l, r, id;
    bool operator< (query& other) const {
        return l / MAXSQRT < other.l / MAXSQRT || (l / MAXSQRT == other.l / MAXSQRT && r < other.r);
    }
};


int main() {

    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<query> q(m);
    for (int i = 0; i < m; i++) {
        cin >> q[i].l >> q[i].r;
        q[i].l--, q[i].r--;
        q[i].id = i;
    }

    sort(q.begin(), q.end());

    const int MAXN = 1000000 + 47;
    auto* cnt = (int*) calloc(sizeof(int), MAXN);
    long long ans = a[0];
    cnt[a[0]] = 1;

    auto* result = (long long*) malloc(sizeof(long long) * m);

    int l = 0, r = 0;
    for (int i = 0; i < m; i++) {
        while (l > q[i].l) {
            l--;
            ans -= (long long) cnt[a[l]] * cnt[a[l]] * a[l];
            cnt[a[l]]++;
            ans += (long long) cnt[a[l]] * cnt[a[l]] * a[l];
        }
        while (r < q[i].r) {
            r++;
            ans -= (long long) cnt[a[r]] * cnt[a[r]] * a[r];
            cnt[a[r]]++;
            ans += (long long) cnt[a[r]] * cnt[a[r]] * a[r];
        }
        while (l < q[i].l) {
            ans -= (long long) cnt[a[l]] * cnt[a[l]] * a[l];
            cnt[a[l]]--;
            ans += (long long) cnt[a[l]] * cnt[a[l]] * a[l];
            l++;
        }
        while (r > q[i].r) {
            ans -= (long long) cnt[a[r]] * cnt[a[r]] * a[r];
            cnt[a[r]]--;
            ans += (long long) cnt[a[r]] * cnt[a[r]] * a[r];
            r--;
        }
        result[q[i].id] = ans;
    }

    for (int i = 0; i < m; i++) {
        cout << result[i] << '\n';
    }
}
