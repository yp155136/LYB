#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define F first
#define S second
#define mp make_pair

pii operator-(const pii &p1, const pii &p2) {
    return mp(p1.F - p2.F, p1.S - p2.S);
}

ll operator^(const pii &p1, const pii &p2) {
    return p1.F * p2.S - p1.S * p2.F;
}

const int N = 200006;
vector<pii> v[N];
ll area[N];
vector<int> perm;
bool used[N];

vector<pii> up[N], down[N];

bool check(vector<pii> &down, vector<pii> &up, pii p) {
    // check up
    auto iter1 = lower_bound(up.begin(), up.end(), p);
    if (iter1 == up.end()) return false;
    if (iter1 == up.begin()) return false;
    auto iter2 = iter1;
    --iter2;
    if ((((*iter1) - p) ^ ((*iter2) - p)) <= 0) return false;
    iter1 = lower_bound(down.begin(), down.end(), p);
    if (iter1 == down.end()) return false;
    if (iter1 == down.begin()) return false;
    iter2 = iter1;
    --iter2;
    if ((((*iter2) - p) ^ ((*iter1) - p)) <= 0) return false;
    return true;

}

int main () {
    if (fopen("castle.in", "r")) {
        freopen("castle.in", "r", stdin);
        freopen("castle.out", "w", stdout);
    }
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        perm.push_back(i);
        int m; scanf("%d", &m);
        for (int j = 0; j < m; ++j) {
            ll x, y; scanf("%lld%lld", &x, &y);
            v[i].push_back(mp(x, y));
        }
        for (int j = 0; j < m; ++j) {
            area[i] += (v[i][j] ^ v[i][(j + 1) % m]);
        }
        area[i] = abs(area[i]);
        // area[i] >>= 1;
        // cerr << "i = " << i << " , area = " << area[i] << endl;
        // reverse(v[i].begin(), v[i].end());
    }
    sort(perm.begin(), perm.end(), [](const int &x, const int &y) {
        return area[x] < area[y];
    });
    int qq; scanf("%d", &qq);
    vector<pii> q;
    for (int i = 1; i <= qq; ++i) {
        ll x, y; scanf("%lld%lld", &x, &y);
        q.push_back(make_pair(x, y));
    }
    for (int i = 1; i <= n; ++i) {
        vector<pii> tmp = v[i];
        ll xmin = (1ll << 20), xmax = -(1 << 20);
        for (int j = 0; j < (int)v[i].size(); ++j) {
            tmp.push_back(v[i][j]);
            xmin = min(xmin, v[i][j].F);
            xmax = max(xmax, v[i][j].F);
        }
        bool done_xmin = false, done_xmax = false;
        int nn = (int)tmp.size();
        int _ = i;
        // down first
        for (int i = 0; i < nn; ++i) {
            if (tmp[i].F == xmin && tmp[i + 1].F != xmin && !done_xmin) {
                for (int j = i; j < nn; ++j) {
                    down[_].push_back(tmp[j]);
                    if (tmp[j].F == xmax) break;
                }
                // sort(down[_].begin(), down[_].end);
                done_xmin = true;
            }
            if (tmp[i].F == xmax && tmp[i + 1].F != xmax && !done_xmax) {
                for (int j = i; j < nn; ++j) {
                    up[_].push_back(tmp[j]);
                    if (tmp[j].F == xmin) break;
                }
                // sort(up[_].begin(), up[_].end());
                reverse(up[_].begin(), up[_].end());
                done_xmax = true;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        // swap(up[i], down[i]);
        // for (pii p: up[i]) cerr << "(" << p.F << ", " << p.S << ") , "; cerr << endl;
        // for (pii p: down[i]) cerr << "(" << p.F << ", " << p.S << ") , "; cerr << endl;
    }
    /*
    for (int i = 1; i <= n; ++i) {
        swap(up[i], down[i]);
    }
    */
    for (pii p: q) {
        // false --> outside
        int l = -1, r = n;
        // check true means inside
        while (r - l != 1) {
            int mid = (l + r) >> 1;
            // cerr << "mid = " << mid << " , check = " << check(down[perm[mid]], up[perm[mid]], p) << endl;
            if (check(down[ perm[mid] ], up[ perm[mid] ], p)) r = mid;
            else l = mid;
        }
        // cerr << "r = " << r << endl;
        used[r] = true;
    }
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        // cerr << "used[i] = " << used[i] << endl;
        if (used[i]) {
            if (i == 0) ans += area[ perm[i] ];
            else ans += area[ perm[i] ] - area[ perm[i - 1] ];
        }
    }
    printf("%lld.%lld00000\n", ans / 2, 5 * (ans % 2));
}

