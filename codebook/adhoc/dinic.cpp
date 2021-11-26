struct Dinic {
  struct Edge {
    int to, cap, rev; 
    Edge(int _to, int _cap, int _rev): to(_to), cap(_cap), rev(_rev){}
  };
  vector<Edge> G[N];
  void add_edge(int from, int to, int cap) {
    G[from].push_back(Edge(to, cap, (int)G[to].size()));
    G[to].push_back(Edge(from, 0, (int)G[from].size() - 1));
  }
  int n, s, t;
  int dfs(int now, int flow) {
    if (now == t) return flow;
    for (int &i = iter[now]; i < (int)G[now].size(); ++i) {
      Edge &e = G[now][i];
      if (e.cap > 0 && level[e.to] == level[now] + 1) {
        int ret = dfs(e.to, min(flow, e.cap));
        if (ret > 0) {
          e.cap -= ret;
          G[e.to][e.rev].cap += ret;
          return ret;
        }
      }
    }
    return 0;
  }
  int flow() {
    int ret = 0;
    while (true) {
      bfs();
      if (level[t] == -1) break;
      memset(iter, 0, sizeof(iter));
      int tmp;
      while ((tmp = dfs(s, INF)) > 0) {
        ret += tmp;
      }
    }
    return ret;
  }
} flow;
