#define edge pair<int, PII>
int n, sol[maxn];
PII x[maxn];
vector<edge> v;
class djs{
public:
    int x[maxn];
    void init(){ for (int i = 0; i < maxn; ++ i) x[i] = i; }
    int Find(int now){ return x[now] == now ? now : x[now] = Find(x[now]); }
    void Union(int a, int b){ x[Find(a)] = Find(b); }
    int operator[](int now){ return Find(now); }
} ds;
PII bit[maxn];
void update(int from, int val, int id){
    for(int i = from; i < maxn; i += i & -i)
        bit[i] = maxn(bit[i], mp(val, id));
}
int query(int from){
    PII res = bit[from];
    for(int i = from; i > 0; i -= i & -i)
        res = maxn(res, bit[i]);
    return res.B;
}
int cmp(int a, int b){
    return x[a] < x[b];
}
int DIS(int q, int w){
    return abs(x[q].A - x[w].A) + abs(x[q].B - x[w].B);
}
void BuildEdge(){
    vector<int> uni;
    for (int i = 0; i < maxn; ++ i)
        bit[i] = mp(-INF, -1);
    for (int i = 0; i < n; ++ i) sol[i] = i;
    for (int i = 0; i < n; ++ i) uni.pb(x[i].B - x[i].A);
    sort(ALL(uni));
    uni.resize(unique(ALL(uni)) - uni.begin());
    sort(sol, sol + n, cmp);
    for (int i = 0; i < n; ++ i){
        int now = sol[i];
        int tmp = x[sol[i]].B - x[sol[i]].A;
        int po = lower_bound(ALL(uni), tmp) - uni.begin() + 1;
        int id = query(po);
        if(id >= 0) v.pb(mp(DIS(id, now), mp(id, now)));
        update(po, x[now].A + x[now].B, now);
    }
}
void Build(){
    BuildEdge();
    for (int i = 0; i < n; ++ i) swap(x[i].A, x[i].B);
    BuildEdge();
    for (int i = 0; i < n; ++ i) x[i].A *= -1;
    BuildEdge();
    for (int i = 0; i < n; ++ i) swap(x[i].A, x[i].B);
    BuildEdge();
}
int solveKruskal(){
    ds.init();
    sort(ALL(v));
    int res = 0;
    for (int i = 0; i < v.size(); ++ i) {
        int dis = v[i].A;
        PII tmp = v[i].B;
        if(ds[tmp.A] != ds[tmp.B]){
            ds.Union(tmp.A, tmp.B);
            res += dis;
        }
    }
    return res;
}
int32_t main(){
    IOS;
    cin >> n;
    for (int i = 0; i < n; ++ i) cin >> x[i].A >> x[i].B;
    Build();
    int ans = solveKruskal();
    cout << ans << endl;
    return 0;
}
