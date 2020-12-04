#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node *lc, *rc;
    int val;
    Node(): lc(NULL), rc(NULL), val(0){}
    void pull() {
        val = __gcd(lc->val, rc->val);
    }
};

const int N = 100006;
int a[N];

Node* Build(int L, int R) {
    Node* node = new Node();
    if (L == R) {
        node->val = a[L];
        return node;
    }
    int mid = (L + R) >> 1;
    node->lc = Build(L, mid);
    node->rc = Build(mid + 1, R);
    node->pull();
    return node;
}

int query(Node* node, int L, int R, int l, int r) {
    if (l > R || L > r) return 0;
    else if (l <= L && R <= r) {
        return node->val;
    }
    int mid = (L + R) >> 1;
    return __gcd(query(node->lc, L, mid, l, r), query(node->rc, mid + 1, R, l, r));
}

string s[N];
int val[N];

int main () {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    int _ = 0;
    int _1 = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        if (s[i][0] == '+') {
            _++;
            string s1 = "";
            for (int j = 1; j < s[i].size(); ++j) {
                a[_] *= 10;
                a[_] += (s[i][j] - '0');
            }
            val[i] = a[_];
        }
    }
    Node* root = Build(1, _);
    int l = 1, r = 0;
    multiset<int> st;
    for (int i = 1; i <= n; ++i) {
        if (s[i][0] == '+') {
            ++r;
            _1 += (a[r] == 1);
            st.insert(a[r]);
        }
        else if (s[i] == "-") {
            st.erase(st.find(a[l]));
            _1 -= (a[l] == 1);
            ++l;
        }
        else {
            int ret = query(root, 1, _, l, r);
            if (st.empty() || ret != *st.begin()) cout << 'N' << '\n';
            else cout << 'Y' << ret << '\n';
            // cout << query(root, 1, _, l, r) << '\n';
        }
    }
}

