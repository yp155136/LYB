const int Mlg = __lg(MAX) + 2;

struct edge {
	int to, weight;
	edge(int _to, int _w): to(_to), weight(_w) {}
};

vector<edge> edg[MAX];

struct Cen {
	ll val;
	int p, sz, dep;
	Cen() {}
	Cen(int _p, int _d): val(0), p(_p), sz(0), dep(_d) {}
}
cen[MAX];
ll dis[Mlg][MAX];

bool visit[MAX];
vector < int > v;
int sz[MAX], mx[MAX];
void dfs_sz(int id) {
	visit[id] = 1;
	v.push_back(id);
	sz[id] = 1;
	mx[id] = 0;
	for (edge i: edg[id]) {
		if (!visit[i.to]) {
			dfs_sz(i.to);
			mx[id] = max(mx[id], sz[i.to]);
			sz[id] += sz[i.to];
		}
	}
}
void dfs_dis(int id, int cen_dep, ll weight) {
	dis[cen_dep][id] = weight;
	visit[id] = 1;
	for (edge i: edg[id])
		if (!visit[i.to])
			dfs_dis(i.to, cen_dep, weight + i.weight);
}
void build(int id, int cen_dep, int p) {
	dfs_sz(id);
	int nn = v.size();
	int ccen = -1;
	for (int i: v) {
		if (max(nn - sz[i], mx[i]) * 2 <= nn)
			ccen = i;
		visit[i] = 0;
	}
	dfs_dis(ccen, cen_dep, 0);
	for (int i: v) visit[i] = 0;
	v.clear();
	visit[ccen] = 1;
	cen[ccen] = Cen(p, cen_dep);
	for (edge i: edg[ccen])
		if (!visit[i.to])
			build(i.to, cen_dep + 1, ccen);
}

void add(int id, int d) {
	for (int p = id; p != -1; p = cen[p].p) {
		cen[p].val += dis[cen[p].dep][id] * d;
		cen[p].val -= dis[cen[p].dep - 1][id] * d;
		cen[p].sz += d;
	}
}

ll query(int id) {
	ll ret = 0;
	int pre_sz = 0;
	for (int p = id; p != -1; p = cen[p].p) {
		ret += cen[p].val;
		ret += (cen[p].sz - pre_sz) * dis[cen[p].dep][id];
		pre_sz = cen[p].sz;
	}
	return ret;
}
// edg[u].push_back(edge(v,w));
// edg[v].push_back(edge(u,w));
// memset(visit,0,sizeof(visit));
// build(1,1,-1);
// add(u, d)
// query(u)