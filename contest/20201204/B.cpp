#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> gao(ll x) {
    set<ll> st;
    for (ll i = 1; i * i <= x; ++i) {
        if (x % i == 0) {
            st.insert(i);
            st.insert(x / i);
        }
    }
    vector<ll> ret;
    for (ll i: st) ret.push_back(i);
    return ret;
}

int main () {
    ll n; cin >> n;
    vector<ll> v1 = gao(4 * n), v2 = gao(n + 1);
    set< pair<ll, ll> > ans;
    for (ll i: v1) {
        for (ll j: v2) {
            ll val1 = i * j;
            ll val2 = (4 * n * (n + 1)) / val1;
            if (val1 > val2) continue;
            ans.insert({2 * (n + 1) + val1, 2 * (n + 1) + val2});
        }
    }
    cout << ans.size() << endl;
    for (auto i: ans) {
        cout << i.first << ' ' << i.second << endl;
    }
}

