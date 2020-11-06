const KMP_SIZE = ;
struct KMP{
	string s;
	int f[KMP_SIZE] , pos;
	void solve(){
		f[0] = pos = -1;
        for (int i = 1; i < s.size(); ++ i) {
			while(pos != -1 && s[pos + 1] != s[i]) pos = f[pos];
			if(s[pos + 1] == s[i]) pos ++;
			f[i] = pos;
		}
	}
};
