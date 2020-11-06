// ax + by = gcd(a, b)
ll exgcd(ll a, ll b, ll & x, ll & y) {
    if (a == 0) return x = 0, y = 1, b;
    ll g = exgcd(b % a, a, y, x);
    x -= b / a * y;
    return g;
}