#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define F first
#define S second
#define mp make_pair

pii operator+(const pii &p1, const pii &p2) {
    return mp(p1.F + p2.F, p1.S + p2.S);
}

pii operator-(const pii &p1, const pii &p2) {
    return mp(p1.F - p2.F, p1.S - p2.S);
}

ll operator*(const pii &p1, const pii &p2) {
    return p1.F * p2.F + p1.S * p2.S;
}

ll operator^(const pii &p1, const pii &p2) {
    return p1.F * p2.S - p1.S * p2.F;
}

const int N = 200006;

pii p[N];
ll w[N];

#define X first
#define Y second

#define is_neg(_k) (_k.Y < 0 || (_k.Y == 0 && _k.X < 0))
bool cmp(pii a, pii b) {
    int A = is_neg(a), B = is_neg(b);
    return (A == B ? (a ^ b) > 0 : A < B);
}

const ll INF = (1ll << 60);
map<pii, ll> cc;

typedef pair<pii, ll> piii;
#define FF F.F
#define FS F.S

ll solve(vector<piii> v) {
    if (v.size() < 3) return INF;
    ll ret = INF;
    int n = (int)v.size();
    int mx_id = -1;
    for (int i = 0; i < n; ++i) {
        if (v[i].FF >= 0 && v[i].FS >= 0) {
            if (mx_id == -1) {
                mx_id = i;
            }
            else if (v[mx_id].S > v[i].S){
                mx_id = i;
            }
        }
    }
    if (mx_id == -1) return INF;
    int ptr = (mx_id + 1) % n;
    while (ptr != mx_id && (v[mx_id].F ^ v[ptr].F) >= 0) {
        ptr = (ptr + 1) % n;
    }
    // if ((v[mx_id].F ^ v[ptr].F) >= 0) return INF;
    if ((v[ptr].F ^ v[mx_id].F) < 0) return INF;
    int st = ptr;
    ll mnn = INF;
    /* for (auto p: v) cerr << p.FF << ' ' << p.FS << endl;
    cerr << "sttttt" << endl;
    cerr << "mx_id = " << mx_id << " , st = " << st << endl; */
    for (int i = (mx_id + 1) % n; i != st; i = (i + 1) % n) {
        if ((v[mx_id].F ^ v[i].F) <= 0) break;
        ll tmp = v[mx_id].S + v[i].S;
        // cerr << "mx_iud = " << mx_id << " , i = " << i << endl;
        // cerr << "n = " << n << endl;
        while (ptr != mx_id && (v[i].F ^ v[ptr].F) > 0) {
            mnn = min(mnn, v[ptr].S);
            ptr = (ptr + 1) % n;
        }
        // cerr << "tmp = " << tmp << " , mnn = " << mnn << endl;
        ret = min(ret, tmp + mnn);
    }
    return ret;
}

int main () {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld%lld%lld", &p[i].F, &p[i].S, &w[i]);
        if (p[i] == mp(0ll, 0ll)) {
            swap(p[i], p[n]);
            --n;
            --i;
            continue;
        }
        ll gcd = abs(__gcd(p[i].F, p[i].S));
        p[i].F /= gcd;
        p[i].S /= gcd;
        if (cc.find(p[i]) == cc.end()) {
            cc[ p[i] ] = w[i];
        }
        else {
            cc[ p[i] ] = min( cc[ p[i] ], w[i] );
        }
    }
    ll ans = INF;
    // 4 vector
    for (int i = 1; i <= n; ++i) {
        ll x = p[i].F, y = p[i].S;
       if (x == y && x == 0) continue;
        pii p1 = mp(x, y), p2 = mp(-y, x), p3 = mp(-x, -y), p4 = mp(y, -x);
        if (cc.find(p1) != cc.end() && 
        (cc.find(p2) != cc.end()) &&
        (cc.find(p3) != cc.end()) &&
        (cc.find(p4) != cc.end()) ) {
            ans = min(ans, cc[p1] + cc[p2] + cc[p3] + cc[p4]);
        }
    }
    // 3 vector
    vector<piii> all;
    for (auto _: cc) {
        all.push_back(_);
    }
    sort(all.begin(), all.end(), [](const piii &p1, const piii &p2) {
        return cmp(p1.F, p2.F);
    });
    ans = min(ans, solve(all));
    for (auto &p: all) {
        p.F = mp(-p.FS, p.FF);
    }
    ans = min(ans, solve(all));
    for (auto &p: all) {
        p.F = mp(-p.FS, p.FF);
    }
    ans = min(ans, solve(all));
    for (auto &p: all) {
        p.F = mp(-p.FS, p.FF);
    }
    ans = min(ans, solve(all));
    for (auto &p: all) {
        p.F = mp(-p.FS, p.FF);
    }
    ans = min(ans, solve(all));
    if (ans > (1ll << 40)) puts("-1");
    else printf("%lld\n", ans);
}

