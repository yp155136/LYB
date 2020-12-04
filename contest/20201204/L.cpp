#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ld, ld> pii;

#define F first
#define S second

pii operator-(const pii &p1, const pii &p2) {
    return make_pair(p1.F - p2.F, p1.S - p2.S);
}

ld operator*(const pii &p1, const pii &p2) {
    return p1.F * p2.F + p1.S * p2.S;
}

ld operator^(const pii &p1, const pii &p2) {
    return p1.F * p2.S - p1.S * p2.F;
}

#define SZ(x) ((int)(x).size())

const ld eps = 1e-9;

int sgn(ld x) {
    if (x < -eps) return -1;
    if (x > eps) return 1;
    return 0;
}

int main () {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; ld d; cin >> n >> d;
    ld ans = 2 * acos(-1) * d;
    vector<pii> v;
    for (int i = 1; i <= n; ++i) {
        int k; cin >> k;
        while (k--) {
            ld a, b; cin >> a >> b;
            v.push_back({a, b});
        }
    }
    sort(v.begin(), v.end());
    vector<pii> up, down;
    for (pii p: v) {
        while (SZ(down) >= 2 && sgn((p - down[SZ(down) - 2]) ^ (p - down.back())) >= 0) {
            down.pop_back();
        }
        down.push_back(p);
    }
    reverse(v.begin(), v.end());
    for (pii p: v) {
        while (SZ(up) >= 2 && sgn((p - up[SZ(up) - 2]) ^ (p - up.back())) >= 0) {
            up.pop_back();
        }
        up.push_back(p);
    }
    vector<pii> all;
    for (pii p: down) all.push_back(p);
    all.pop_back();
    for (pii p: up) all.push_back(p);
    // cerr << "ans = " << ans << endl;
    for (int i = 0; i < SZ(all) - 1; ++i) {
        // cerr << all[i].F << " , " << all[i].S << endl;
        ans += sqrt((all[i] - all[i + 1]) * (all[i] - all[i + 1]));
    }
    cout << fixed << setprecision(5) << ans << endl;
}
