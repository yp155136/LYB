void build_partition(int _dp[], int n, int mod){
	_dp[0] = 1;
	for(int i = 1 ; i <= n; ++ i){
		for(int j = 1; j <= n; ++ j){
			int tmp = j * (j * 3 - 1) / 2;
			if(tmp > i) break;
			else if(j % 2 == 1) _dp[i] = (_dp[i] + _dp[i - tmp]) % mod;
			else if(j % 2 == 0) _dp[i] = (_dp[i] - _dp[i - tmp] + mod) % mod;
		}
		for(int j = 1; j <= n; ++ j){
			int tmp = j * (j * 3 + 1) / 2;
			if(tmp > i) break;
			else if(j % 2 == 1) _dp[i] = (_dp[i] + _dp[i - tmp]) % mod;
			else if(j % 2 == 0) _dp[i] = (_dp[i] - _dp[i - tmp] + mod) % mod;
		}
	}
	return;
}