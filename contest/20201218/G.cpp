#include <bits/stdc++.h>
using namespace std;

const int N = 200006;
typedef long double ld;

typedef long long ll;

int main () {
    if (fopen("princess.in" ,"r")) {
        freopen("princess.in", "r", stdin);
        freopen("princess.out", "w", stdout);
    }
    ios::sync_with_stdio(0); cin.tie(0);
    ld L;
    cin >> L;
    ld l = log(L);
    int a = l;
    int b = a + 1;
    ld ans = 300;
    if(a != 0) {
        ans = min(ans, (ld) a * pow(L, (ld)(1/(ld)a)) );
    }
    if(b != 0) {
        ans = min(ans, (ld) b * pow(L, (ld)(1/(ld)b)) );
    }
    cout << setprecision(6) << fixed << ans << '\n';

}


