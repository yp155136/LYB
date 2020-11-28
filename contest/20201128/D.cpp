#include <bits/stdc++.h>
using namespace std;

struct Treap {
    Treap *lc, *rc;
    int key, pri, sz;
    Treap(int _key): lc(NULL), rc(NULL), key(_key), pri(rand()), sz(1){}
};

int Sz(Treap* t) {
    return t ? t->sz : 0;
}

void pull(Treap* t) {
    if (!t) return;
    t->sz = Sz(t->lc) + Sz(t->rc) + 1;
}

Treap* merge(Treap* a, Treap* b) {
    if (!a || !b) return a ? a : b;
    else if (a->pri > b->pri) {
        a->rc = merge(a->rc, b);
        pull(a);
        return a;
    }
    else {
        b->lc = merge(a, b->lc);
        pull(b);
        return b;
    }
}

void split(Treap* t, int k, Treap* &a, Treap* &b) {
    if (!t) a = b = NULL;
    else if (Sz(t->lc) + 1 <= k) {
        a = t;
        split(t->rc, k - Sz(t->lc) - 1, a->rc, b);
        pull(a);
    }
    else {
        b = t;
        split(t->lc, k, a, b->lc);
        pull(b);
    }
}

const int N = 200006;

vector<int> v[N];

Treap *odd, *even;
int pos[N];

int main () {
    srand(880301);
    int h, w, n; scanf("%d%d%d", &h, &w, &n);
    odd = even = NULL;
    for (int i = 1; i <= w; ++i) {
        if (i % 2 == 0) {
            even = merge(even, new Treap(i));
        }
        else {
            odd = merge(odd, new Treap(i));
        }
    }
    for (int i = 1; i <= n; ++i) {
        int a, b; scanf("%d%d", &a, &b);
        v[a].push_back(b);
    }
    for (int i = 1; i <= h; ++i) {
        if (i % 2 == 1) {
            swap(odd, even);
            for (int b: v[i]) {
                int _ = b / 2 + 1;
                Treap *tl1, *tr1;
                Treap *tl2, *tr2;
                split(odd,  _ - 1, tl1, odd); split(odd, 1, odd, tr1);
                split(even, _ - 1, tl2, even); split(even, 1, even, tr2);
                Treap *tmp1 = merge(tl1, merge(even, tr1));
                Treap *tmp2 = merge(tl2, merge(odd, tr2));
                odd = tmp1;
                even = tmp2;
            }
        }
        else {
            Treap *tl, *tr;
            split(odd, 1, tl, odd);
            split(even, w / 2 - 1, even, tr);
            Treap *tmp1 = merge(tl, even);
            Treap *tmp2 = merge(odd, tr);
            odd = tmp1;
            even = tmp2;
            for (int b: v[i]) {
                int _ = b / 2 + 1;
                Treap *tl1, *tr1;
                Treap *tl2, *tr2;
                split(odd,  _ - 1, tl1, odd); split(odd, 1, odd, tr1);
                split(even, _ - 2, tl2, even); split(even, 1, even, tr2);
                Treap *tmp1 = merge(tl1, merge(even, tr1));
                Treap *tmp2 = merge(tl2, merge(odd, tr2));
                odd = tmp1;
                even = tmp2;
            }
            // cerr << "here" << endl;
        }
    }
    for (int i = 1; i <= w; ++i) {
        Treap *t;
        if (i % 2 == 1) split(odd, 1, t, odd);
        else split(even, 1, t, even);
        // printf("%d\n", t->key);
        pos[ t->key ] = i;
    }
    for (int i = 1; i <= w; ++i) {
        printf("%d%c", pos[i], "\n\n"[i == w]);
    }
}

