#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

int main () {
    ld d; cin >> d;
    ld ans1 = d * sqrt(2);
    ld dd = floor(d);
    ld eps = 1e-9;
    if (dd - eps <= d && d <= sqrt(dd * dd + 1) + eps) {
        ans1 = max(ans1, dd + 1);
    }
    cout << fixed << setprecision(12) << ans1 << endl;
}

