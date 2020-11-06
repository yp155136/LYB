#include <bits/stdc++.h>
using namespace std;

const int N = 30006;
const int K = 177; //一個樹塊中至多有 K 個點

int w[N], sum[N], mx[N];
int root[N], sz[N], fa[N], dep[N];
vector<int> G[N], T[N]; // T 存著樹塊中的邊
// root[i] 紀錄點 i 所位於的樹塊的根，
// sum[i], mx[i] 分別存 i 到樹根的和、最大值

void dfs1(int now, int par, int depth) {
	fa[now] = par; dep[now] = depth;
	if (!root[now]) { // 不屬於任何樹塊，那就把自己當根
		root[now] = now;
		sz[now] = 1;
	}
	for (int i = 0; i < (int)G[now].size(); ++i) {
		int to = G[now][i];
		if (to == par) continue;
		if (sz[ root[now] ] + 1 < K) { 
			// 如果把 now 加入樹塊還不會超過限制的話就加入
			T[now].push_back(to);
			root[to] = root[now];
			++sz[ root[now] ];
		}
		dfs1(to, now, depth + 1);
	}
}

void dfs2(int now, int pre_sum, int pre_mx) {
	// 計算這個樹塊的 mx, sum
	sum[now] = pre_sum, mx[now] = pre_mx;
	for (int i = 0; i < (int)T[now].size(); ++i) {
		int to = T[now][i];
		dfs2(to, pre_sum + w[to], max(pre_mx, w[to]));
	}
}

void change(int pos, int val) {
	w[pos] = val;
	dfs2(root[pos], w[ root[pos] ], w[ root[pos] ]);
	// 這邊偷懶每次都從樹根開始更新，可以只從 pos 下去更新
}

void qmax(int u, int v) {
	// 這邊跟下面的 qsum 很像，就留給讀者做練習了
}

void qsum(int u, int v) {
	int ans = 0;
	while (u != v) {
		if (root[u] == root[v]) {
			// 位於同一個樹塊，就慢慢往上爬
			if (dep[u] < dep[v]) swap(u, v);
			ans += w[u];
			u = fa[u];
		}
		else {
			// 位於不同樹塊，就讓較深的人一次往上跳一塊
			if (dep[ root[u] ] < dep[ root[v] ]) swap(u, v);
			ans += sum[u];
			u = fa[ root[u] ];
		}
	}
	ans += w[u]; // 最後記得加上 LCA 的答案
	printf("%d\n", ans);
}
