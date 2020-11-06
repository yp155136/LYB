void build_phi(int ax[], int n) {
	for (int i = 1; i <= n; ++i)
		ax[i] = i;
	for (int i = 1; i <= n; ++i)
		for (int j = i + i; j <= n; j += i)
			ax[j] -= ax[i];
}
void build_mu(int ax[], int n) {
	for (int i = 1; i <= n; ++i)
		ax[i] = 0;
	ax[1] = 1;
	for (int i = 1; i <= n; ++i)
		for (int j = i + i; j <= n; j += i)
			ax[j] -= ax[i];
}