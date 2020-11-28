#include <bits/stdc++.h>
using namespace std;

const int N = 200006;
const int P = 19;

struct BIT {
    int a[N];
    int n;
    void init(int _n) {
        n = _n;
        memset(a, 0, sizeof(a));
    }
    void update(int pos, int val) {
        for (int i = pos; i <= n; i += i & (-i)) {
            a[i] += val;
        }
    }
    int query(int pos) {
        int ret = 0;
        for (int i = pos; i > 0; i -= i & (-i)) {
            ret += a[i];
        }
        return ret;
    }
    int queryLR(int l, int r) {
        return query(r) - query(l - 1);
    }
} bit;

typedef long long ll;
typedef pair<int, int> pii;
vector<pii> G[N];

int lca[P][N];
int pin[N], pout[N];
int stamp = 0;

void dfs(int now, int par) {
    ++stamp;
    pin[now] = stamp;
    for (pii p: G[now]) {
        if (p.first != par) dfs(p.first, now);
    }
    pout[now] = stamp;
}

ll dis[P][N];

struct Cen {
    int par;
    ll tot_w;
    ll tot_par;
    int sz;
    int depth;
} c[N];

#define F first
#define S second
bool vis[N];

vector<int> all;
int sz[N], mx[N];

void dfs_cen(int now, int par) {
    sz[now] = 1;
    mx[now] = 0;
    all.push_back(now);
    for (pii p: G[now]) {
        int to = p.F;
        if (to != par && !vis[to]) {
            dfs_cen(to, now);
            mx[now] = max(mx[now], sz[to]);
            sz[now] += sz[to];
        }
    }
}

int get_cen(int now) {
    all.clear();
    dfs_cen(now, now);
    int n = (int)all.size();
    for (int i: all) {
        if (max(mx[i], n - sz[i]) <= n / 2) {
            return i;
        }
    }
}

void get_dis(int depth, int now, int par, ll now_dis) {
    dis[depth][now] = now_dis;
    for (pii p: G[now]) {
        int to = p.first;
        ll w = p.second;
        if (!vis[to] && to != par) {
            get_dis(depth, to, now, now_dis + w);
        }
    }
}

void dfs_gao(int now, int cen_par, int cen_dep) {
    int cen = get_cen(now);
    // cerr << "cen = " << cen << endl;
    c[cen].par = cen_par;
    c[cen].depth = cen_dep;
    c[cen].tot_w = 0;
    c[cen].tot_par = 0;
    c[cen].sz = 0;
    get_dis(cen_dep, cen, cen, 0);
    vis[cen] = true;
    for (pii p: G[cen]) {
        int to = p.first;
        if (!vis[to]) {
            dfs_gao(to, cen, cen_dep + 1);
        }
    }
}

void addd(int pos) {
    int now = pos;
    while (now != -1) {
        c[now].tot_w += dis[ c[now].depth ][pos];
        if (c[now].par != -1) {
            c[now].tot_par += dis[ c[now].depth - 1 ][pos];
        }
        c[now].sz++;
        now = c[now].par;
    }
    bit.update(pin[pos], 1);
}

ll query(int pos) {
    // cerr << "in q" << endl;
    ll ret = 0;
    int _ = pos;
    while (pos != -1) {
        ret += c[pos].tot_w + (c[pos].sz * 1ll * dis[ c[pos].depth ][_]);
        if (c[pos].par != -1) ret -= (c[pos].tot_par + c[pos].sz * 1ll * dis[ c[pos].depth - 1 ][_]);
        pos = c[pos].par;
    }
    // cerr << "out q" << endl;
    return ret;
}

const ll INF = (1ll << 60);

ll now_cen = 1;
ll now_ans = INF;

void update(int p) {
    ll ret = query(p);
    if (ret < now_ans) {
        now_ans = ret;
        now_cen = p;
    }
}

int main () {
    int n; scanf("%d", &n);
    for (int i = 2; i <= n; ++i) {
        int p, d; scanf("%d%d", &p, &d);
        G[p].push_back(make_pair(i, d));
        G[i].push_back(make_pair(p, d));
        lca[0][i] = p;
    }
    bit.init(n);
    lca[0][1] = 1;
    dfs(1, 1);
    for (int i = 1; i < P; ++i) {
        for (int j = 1; j <= n; ++j) {
            lca[i][j] = lca[i - 1][ lca[i - 1][j] ];
        }
    }
    dfs_gao(1, -1, 0);
    for (int k = 1; k <= n; ++k) {
        // cerr << "k = " << k << endl;
        addd(k);
        // try to find new centroid
        now_ans = INF;
        int tmp1 = now_cen;
        for (int i = P - 1; i >= 0; --i) {
            // cerr << "i = " << i << endl;
            int to = lca[i][tmp1];
            // cerr << "to = " << to << endl;
            int sz = bit.queryLR(pin[to], pout[to]);
            if (k - sz >= sz) {
                tmp1 = to;
            }
        }
        update(tmp1);
        update(lca[0][tmp1]);
        tmp1 = k;
        for (int i = P - 1; i >= 0; --i) {
            int to = lca[i][tmp1];
            int sz = bit.queryLR(pin[to], pout[to]);
            if (k - sz >= sz) {
                tmp1 = to;
            }
        }
        update(tmp1);
        update(lca[0][tmp1]);
        printf("%lld\n", now_ans);
        /*ll ans2 = query(tmp1);
        cout << "ans1 = " << ans1 << " , tmp1 = " << tmp2 << " ans2 = " << ans2 << " , tmp2 = " << tmp1 << endl;
        if (ans1 < ans2) {
            printf("%lld\n", ans1);
            now_cen = tmp2;
        }
        else {
            printf("%lld\n", ans2);
            now_cen = tmp1;
        }*/
        // assert(0);

    }
}

