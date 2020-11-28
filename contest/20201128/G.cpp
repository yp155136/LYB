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

const int N = 1006;
pii p[N];

void no() {
    puts("Impossible");
    exit(0);
}

void yes() {
    puts("Possible");
    exit(0);
}

ll sgn(ll x) {
    return ((x > 0) - (x < 0));
}

bool check(pii p1, pii p2, pii q1, pii q2) {
    if (((p1 - p2) * (q1 - q2)) == 0) {
        return true;
    }
    int v1 = sgn((q1 - p1) * (p2 - p1)), v2 = sgn((q2 - p1) * (p2 - p1));
    if (v1 <= 0 && v2 <= 0) {
        return true;
    }
    int v3 = sgn((q1 - p2) * (p1 - p2)), v4 = sgn((q2 - p2) * (p1 - p2));
    if (v3 <= 0 && v4 <= 0) {
        return true;
    }
    return false;
}

#define X first
#define Y second

#define is_neg(_k) (_k.Y < 0 || (_k.Y == 0 && _k.X < 0))
bool cmp(pii a, pii b) {
    int A = is_neg(a), B = is_neg(b);
    return (A == B ? (a ^ b) > 0 : A < B);
}

pii q[N];

int main () {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld%lld", &p[i].F, &p[i].S);
    }
    /* 
    for (int i = 1; i <= n - 2; ++i) {
        pii p1 = (p[i] - p[i + 1]);
        pii p2 = (p[i + 2] - p[i + 1]);
        if ((p1 * p2) > 0) {
            no();
        }
    }
    for (int i = 1; i <= n - 1; ++i) {
        for (int j = 1; j <= n - 1; ++j) {
            if (i == j) continue;
            pii p1 = p[i], p2 = p[i + 1];
            pii q1 = p[j], q2 = p[j + 1];
            if (check(p1, p2, q1, q2)) {
                ;
            }
            else {
                no();
            }
        }
    }
    yes();
    */ 
    for (int i = 1; i <= n; ++i) {
        vector<pii> up, down;
        vector<int> all;
        for (int j = 1; j <= n; ++j) {
            if (i == j) continue;
            if (j < i) {
                down.push_back((p[j] - p[i]));
            }
            else if (j > i) {
                up.push_back((p[j] - p[i]));
            }
            q[j] = p[j] - p[i];
            all.push_back(j);
        }
        sort(up.begin(), up.end(), cmp);
        sort(down.begin(), down.end(), cmp);
        sort(all.begin(), all.end(), [](const int &x, const int &y) {
            return cmp(q[x], q[y]);
        });
        int n1 = (int)up.size();
        int n2 = (int)down.size();
        bool ok = false;
        for (int i = 0; i < n1; ++i) {
            pii p1 = up[i], p2 = up[(i + 1) % n1];
            // cerr << (p1 ^ p2) << endl;
            if ((p1 ^ p2) < 0) {
                // cerr << "hereee" << endl;
                ok = true;
            }
        }
        if (!ok && (int)up.size() > 1) {
            // cerr << "here i = " << i << endl;
            no();
        }
        ok = false;
        for (int i = 0; i < n2; ++i) {
            pii p1 = down[i], p2 = down[(i + 1) % n2];
            if ((p1 ^ p2) < 0) {
                ok = true;
            }
        }
        if (!ok && (int)down.size() > 1) {
            // cerr << "here ii = " << i << endl;
            no();
        }
        int last = -1;
        all.push_back(-1);
        vector<int> gao;
        for (int j: all) {
            int type = 0;
            if (j < i) {
                type = 1;
            }
            else {
                type = 2;
            }
            if (type != last) {
                if (last != -1) {
                    gao.push_back(last);
                }
            }
            last = type;
        }
        if (gao.size() > 1) {
            if (gao.back() == gao[0]) gao.pop_back();
            if (gao.size() > 2) {
                no();
            }
        }
    }
    yes();
}

