const int ZVALUE_SIZE = ;
struct Z_VALUE {
	string s;
	int l = 0, r = 0, z[ZVALUE_SIZE];
	void solve() {
		for (int i = 0; i < s.size(); ++i) {
			z[i] = max(min(z[i - l], r - i), 0 LL);
			while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) {
				l = i, r = i + z[i];
				z[i]++;
			}
		}
	}
};