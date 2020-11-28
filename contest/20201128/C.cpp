#include <bits/stdc++.h>
using namespace std;

int deg[10];
//int gao[10];
int exi[5][5];
int mx;
int n;

void dfs(int now, int m) {
    mx = max(m, mx);
    if(now == 0)    return;
    while(now) {
        int can = 1;
        int cnt = 0;
        for(int i = 0; i < n; ++ i) {
            if(((now >> i) & 1) == 0) continue;
            ++ cnt;
            if(deg[i] == 0) {
                can = 0;
                break;
            }
            for(int j = 0; j < n; ++ j) {
                if( ((now >> j) & 1) == 0 || j == i)   continue;
                if(exi[i][j]) {
                    can = 0;
                    break;
                }
            }
            if(can == 0) break;
        }
        if(can) {
            for(int i = 0; i < n; ++ i) {
                if( ((now >> i) & 1) == 0) continue;
                deg[i] --;
                for(int j = 0; j < n; ++ j) {
                    if(((now >> j) & 1) == 0 || j == i)   continue;
                    exi[i][j] = 1;
                }
            }
            dfs(now - 1, m + cnt - 1);
            for(int i = 0; i < n; ++ i) {
                if(((now >> i) & 1) == 0) continue;
                deg[i] ++ ;
                for(int j = 0; j < n; ++ j) {
                    if(((now >> j) & 1) == 0 || j == i)   continue;
                    exi[i][j] = 0;
                }
            }
        }
        -- now;
    }
    return;
}

int main () {
    cin >> n;
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> deg[i];
        sum += deg[i];
    }
    dfs((1 << n) - 1, 0);
    cout << sum - mx << endl;
}

