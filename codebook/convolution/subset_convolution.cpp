for(int i = 0; i <= n; ++ i) {
	// f[__builtin_popcount(s)][s] = s, otherwise = 0. So is g[i]
	FWT(f[i], n) // OR
	FWT(g[i], n) // OR
	for(int s = 0; s < (1 << n); ++ s)
		for(int j = 0; j <= i; ++ j)
			h[i][s] += f[j][s] * g[i - j][s]
	IFWT(h[i], n) // OR
	for(int s = 0; i < (1 << n); ++ s)
		h[__builtin_popcount(s)][s] // is the real answer
}