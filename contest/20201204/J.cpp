#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

const int N = 100006;

long long a[N], b[N], pre[N];

int main () {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + (a[i] - b[i]) * (a[i] - b[i]);
    }
    int m; cin >> m;
    while (m--) {
        int l, r; cin >> l >> r;
        long long val = pre[r] - pre[l - 1];
        cout << fixed << setprecision(6) << sqrt(val) << '\n';
    }
}

