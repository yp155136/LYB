#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int N = 62;

ll d[N];

int main () {
    int n, m; scanf("%d%d", &n, &m);
    vector<int> idx;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &d[i]);
        idx.push_back(i);
    }
    sort(idx.begin(), idx.end(), [](const int &x, const int &y) {
        return d[x] < d[y];
    });
    vector<pii> ans;
    for (int i = 0; i < n; ++i) {
        int _ = idx[i];
        ll tar = d[_];
        if (tar == 0) {
            if (_ == m) ++d[_];
        }
        else {
            for (int j = i - 1; j >= 0; --j) {
                int __ = idx[j];
                if (tar >= d[__]) {
                    tar -= d[__];
                    ans.push_back({__, _});
                }
            }
        }
    }
    cout << ans.size() << endl;
    for (auto i: ans) {
        cout << i.first << ' ' << i.second << endl;
    }
}

