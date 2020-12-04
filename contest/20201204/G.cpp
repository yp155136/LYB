#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef pair<int, int> pii;

const int N = 55;

map<pii, int> dp[N][N];
int arr[N];
int n;

int que(int l, int r, pii ii) {
    // cout << l << ' ' << r << '\n';
    if(dp[l][r].find(ii) != dp[l][r].end()) return dp[l][r][ii];
    // cout << "here" << endl;
    
    if(l == r)  return dp[l][r][ii] = 0;
    if(l == r - 1) {
        return dp[l][r][ii] = (__gcd(ii.first, ii.second) != 1);
    }
    set<int> st;
    // cout << "l = " << l << endl;
    int g = __gcd(ii.first, arr[l + 1]);

    if(g != 1){
        pii pa = ii;
        pa.first = arr[l + 1] / g;
        st.insert(que(l + 1, r, pa) );
    }
    // cout << "r = " << r << endl;
    
    g = __gcd(ii.second, arr[r - 1]);

    if(g != 1) {
        pii pa = ii;
        pa.second = arr[r - 1] / g;
        st.insert(que(l, r - 1, pa));
    }

    for(int i = l + 1; i <= r - 2; ++ i) {
        g = __gcd(arr[i], arr[i + 1]);
        if(g != 1) {
            pii pa = ii;
            pa.second = arr[i] / g;
            pii pb = ii;
            pb.first = arr[i + 1] / g;
            st.insert(que(l, i, pa) ^ que(i + 1, r, pb));
        }
    }
    for(int i = 0; ; ++ i) {
        if(st.find(i) == st.end()) {
            //cerr << l << ' ' << r << ' ' << ii.first << ' ' << ii.second << ' ' << i << '\n';
            return dp[l][r][ii] = i;
        }
    }
}

int main () {
//    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++ i) {
        cin >> arr[i];
    }
    // memset(dp, -1, sizeof dp);
    int s = que(1, n, pii(arr[1], arr[n]));
    if(s == 0) cout << "Bob\n";
    else        cout << "Alice\n";
}
