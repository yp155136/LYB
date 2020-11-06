//MAXN
const int N = 26;
struct Palindromic_Tree {
	int next[MAXN][N];//trie tree edge
	int len[MAXN];//tree edge depth*2 (-1)
	int fail[MAXN];//fail link
	int num[MAXN];//fail link depth
	int cnt[MAXN];//# of this Palindrom
	int S[MAXN];//string
	int p;//# of different Palindrom + 2
	int n;//string len
	int last;
	int newnode(int l) {
		memset(next[p], 0, N * 4);
		cnt[p] = num[p] = 0;
		len[p] = l;
		return p ++;
	}
	void init() {
		p = n = 0;
		last = 1;
		newnode (0);
		newnode (-1);
		S[n] = -1;
		fail[0] = 1;
	}
	int get_fail(int x){
		while (S[n - len[x] - 1] != S[n]) x = fail[x];
		return x;
	}
	void add(int c) {	
		c -= 'a';
		S[++ n] = c;
		int cur = get_fail ( last );
		if ( !next[cur][c] ){
			int now = newnode ( len[cur] + 2 );
			fail[now] = next[get_fail ( fail[cur] )][c];
			next[cur][c] = now;
			num[now] = num[fail[now]] + 1;
		}
		last = next[cur][c];
		cnt[last] ++;
	}
	void count () {
		for (int i = p - 1; i >= 0; -- i) cnt[fail[i]] += cnt[i];
	}
};
