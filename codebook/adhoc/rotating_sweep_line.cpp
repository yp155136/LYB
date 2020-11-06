PII p[maxn];
int n, idx[maxn], pos[maxn];
vector<PII> v;
inline PII operator + (PII x, PII y) {
	return make_pair(x.F + y.F, x.S + y.S); }
inline PII operator - (PII x, PII y) { 
	return make_pair(x.F - y.F, x.S - y.S); }
inline long long cross(PII x, PII y) { 
	return 1ll * x.F * y.S - 1ll * x.S * y.F; }
inline int cmp(PII x, PII y) {
	x = p[x.S] - p[x.F];
	y = p[y.S] - p[y.F];
	return cross(x, y) > 0;
}
int32_t main() {
	cin.tie(0), cout.sync_with_stdio(0);
	cin >> n >> wnt, wnt += wnt;
	for (int i = 1; i <= n; ++ i)
		cin >> p[i].F >> p[i].S;
	sort(p + 1, p + 1 + n);
	for (int i = 1; i <= n; ++ i)
		idx[i] = i, pos[i] = i;
	for (int i = 1; i <= n; ++ i)
		for (int j = i + 1; j <= n; ++ j)
			v.emplace_back(i, j);
	sort(v.begin(), v.end(), cmp);

	for(auto line : v) {
		int fr = pos[line.F], ba = pos[line.S], now;
		if(fr > ba) swap(fr, ba);
		// [TODO] points:
		// p[idx[    1]] more farther
		// p[idx[    2]] farther
		// p[idx[   fr]] ... p[idx[ba]]
		// p[idx[n - 1]] farther
		// p[idx[n - 0]] more farther
		swap(idx[fr], idx[ba]);
		swap(pos[line.F], pos[line.S]);
	} 
    return 0;
}

