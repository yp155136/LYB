#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vint;
vector<int> pre;

int n, k, t;

vector<vint> go(int now, int left) {
    // cerr << "now = " << now << " , left = " << left << endl;
    if (left == 0) {
        vector<vint> ret;
        ret.push_back(pre);
        return ret;
    }
    if ((n - now + 1) < left) return {};
    if (now == n + 1) return {};
    pre.push_back(now);
    vector<vint> ret1 = go(now + 1, left - 1);
    pre.pop_back();
    vector<vint> ret2 = go(now + 1, left);
    reverse(ret2.begin(), ret2.end());
    vector<vint> ret;
    for (auto v1: ret1) ret.push_back(v1);
    for (auto v2: ret2) ret.push_back(v2);
    if (ret.size() >= t) {
        cout << t << endl;
        for (int i = 0; i < t; ++i) {
            for (int j = 0; j < k; ++j) {
                cout << ret[i][j] << " \n"[j == k - 1];
            }
        }
        exit(0);
    }
    return ret;
}

int main () {
    cin >> n >> k >> t;
    ll v = 1;
    for (int i = k + 1; i <= n; ++i) {
        v *= i;
        v /= (i - k);
        if (v >= t) {
            n = i;
            break;
        }
    }
    vector<vint> ret = go(1, k);
    /*for (auto i: ret) {
        for (auto j: i) cout << j << ' ';
        cout << endl;
    }*/
    cout << 0 << endl;
}

