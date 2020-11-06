/*
Maximum density subgraph (\sum W_e + \sum W_v) / |V|
Binary search on answer:
For a fixed D, construct a Max flow model as follow:
Let S be Sum of all weight(or inf)
1. from source to each node with cap = S
2. For each (u,v,w) in E, (u->v,cap=w), (v->u,cap=w)
3. For each node v, from v to sink with cap = S + 2 * D - deg[v] - 2 * (W of v)
where deg[v] = \sum weight of edge associated with v
If maxflow < S * |V|, D is an answer.
Requiring subgraph: all vertex can be reached from source with
edge whose cap > 0.
*/

//Be careful that it's zero base !!!!!!!!
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define SZ(x) ((int)(x).size())
#define eb emplace_back
const ll INF = 0x3f3f3f3f3f3f3f3f;

const ll N = 5e2 + 5;
struct isap{
	struct edge{
		int t, r;
		ll c;
		edge(int _t, int _r, ll _c) : t(_t), r(_r), c(_c) {}
	};
	int n, S, T;
	vector<edge> adj[N];
	int dis[N], gap[N], ok;
	isap(int _n, int _s, int _t) : n(_n), S(_s), T(_t) {
		for(int i = 0; i < n + 2; ++ i)	adj[i].clear();
	}
	void add(int u, int v, ll c){
		adj[u].eb(v, adj[v].size(), c);
		adj[v].eb(u, adj[u].size() - 1, 0);
	}
	ll dfs(int now, ll f){
		if(now == T)	return f;
		int mi = n;
		for(edge &e : adj[now]){
			if(e.c){
				ll x;
				if(dis[now] == dis[e.t] + 1 && (x = dfs(e.t, min(f, e.c)))){
					e.c -= x;
					adj[e.t][e.r].c += x;
					return x;
				}
				mi = min(mi, dis[e.t]);
			}
		}
		if(--gap[dis[now]] == 0)	ok = 0;
		dis[now] = mi + 1;
		gap[ dis[now] ]++;
		return 0;
	}
	ll flow(){
		memset(dis, 0, n * 4);
		memset(gap, 0, n * 4);
		gap[0] = n;
		ok = 1;
		ll r = 0;
		while(dis[S] < n && ok)	r += dfs(S, INF);
		return r;
	}
	// below for bounded only
	ll D[N];
	void bounded_init() {
		memset(D, 0, n * 8);
	}
	void add2(int u, int v, ll b, ll c) {
		add(u, v, c - b);
		D[u] -= b;
		D[v] += b;
	}
	ll bounded_flow() {
		int SS = n, TT = n + 1;
		ll base = 0;
		for(int i = 0; i < n; ++ i) {
			if (D[i] > 0) base += D[i];
			if (D[i] > 0) add(SS, i, D[i]);
			if (D[i] < 0) add(i, TT, -D[i]);
		}
		add(T, S, INF);
		int tmps = S, tmpt = T;
		n += 2; S = SS, T = TT;
		ll f = flow();
		n -= 2; S = tmps; T = tmpt;
		return f == base ? flow() : -1LL;
	}
};