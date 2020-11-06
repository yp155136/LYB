// power
int DiscreteLog_with_s(int s, int x, int y, int m) {
    int kStep = max((int)sqrt(m), 10);
    unordered_map<int, int> p;
    int b = 1;
    for (int i = 0; i < kStep; ++i) {
        p[y] = i;
        y = 1LL * y * x % m;
        b = 1LL * b * x % m;
    }
    for (int i = 0; i < m + 10; i += kStep) {
        s = 1LL * s * b % m;
        if (p.find(s) != p.end()) return i + kStep - p[s];
    }
    return -1;
}
int DiscreteLog(int x, int y, int m) {
    // x ^ ? === y % m
    if (m == 1) return 0;
	// y %= m;
    int s = 1;
    for (int i = 0; i < 70; ++i) {
        if (s == y) return i;
        s = 1LL * s * x % m;
    }
    if (s == y) return 70;
    int p = 70 + DiscreteLog_with_s(s, x, y, m);
    if (power(x, p, m) != y) return -1;
    return p;
}
