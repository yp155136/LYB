// sz_lim, MAX, MAX_len
int res[MAX], aux[MAX_len];
void db(int t, int p, int len, int k, int &sz) {
    if (sz >= sz_lim) return;
    if (t > len) {
        if (len % p == 0) {
            for (int i = 1; i <= p && sz < sz_lim; ++i) res[sz++] = aux[i];
        }
    } else {
        aux[t] = aux[t - p];
        db(t + 1, p, len, k, sz);
        for (int i = aux[t - p] + 1; i < k; ++i) {
            aux[t] = i;
            db(t + 1, t, len, k, sz);
        }
    }
}
// return cyclic string such that every string of length len using k character appears as a substring.
int de_bruijn(int k, int len) {
    if (k == 1) {
        res[0] = 0;
        return 1;
    }
    for (int i = 0; i < k * len; i++) aux[i] = 0;
    int sz = 0;
    db(1, 1, len, k, sz);
    return sz; // k^n
}
