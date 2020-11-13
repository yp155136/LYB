typedef pair<double, double> pdd;
#define F first
#define S second

int n;
pdd a[maxn];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

double dis(pdd p1, pdd p2) {
	return hypot(p1.F - p2.F, p1.S - p2.S);
}
inline double sq(double x) {
	return x * x;
}
pdd external(pdd p1, pdd p2, pdd p3) {
	double a1 = p1.F - p2.F, a2 = p1.F - p3.F;
	double b1 = p1.S - p2.S, b2 = p1.S - p3.S;

	double c1 = (sq(p1.F) - sq(p2.F) 
						 + sq(p1.S) - sq(p2.S)) / 2;
	double c2 = (sq(p1.F) - sq(p3.F) 
						 + sq(p1.S) - sq(p3.S)) / 2;
	double dd = a1 * b2 - a2 * b1;
	return make_pair((c1 * b2 - c2 * b1) / dd
								 , (a1 * c2 - a2 * c1) / dd);
}
int main() {
	cin >> n;
	for (int i = 0; i < n; ++ i)
		cin >> a[i].F >> a[i].S;
	shuffle(a, a + n, rng);

	pdd center = a[0];
	double r = 0;

	for (int i = 0; i < n; ++ i) {
		if (dis(center, a[i]) <= r) continue;
		center = a[i], r = 0;
		for (int j = 0; j < i; ++ j) {
			if (dis(center, a[j]) <= r) continue;
			center.F = (a[i].F + a[j].F) / 2;
			center.S = (a[i].S + a[j].S) / 2;
			r = dis(center, a[i]);
			for (int k = 0; k < j; ++ k) {
				if (dis(center, a[k]) <= r) continue;
				center = external(a[i], a[j], a[k]);
				r = dis(center, a[i]);
			}
		}
	}

	cout << fixed << setprecision(10) << r << endl;
	cout << center.F << " " << center.S << "\n";
	return 0;
}

