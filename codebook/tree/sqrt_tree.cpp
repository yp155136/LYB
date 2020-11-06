#include <bits/stdc++.h>

using namespace std;

const int N = 30006;
const int K = 177;

int w[N], sum[N], mx[N];
int root[N], sz[N], fa[N], dep[N];
vector<int> G[N], T[N];

void dfs1(int now, int par, int depth) {
	fa[now] = par;
	dep[now] = depth;
	if (!root[now]) {
		root[now] = now;
		sz[now] = 1;
	}
	for (int i = 0; i < (int) G[now].size(); ++i) {
		int to = G[now][i];
		if (to == par) continue;
		if (sz[root[now]] + 1 < K) {
			T[now].push_back(to);
			root[to] = root[now];
			++sz[root[now]];
		}
		dfs1(to, now, depth + 1);
	}
}

void dfs2(int now, int pre_sum, int pre_mx) {
	sum[now] = pre_sum, mx[now] = pre_mx;
	for (int i = 0; i < (int) T[now].size(); ++i) {
		int to = T[now][i];
		dfs2(to, pre_sum + w[to], max(pre_mx, w[to]));
	}
}

void change(int pos, int val) {
	w[pos] = val;
	dfs2(root[pos], w[root[pos]], w[root[pos]]);
}

void qmax(int u, int v) {
	// TODO
}

void qsum(int u, int v) {
	int ans = 0;
	while (u != v) {
		if (root[u] == root[v]) {
			if (dep[u] < dep[v]) swap(u, v);
			ans += w[u];
			u = fa[u];
		} else {
			if (dep[root[u]] < dep[root[v]]) swap(u, v);
			ans += sum[u];
			u = fa[root[u]];
		}
	}
	ans += w[u];
	printf("%d\n", ans);
}