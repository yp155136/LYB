#define is_neg(_k) (_k.Y < 0 || (_k.Y == 0 && _k.X < 0))
bool cmp(pll a,pll b) {
	int A = is_neg(a), B = is_neg(b);
	return (A == B ? (a ^ b) > 0 : A < B);
}
