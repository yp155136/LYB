#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll dp[10006];

int main () {
    ios::sync_with_stdio(0); cin.tie(0);
    ll n, k; cin >> n >> k;
    for (ll i = 2; i <= n - 1; ++i) {
        dp[1] = 1;
        for (ll j = 2; j <= n; ++j) {
            dp[j] = dp[j - 1];
            if (j - i >= 1) {
                dp[j] += dp[j - i];
            }
            if (j % 7 == 0) {
                dp[j] += dp[j / 7];
            }
            dp[j] = min(dp[j], (1ll << 61));
        }
        if (dp[n] == k) {
            cout << i << endl;
            return 0;
        }
    }
    cout << 0 << endl;
}

