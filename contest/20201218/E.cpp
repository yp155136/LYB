#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, k;

struct Level {
    int e, h, d, r;
} l[120];

struct People {
    int h, d, e;
} p[120];

int dp[1 << 21], xx[1 << 21], ee[1 << 21], x[120];

int32_t main() {
    if (fopen("creeping.in", "r")) {
        freopen("creeping.in", "r", stdin);
        freopen("creeping.out", "w", stdout);
    }
    cin.tie(0), cout.sync_with_stdio(0);
    
    cin >> n >> k;

    for (int i = 1; i <= k; ++ i) 
        cin >> l[i].e >> l[i].h >> l[i].d >> l[i].r, x[i] = l[i].e;
    
    x[k + 1] = x[k] + 100;

    for (int i = 0; i < n; ++ i)
        cin >> p[i].h >> p[i].d >> p[i].e;
    
    int ans = 0;


    for (int i = 0; i < (1 << n); ++ i) {
        for (int j = 0; j < n; ++ j) 
            if (i & (1 << j)) ee[i] += p[j].e;
        xx[i] = upper_bound(x + 1, x + k + 1 + 1, min(x[k], ee[i])) - 1 - x;
//        cout << "i: " << i << " " << xx[i] << "\n";
    }
    
    memset(dp, -1, sizeof dp);
    dp[0] = 1;
    
    for (int i = 0; i < (1 << n); ++ i) {
        if (dp[i] == -1) continue;
        for (int j = 0; j < n; ++ j) {
            if (i & (1 << j)) continue;
            
            int now_level = xx[i];
            int newdam = p[j].d - l[now_level].r;
            int newbld = min(l[xx[i | (1 << j)]].h, l[now_level].h);
            
            // i die time = newbld / newdam
            // y die time = p[j].h / l[now_level].d

            // if (newbld * l[now_level].d > p[j].h * newdam)

            if (newdam <= 0)
                dp[i | (1 << j)] = j;
            else {
                int i_die_time = newbld / newdam + (newbld % newdam != 0);
                int y_die_time = p[j].h / l[now_level].d + (p[j].h % l[now_level].d != 0);
                if (i_die_time > y_die_time) 
                    dp[i | (1 << j)] = j;
            }
        }
        if (ee[i] > ee[ans]) ans = i;
    }

    cout << ee[ans] << "\n";
    vector<int> sol;
    while (ans != 0) sol.emplace_back(dp[ans]), ans = ans ^ (1 << dp[ans]);
    reverse(sol.begin(), sol.end());
    
    cout << sol.size() << "\n";
    
    for (int i = 0; i < sol.size(); ++ i)
        cout << sol[i] + 1 << " \n"[i + 1 == sol.size()];
    return 0;
}
