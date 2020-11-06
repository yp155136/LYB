int n, x[MAX], ans = 0;
vector<int> v;
int DFS(int now) {
    int val = v[now] + v[now + 1];
    ans += val;
    v.erase(v.begin() + now);
    v.erase(v.begin() + now);
    int id = 0;
    for (int i = now - 1; i >= 0; -- i)
        if(v[i] >= val) { id = i + 1; break; }
    v.insert(v.begin() + id, val);
    while(id >= 2 && v[id - 2] <= v[id]) {
        int dis = v.size() - id;
        DFS(id - 2);
        id = v.size() - dis;
    }
}
int32_t main() {
    IOS;
    cin >> n;
    for (int i = 0; i < n; ++ i) cin >> x[i];
    for (int i = 0; i < n; ++ i) {
        v.emplace_back(x[i]);
        while(v.size() >= 3 && v[v.size() - 3] <= v[v.size() - 1]) 
            DFS(v.size() - 3);
    }
    while(v.size() > 1) DFS(v.size() - 2);
    cout << ans << endl;
    return 0;
}
