#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
ll d, arr[333], s;
int main() {
    cin >> d;
    for(int i = 0; i < d; ++ i){
        cin >> arr[i];
    }
    cin >> s;
    ll sum = 0;
    for(int i = 0; i < d; ++ i) {
        arr[i] = min(arr[i], s);
        sum += arr[i];
    }
    ll ans = 1;
    for(int i = 0; i < d; ++ i) {
        ans *= arr[i];
        ans %= MOD;
    }
    for(ll i = 1; i <= d; ++ i) {
        ans *= i;
        ans %= MOD;
    }
    ll Q = 1;
    for(int i = 0; i < d; ++ i) {
        ll w = s - (sum - arr[i]);
        w = max(w, 0LL);
        w = arr[i] - w;
        w %= MOD;
        Q = Q * w % MOD;
    }
    ans -= Q;
    ans %= MOD;
    ans += MOD;
    ans %= MOD;
    cout << ans << '\n';
    
}
