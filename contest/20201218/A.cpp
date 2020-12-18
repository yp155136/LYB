#include <bits/stdc++.h>
using namespace std;

const int N = 200006;
int a[N];

string s[N];
string s_same[N];
int w[N];
vector<int> v[N];

string rit_str;
int rit_ptr = 0;

int rit() {
    char c; int ret = 0;
    do {
        c = rit_str[rit_ptr++];
    } while (c < '0' || c > '9');
    do {
        ret = (ret << 1) + (ret << 3) + (c - '0');
        c = rit_str[rit_ptr++];
    } while ('0' <= c && c <= '9');
    return ret;
}

bool cmp(int a, int b) {
    if (w[a] != w[b]) {
        return w[a] > w[b];
    }
    else {
        if (s_same[a] != s_same[b]) return s_same[a] < s_same[b];
        else return s[a] < s[b];
    }
}

vector<int> ans[N];

int main () {
    if (fopen("army.in" ,"r")) {
        freopen("army.in", "r", stdin);
        freopen("army.out", "w", stdout);
    }
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    for (int i = 1; i <= m; ++i) {
        cin >> a[i];
    }
    string tmp; getline(cin, tmp);
    vector<int> perm;
    for (int i = 1; i <= n; ++i) {
        getline(cin, tmp);
        for (char c: tmp) {
            if (c == ' ') {
                if (s[i] != "") s[i].push_back(c);
            }
            else if ('0' <= c && c <= '9') {
                break;
            }
            else {
                s[i].push_back(c);
            }
        }
        while (s[i].back() == ' ') s[i].pop_back();
        s_same[i] = s[i];
        for (char &c: s_same[i]) {
            if (c <= 'Z' && c != ' ') {
                c = (c - 'A') + 'a';
            }
        }
        rit_str = tmp;
        rit_ptr = 0;
        w[i] = rit();
        int kk = rit();
        // cerr << "w[i] = " << w[i] << " , v = " << kk << endl;
        for (int j = 0; j < kk; ++j) {
            v[i].push_back(rit());
        }
        perm.push_back(i);
    }
    sort(perm.begin(), perm.end(), cmp);
    while (!perm.empty()) {
        vector<int> nxt;
        for (int i: perm) {
            // if (v[i].size() <= ptr) continue;
            for (int ptr = 0; ptr < v[i].size(); ++ptr) {
                if (ans[ v[i][ptr] ].size() < a[ v[i][ptr] ]) {
                    ans[ v[i][ptr] ].push_back(i);
                    break;
                }
            }
        }
        perm = nxt;
    }
    for (int i = 1; i <= m; ++i) {
        sort(ans[i].begin(), ans[i].end(), [](const int &x, const int &y) {
            // if (s_same[x] != s_same[y]) return s_same[x] < s_same[y];
            // else return s[x] < s[y];
            // return s_same[x] + s[x] < s_same[y] + s[y];
            for (int i = 0; i < min(s[x].size(), s[y].size()); ++i) {
                if (s_same[x][i] != s_same[y][i]) return s_same[x][i] < s_same[y][i];
                else if (s[x][i] != s[y][i]) return s[x][i] < s[y][i];
            }
            return s[x].size() < s[y].size();
        });
        for (int j: ans[i]) {
            cout << s[j] << endl;
        }
        if (i != m) cout << endl;
    }
}


