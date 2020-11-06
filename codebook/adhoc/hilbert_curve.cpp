// soring Mo's with hilbert(nn, L, R) can be faster !!
// needed: nn >= n, no need to change n, nn = 2^k
// usage: sort (ql_i, qr_i) by hilbert(nn, ql_i, qr_i)
ll hilbert(int nn, int x, int y) {
	ll res = 0;
	for (int s = nn / 2; s; s >>= 1) {
		int rx = (x & s) > 0;
		int ry = (y & s) > 0;
		res += s * 1ll * s * ((3 * rx) ^ ry);
		if (ry == 0) {
			if (rx == 1) {
				x = s - 1 - x;
				y = s - 1 - y;
			}
			swap(x, y);
		}
	}
	return res;
}