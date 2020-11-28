#include <bits/stdc++.h>
using namespace std;
#define int long long
#define maxn 52
#define mod 1000000007

int n, m, dp[maxn][maxn][22][30];
string s[maxn];

int DP(int l, int r, int idx, int f) {

    if (dp[l][r][idx][f] != -1) return dp[l][r][idx][f];
    
    if (l != r && s[l].size() == idx && s[l + 1].size() == idx) return 0;
    if (f == 26)
        return dp[l][r][idx][f] = 0;
    if (l == r && idx == s[l].size())
        return dp[l][r][idx][f] = 1;
    if (f == 0 && s[l].size() == idx)
        return dp[l][r][idx][f] = DP(l + 1, r, idx, f);
    
    
    int ans = DP(l, r, idx, f + 1);

    for (int i = l; i <= r; ++ i) {
        if (s[i].size() <= idx) return 0;
    }

    for (int i = l; i <= r; ++ i) {
        if (s[i][idx] - 'a' == f || s[i][idx] == '?') {
            if (i != r)
                 ans = (ans + DP(l, i, idx + 1, 0) * DP(i + 1, r, idx, f + 1)) % mod;
            else ans = (ans + DP(l, i, idx + 1, 0)) % mod;
        } else break;
    }
    //cout << "l = " << l << " r = " << r << " idx = " << idx << " f = " << char(f + 'a') << " ans: " << ans << "\n";
    return dp[l][r][idx][f] = ans;
}

int32_t main() {
    cin.tie(0), cout.sync_with_stdio(0);
    memset(dp, -1, sizeof dp);
    cin >> n;
    for (int i = 0; i < n; ++ i) cin >> s[i];
    
//    int big = 0;
//    for (int i = 0; i < n; ++ i) big = max(big, s[i].size());
//    for (int i = 0; i < n; ++ i) while (s[i].size() != big) s[i] += 'a' - 1;
//    for (int i = 0; i < n; ++ i)
//        for (int j = 0; j < s[i].size(); ++ j)
//            s[i][j] ++;
    
    cout << DP(0, n - 1, 0, 0) << "\n";
    return 0;
}
