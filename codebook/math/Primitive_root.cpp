// build_phi, power, eb
// M has primitive root when M = 2, 4, p^n, 2p^n
ll Primitive_root(ll n) {
	if (n == 2) return 1;
	vector<ll> sol;
	ll val = phi[n];
	for (ll i = 2; i * i <= val; ++i) {
		if (val % i == 0) {
			sol.eb(i);
			while (val % i == 0) val /= i;
		}
	}
	if (val != 1) sol.eb(val);
	for (ll i = 2; i < n; ++i) {
		if (__gcd(i, n) != 1) continue;
		ll ok = 1;
		for (auto to: sol) {
			if (power(i, phi[n] / to, n) == 1) {
				ok = 0;
				break;
			}
		}
		if (ok)
			return i;
	}
	return -1;
}