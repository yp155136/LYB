const int SA_SIZE = ;
const int logn = 1 + ;
string s;
int sa[SA_SIZE], rk[SA_SIZE], lcp[SA_SIZE];
int tma[2][SA_SIZE], c[SA_SIZE], sp[SA_SIZE][logn];
 
int getsa() {
	-> update m = ? // how many char
	int *x = tma[0], *y = tma[1], n = s.size(), m = 200;
	for (int i = 0; i < m; ++ i) c[i] = 0;
	for (int i = 0; i < n; ++ i) c[x[i] = s[i]] ++;
	for (int i = 1; i < m; ++ i) c[i] += c[i - 1];
	for (int i = n - 1; i >= 0; -- i) sa[--c[x[i]]] = i;
	for(int k = 1; k <= n; k <<= 1) {
		for (int i = 0; i < m; ++ i) c[i] = 0;
		for (int i = 0; i < n; ++ i) c[x[i]] ++;
		for (int i = 1; i < m; ++ i) c[i] += c[i - 1];
		int p = 0;
		for (int i = n - k; i < n; ++ i) y[p ++] = i;
		for (int i = 0; i < n; ++ i) if(sa[i] >= k) y[p ++] = sa[i] - k;
		for (int i = n - 1; i >= 0; -- i) sa[--c[x[y[i]]]] = y[i];
		y[sa[0]] = p = 0;
		for (int i = 1; i < n; ++ i) {
			if( x[sa[i]] == x[sa[i - 1]] && sa[i] + k < n && sa[i - 1] + k < n &&
				x[sa[i] + k] == x[sa[i - 1] + k] );
			else p ++;
			y[sa[i]] = p;
		}
		swap(x, y);
		if(p + 1 == n) break;
		m = p + 1;
	}
}
void getlcp() {
	int tmp = 0, n = s.size();
	for (int i = 0; i < n; ++ i) rk[sa[i]] = i;
	for (int i = 0; i < n; ++ i) {
		if(rk[i] == 0) lcp[0] = 0;
		else {
			if(tmp) tmp --;
			int po = sa[rk[i] - 1];
			while(tmp + po < n && tmp + i < n && s[tmp + i] == s[tmp + po]) tmp ++;
			lcp[rk[i]] = tmp;
		}
	}
}
void getsp() {
	int n = s.size();
	for (int i = 0; i < n; ++ i) sp[rk[i]][0] = s.size() - i;
	for (int i = 1; i < n; ++ i) sp[i - 1][1] = lcp[i];
	for (int i = 2; i < logn; ++ i) {
		for (int j = 0; j < n; ++ j) {
			if(j + (1 << (i - 2)) >= s.size()) continue;
			sp[j][i] = min(sp[j][i - 1], sp[j + (1 << (i - 2))][i - 1]);
		}
	}
}
int Query(int L, int R) {
	int tmp = (L == R) ? 0 : 32 - __builtin_clz(R - L);
	if(tmp == 0) return sp[L][0];
	else return min(sp[L][tmp], sp[R - (1 << (tmp - 1))][tmp]);
}
int Find(string ss) {
	int L = 0, R = s.size(), now;
	while(R - L > 1) {
		now = (L + R) / 2;
		if(s[sa[now]] == ss[0]) break;
		else if(s[sa[now]] > ss[0]) R = now;
		else if(s[sa[now]] < ss[0]) L = now;
	}
	if(s[sa[now]] != ss[0]) return 0;
	for (int i = 1; i < ss.size(); ++ i) {
		int pre = now, ty = 0;
		if(sa[now] + i >= s.size()) L = now, ty = 0;
		else if(s[sa[now] + i] == ss[i]) continue;
		else if(s[sa[now] + i] > ss[i]) R = now, ty = 1;
		else if(s[sa[now] + i] < ss[i]) L = now, ty = 0;
 
		while(R - L > 1) {
			now = (L + R) / 2;
			if(sa[now] + i >= s.size()) {
				if(ty == 0) R = now;
				if(ty == 1) L = now;
			}
			else if(ty == 0 && Query(pre, now) < i) R = now;
			else if(ty == 1 && Query(now, pre) < i) L = now;
			else if(s[sa[now] + i] == ss[i]) break;
			else if(s[sa[now] + i] > ss[i]) R = now;
			else if(s[sa[now] + i] < ss[i]) L = now;
		}
		if(sa[now] + i >= s.size()) return 0;
		if(s[sa[now] + i] != ss[i]) return 0;
	}
	L = now, R = now;
	for (int i = 19; i >= 0; -- i) {
		if(R + (1 << i) >= s.size()) continue;
		else if(Query(L, R + (1 << i)) >= ss.size()) R += (1 << i);
	}
	for (int i = 19; i >= 0; -- i) {
		if(L - (1 << i) < 0) continue;
		else if(Query(L - (1 << i), R) >= ss.size()) L -= (1 << i);
	}
	return R - L + 1;
}
/*
how to use :
1. cin >> s;
2. getsa(), getlcp(), getsp();
3. string ss;
4. cin >> ss;
5. cout << Find(ss) << endl;
*/

