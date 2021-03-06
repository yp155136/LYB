const int MAX = 1050;
const int INF = 0x3f3f3f3f;
struct DLX{
	int n, sz, s[MAX];
	int row[MAX * 100], col[MAX * 100];
	int l[MAX * 100], r[MAX * 100], u[MAX * 100], d[MAX * 100];
	int ans;
	void init(int n) {
		this -> n = n;
		ans = INF;
		for (int i = 0; i <= n; ++ i) {
			u[i] = d[i] = i;
			l[i] = i - 1;
			r[i] = i + 1;
		}
		r[n] = 0, l[0] = n;
		sz = n + 1;
		memset(s, 0, sizeof s);
	}
	void AddRow(int rr, vector<int> sol) {
		int tmp = sz;
		for (auto to : sol) {
			l[sz] = sz - 1;
			r[sz] = sz + 1;
			d[sz] = to;
			u[sz] = u[to];
			d[u[to]] = sz, u[to] = sz;
			row[sz] = rr, col[sz] = to;
			s[to] ++, sz ++;
		}
		r[sz - 1] = tmp, l[tmp] = sz - 1;
	}
#define FOR(i, way, to) for (int i = way[to]; i != to; i = way[i])
	void remove(int c) {
		l[r[c]] = l[c];
		r[l[c]] = r[c];
		FOR(i, d, c) FOR(j, r, i) {
			u[d[j]] = u[j];
			d[u[j]] = d[j];
			--s[col[j]];
		}
	}
	int restore(int c) {
		FOR(i, u, c) FOR(j, l, i) {
			++s[col[j]];
			u[d[j]] = j;
			d[u[j]] = j;
		}
		l[r[c]] = c;
		r[l[c]] = c;
	}
	void DFS(int floor) {
		if (r[0] == 0) {
			ans = min(ans, floor);
			return;
		}
		if (floor >= ans) return;
		int c = r[0];
		FOR(i, r, 0) if (s[i] < s[c]) c = i;
		remove(c);
		FOR(i, d, c) {
			FOR(j, r, i) remove(col[j]);
			DFS(floor + 1);
			FOR(j, l, i) restore(col[j]);
		}
		restore(c);
	}
} solver;
int n, m;
int main() {
	while (cin >> n >> m) {
		solver.init(m);
		for (int i = 0; i < n; ++ i) {
			int nn, in;
			cin >> nn;
			vector<int> sol;
			for (int j = 0; j < nn; ++ j)
				cin >> in, sol.emplace_back(in);
			solver.AddRow(i, sol);
		}
		solver.DFS(0);
		if (solver.ans == INF) cout << "No" << endl;
		else cout << solver.ans << endl;
	}
}