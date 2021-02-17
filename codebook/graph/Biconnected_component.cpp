int low[N], dfn[N];
bool vis[N];
int e[M], x[M], y[M]; // e[i] = x[i] ^ y[i]
int stamp, bcc_no = 0;

vector<int> G[N], bcc[N];
stack<int> sta;

void dfs(int now, int par_eid) {
	vis[now] = true;
	dfn[now] = low[now] = (++stamp);
	for (int i : G[now]) {
		if (i == par_eid) continue;
		int to = (e[i] ^ now);
		if (!vis[to]) {
			sta.push(i); dfs(to, i);
			low[now] = min(low[now], low[to]);
			if (low[to] >= dfn[now]) {
				++bcc_no; int p; // p is edge index
				do {
					p = sta.top(); sta.pop();
					bcc[bcc_no].push_back(p);
				} while (p != i);
			}
		}
		else if (dfn[to] < dfn[now]) {
			sta.push(i);
			low[now] = min(low[now], dfn[to]);
		}
	}
}
