#include <bits/stdc++.h>
using namespace std;

const int SA_SIZE = 200090;
const int logn = 1 + 19;
string s;
int sa[SA_SIZE], rk[SA_SIZE], lcp[SA_SIZE];
int tma[2][SA_SIZE], c[SA_SIZE];

void getsa() {
    int *x = tma[0], *y = tma[1], n = (int)s.size(), m = 200;
    for (int i = 0; i < m; ++i) c[i] = 0;
    for (int i = 0; i < n; ++i) c[ x[i] = s[i] ]++;
    for (int i = 1; i < m; ++i) c[i] += c[i - 1];
    for (int i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
    for (int k = 1; k <= n; k <<= 1) {
        for (int i = 0; i < m; ++i) c[i] = 0;
        for (int i = 0; i < n; ++i) c[ x[i] ]++;
        for (int i = 1; i < m; ++i) c[i] += c[i - 1];
        int p = 0;
        for (int i = n - k; i < n; ++i) y[p++] = i;
        for (int i = 0; i < n; ++i) {
            if (sa[i] >= k) y[p++] = sa[i] - k;
        }
        for (int i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
        y[ sa[0] ] = p = 0;
        for (int i = 1; i < n; ++i) {
            if (x[sa[i]] == x[sa[i - 1]] && sa[i] + k < n && sa[i - 1] + k < n && x[sa[i] + k] == x[sa[i - 1] + k]) ;
            else ++p;
            y[ sa[i] ] = p;
        }
        swap(x, y);
        if (p + 1 == n) break;
        m = p + 1;
    }
}

void getlcp() {
    int tmp = 0, n = s.size();
    for (int i = 0; i < n; ++i) rk[ sa[i] ] = i;
    for (int i = 0; i < n; ++i) {
        if (rk[i] == 0) lcp[0] = 0;
        else {
            if (tmp) tmp--;
            int po = sa[ rk[i] - 1 ];
            while (tmp + po < n && tmp + i < n && s[tmp + i] == s[tmp + po]) ++tmp;
            lcp[rk[i]] = tmp;
        }
    }
}
#define maxn 200900

string ss[30];
int n, k, l[maxn], r[maxn], p[maxn], b[maxn], cnt[30], rr[maxn];

int main () {
    if (fopen("spell.in", "r")) {
        freopen("spell.in", "r", stdin);
        freopen("spell.out", "w", stdout);
    }
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; ++ i) cin >> ss[i], s += ss[i], s += 'A' + i;

    if (n == 1) {
        n ++;
        ss[1] = ss[0];
        s += ss[1];
        s += 'B';

    }
        
    
    for (int i = 0, tmp = 0; i < s.size(); ++ i) {
        if (s[i] >= 'a' && s[i] <= 'z') b[i] = tmp;
        else tmp ++;
    }

    cin >> k;
    
    getsa();
    getlcp();
//    for (int i = 0; i < s.size(); ++ i) cout << rk[i] << " \n"[i + 1 == s.size()];
//    for (int i = 0; i < s.size(); ++ i) cout << sa[i] << " \n"[i + 1 == s.size()];
//    for (int i = 0; i < s.size(); ++ i) cout << lcp[i] << " \n"[i + 1 == s.size()];
//    for (int i = 0; i < s.size(); ++ i) {
//        int now = sa[i];
//        cout << "i: " << i << ", ";
//        cout << b[now] << " ";
//        for (int j = now; j < s.size(); ++ j) cout << s[j]; cout << endl;
//    }
    
    int pos = 0, kind = 0;

    multiset<int> cc;

    for (int i = 0; i < s.size(); ++ i) {
        int now = sa[i];
        if (s[now] < 'a' || s[now] > 'z') {
            pos = i + 1;
            continue;
        }
//        cout << "i: " << i << endl;

        while (kind != n && pos < s.size()) {
  //          cout << "pos: " << pos << endl;
            cc.insert(lcp[pos]);
            int add = b[sa[pos ++]];
            if (cnt[add]) kind --;
            cnt[add] ++;
            if (cnt[add]) kind ++;
        }
        if (kind != n) {
            p[i] = p[i - 1];
            continue;
        }
        
        cc.erase(cc.find(lcp[i]));
        
        r[i] = *cc.begin() - 1;
        rr[i] = r[i];

        if (i >= 1)
            l[i] = min(rr[i - 1] + 1, lcp[i]);

        if (l[i] > r[i]) l[i] = 0, r[i] = -1;

        p[i] = r[i] - l[i] + 1;

        if (i >= 1) p[i] += p[i - 1];
        
      //  cout << "l: " << l[i] << " " << "r: " << r[i] << "\n";
        if (cnt[b[now]]) kind --;
        cnt[b[now]] --;
        if (cnt[b[now]]) kind ++;

    //    cout << "exit: i = " << i << " kind: " << kind << "\n";
    }
    if (n == 2) {
//        if (ss[0].substr(0, 5) == "stosv") return 0;
    }
    while (k --) {
        int in, val; cin >> in;
//        cout << "now in: " << in << endl;
        int now = lower_bound(p, p + s.size(), in) - p;
        
//        cout << "[db] now: " << now << " " << p[now] << " " << p[now - 1] << "\n";
        if (now == 0) val = in;
        else val = in - p[now - 1];
//        cout << "[db] val: " << val << "\n";
        
        int len = l[now] + val;

//        cout << "[db] len: " << len << "\n";

        for (int i = 0; i < len; ++ i) {
            if (sa[now] + i >= s.size()) {
                cout << "RE" << endl;
                return 0;
            }
            cout << s[ sa[now] + i ];
        } cout << "\n";
    }
//    cout << "here" << endl;
 //   for (int i = 0; i < s.size(); ++ i)
 //       cout << p[i] << " \n"[i + 1 == s.size()];
}

