// isPrime (miller rabin)
map < ll, int > cnt;
void PollardRho(ll n) {
	if (n == 1) return;
	if (isPrime(n)) return ++cnt[n], void();
	if (n % 2 == 0) return PollardRho(n / 2), ++cnt[2], void();
	ll x = 2, y = 2, d = 1, p = 1;
	auto f = [ & ](auto x, auto n, int p) {
		return (mul(x, x, n) + p) % n;
	}
	while (true) {
		if (d != n && d != 1) {
			PollardRho(n / d);
			PollardRho(d);
			return;
		}
		if (d == n) ++p;
		x = f(x, n, p);
		y = f(f(y, n, p), n, p);
		d = __gcd(abs(x - y), n);
	}
}