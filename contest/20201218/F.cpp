#include <bits/stdc++.h>
using namespace std;

#define FOR(i, way, to) for (int i = way[to] ; i != to ; i = way[i])

namespace DLX {
    int col_size, sz;
    vector<int> s, l, r, u, d, row, col, current;
    void Init(int n) {
        s.clear();
        l.clear();
        r.clear();
        u.clear();
        d.clear();
        row.clear();
        col.clear();
        current.clear();
        col_size = n;
        for (int i = 0; i <= n; ++i) {
            u.emplace_back(i);
            d.emplace_back(i);
            l.emplace_back(i - 1);
            r.emplace_back(i + 1);
        }
        s.resize(n + 1, 0);
        row.resize(n + 1, 0);
        col.resize(n + 1, 0);
        r[n] = 0, l[0] = n, sz = n + 1;
    }
    void AddRow(int rr, vector<int> sol) {
        int tmp = sz;
        for (auto to: sol) {
            l.emplace_back(sz - 1);
            r.emplace_back(sz + 1);
            d.emplace_back(to);
            u.emplace_back(u[to]);
            d[ u[to] ] = sz, u[to] = sz;
            row.emplace_back(rr);
            col.emplace_back(to);
            s[to]++, sz++;
        }
        r[sz - 1] = tmp, l[tmp] = sz - 1;
    }
    void Remove(int c) {
        l[ r[c] ] = l[c];
        r[ l[c] ] = r[c];
        FOR(i, d, c) FOR(j, r, i) {
            u[ d[j] ] = u[j];
            d[ u[j] ] = d[j];
            --s[ col[j] ];
        }
    }
    void Restore(int c) {
        FOR(i, u, c) FOR(j, l, i) {
            ++s[ col[j] ], u[ d[j] ] = d[ u[j] ] = j;
        }
        l[ r[c] ] = r[ l[c] ] = c;
    }
    void Dfs(int floor) {
        if (r[0] == 0) return;
        int c = r[0];
        FOR(i, r, 0) {
            if (s[i] <= s[c]) c = i;
            if (s[i] == 0) return;
        }
        Remove(c);
        FOR(i, d, c) {
            FOR(j, r, i) Remove(col[j]);
            current.emplace_back(row[i]);
            Dfs(floor + 1);
            if (r[0] == 0) return;
            current.pop_back();
            FOR(j, l, i) Restore(col[j]);
        }
        Restore(c);
    }
    vector<int> Solve() {
        return Dfs(0), current;
    }
}

struct Pt {
    int x, y, z;
    Pt(): x(0), y(0), z(0) {}
    Pt(int _x, int _y, int _z): x(_x), y(_y), z(_z){}
};

Pt operator+(const Pt &p1, const Pt &p2) {
    return Pt(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
}

Pt operator-(const Pt &p1, const Pt &p2) {
    return Pt(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

Pt operator^(const Pt &p1, const Pt &p2) {
    return Pt(p1.y * p2.z - p1.z * p2.y, p1.z * p2.x - p1.x * p2.z, p1.x * p2.y - p1.y * p2.x);
}

const int N = 26;

int a[N][N][N];
int n, m, k;

int dlx_id[N][N][N];

bool single_inside(Pt p) {
    return 1 <= p.x && p.x <= n && 1 <= p.y && p.y <= m && 1 <= p.z && p.z <= k;
}

bool all_inside(vector<Pt> v) {
    for (Pt p: v) {
        if (!single_inside(p)) return false;
    }
    return true;
}

int dx[6] = {1, -1, 0, 0, 0, 0};
int dy[6] = {0, 0, 1, -1, 0, 0};
int dz[6] = {0, 0, 0, 0, 1, -1};

Pt dlx_to_pt[8787];

vector< vector<int> > dlx_all;
int dlx_ptr = 0;

void f(int type, vector<Pt> pts) {
    if (all_inside(pts)) {
        for (Pt p: pts) {
            if (a[p.x][p.y][p.z] == 0) return;
        }
        vector<int> v;
        v.push_back(type + dlx_ptr);
        for (Pt p: pts) {
            v.push_back(dlx_id[p.x][p.y][p.z]);
        }
        sort(v.begin(), v.end());
        dlx_all.push_back(v);
        DLX::AddRow((int)dlx_all.size() - 1, v);
    }
}

int ans[N][N][N];

int main () {
    if (fopen("lock.in", "r")) {
        freopen("lock.in", "r", stdin);
        freopen("lock.out", "w", stdout);
    }
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int _ = 1; _ <= k; ++_) {
                cin >> a[i][j][_];
                if (a[i][j][_] == 1) {
                    dlx_id[i][j][_] = (++dlx_ptr);
                    dlx_to_pt[dlx_ptr] = Pt(i, j, _);
                }
            }
        }
    }
    DLX::Init(dlx_ptr + 7);
    // DLX::Init(dlx_ptr);
    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= m; ++y) {
            for (int z = 1; z <= k; ++z) {
                for (int v1 = 0; v1 < 6; ++v1) {
                    for (int v2 = v1 + 1; v2 < 6; ++v2) {
                        if (v1 + 1 == v2 && v1 % 2 == 0) continue;
                        Pt now = Pt(x, y, z);
                        Pt d1 = Pt(dx[v1], dy[v1], dz[v1]);
                        Pt d2 = Pt(dx[v2], dy[v2], dz[v2]);
                        Pt cross = (d1 ^ d2);
                        Pt now1 = now + d1, now2 = now + d2;
                        // type 7
                        f(7, {now, now1, now2});
                        // type 1
                        f(1, {now, now1, now2, now1 + d1});
                        f(1, {now, now1, now2, now2 + d2});
                        // type 2
                        f(2, {now, now1, now2, now1 - d2});
                        f(2, {now, now1, now2, now2 - d1});
                        // type 3
                        f(3, {now, now1, now2, now + cross});
                        f(3, {now, now1, now2, now - cross});
                        // type 4
                        f(4, {now, now1, now2, now - d1});
                        f(4, {now, now1, now2, now - d2});
                        // type 5
                        f(5, {now, now1, now2, now1 + cross});
                        f(5, {now, now1, now2, now2 - cross});
                        // type 6
                        f(6, {now, now1, now2, now1 - cross});
                        f(6, {now, now1, now2, now2 + cross});
                    }
                }
            }
        }
    }
    DLX::AddRow(-1, {dlx_ptr + 1});
    DLX::AddRow(-1, {dlx_ptr + 2});
    DLX::AddRow(-1, {dlx_ptr + 3});
    DLX::AddRow(-1, {dlx_ptr + 4});
    DLX::AddRow(-1, {dlx_ptr + 5});
    DLX::AddRow(-1, {dlx_ptr + 6});
    DLX::AddRow(-1, {dlx_ptr + 7});
    vector<int> all = DLX::Solve();
    int _ = 0;
    for (int i: all) {
        if (i == -1) continue;
        vector<int> v = dlx_all[i];
        if (v.size() == 1) continue;
        int type = v.back() - dlx_ptr;
        ++_;
        for (int j: v) {
            if (j > dlx_ptr) continue;
            Pt p = dlx_to_pt[j];
            // ans[p.x][p.y][p.z] = type;
            ans[p.x][p.y][p.z] = _;
        }
    }
    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= m; ++y) {
            for (int z = 1; z <= k; ++z) {
                printf("%d", ans[x][y][z]);
            }
            puts("");
        }
        if (x != n) puts("");
    }
}

