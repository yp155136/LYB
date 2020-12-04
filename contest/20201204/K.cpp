#include <bits/stdc++.h>
using namespace std;

const int N = 1006;
const int M = 1006;

string s[N];
int n, m;

void f(char x, char y, char z, int n, vector<int> all) {
    if (all.size() == 1 || n == 0) {
        cout << all[0] << endl;
        return;
    }
    vector<int> v1, v2;
    for (int idx: all) {
        if (s[idx][n - 1] == s[ all[0] ][n - 1]) {
            v1.push_back(idx);
        }
        else {
            v2.push_back(idx);
        }
    }
    if (s[ all[0] ][n - 1] != x) {
        swap(v1, v2);
    }
    if (!v2.empty()) {
        f(z, y, x, n - 1, v2);
    }
    else {
        f(x, z, y, n - 1, v1);
    }
}

int main () {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    vector<int> all;
    for (int i = 1; i <= m; ++i) {
        cin >> s[i];
        all.push_back(i);
    }
    f('A', 'B', 'C', n, all);
}

