struct Cost_Flow {
	struct Edge {
		int to, cap, rev, cost;
		Edge(int _to, int _cap, int _rev, int _cost): to(_to), cap(_cap), rev(_rev), cost(_cost) {}
	};
	vector<Edge> G[N];
	void add_edge(int from, int to, int cap, int cost) {
		G[from].push_back(Edge(to, cap, (int)G[to].size(), cost));
		G[to].push_back(Edge(from, 0, (int)G[from].size() - 1, -cost));
	}
	int n, s, t;
	void init(int _n, int _s, int _t) {
		n = _n, s = _s, t = _t;
		for (int i = 0; i <= n; ++i) {
			G[i].clear();
		}
	}
	bool in_que[N];
	int dis[N], par[N], par_id[N];
	pair<int, int> flow() {
		int flow = 0, cost = 0;
		while (true) {
			for (int i = 0; i <= n; ++i) {
				dis[i] = INF, in_que[i] = false;
			}
			queue<int> que; que.push(s);
			dis[s] = 0;
			while (!que.empty()) {
				int t = que.front(); que.pop();
				int ptr = 0;
				in_que[t] = false;
				for (Edge e: G[t]) {
					if (e.cap > 0) {
						if (dis[e.to] > dis[t] + e.cost) {
							dis[e.to] = dis[t] + e.cost;
							par[e.to] = t, par_id[e.to] = ptr;
							if (!in_que[e.to]) {
								que.push(e.to);
								in_que[e.to] = true;
							}
						}
					}
					++ptr;
				}
			}
			if (dis[t] == INF) break;
			int mn_flow = INF;
			for (int i = t; i != s; i = par[i]) {
				mn_flow = min(mn_flow, G[ par[i] ][ par_id[i] ].cap);
			}
			flow += mn_flow;
			cost += mn_flow * dis[t];
			for (int i = t; i != s; i = par[i]) {
				G[ par[i] ][ par_id[i] ].cap -= mn_flow;
				G[ i ][ G[ par[i] ][ par_id[i] ].rev ].cap += mn_flow;
			}
		}
		return make_pair(flow, cost);
	}
} flow;
