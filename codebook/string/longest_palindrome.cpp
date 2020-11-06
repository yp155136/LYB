const int PALINDROME_MAX = 2 * ;
struct Palindrome {
	string s, ss; // ss = input
	int z[PALINDROME_MAX];
	void solve() {
		s.resize(ss.size() + ss.size() + 1, '.');
		for (int i = 0; i < ss.size(); ++i)
			s[i + i + 1] = ss[i];
		int l = 0, r = 0;
		for (int i = 0; i < s.size(); ++i) {
			z[i] = max(min(z[l + l - i], r - i), 1);
			while (i - z[i] >= 0 && i + z[i] < s.size() && s[i - z[i]] == s[i + z[i]]) {
				l = i, r = i + z[i];
				z[i]++;
			}
		}
	}
};