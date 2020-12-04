#include <bits/stdc++.h>
using namespace std;

int n;
string s, ans;

int main() {
    cin.tie(0), cout.sync_with_stdio(0);
    cin >> n >> s;
    reverse(s.begin(), s.end());
    for (int i = 0; i < s.size(); ++ i) ans += "0";
    int pre = 0, mis = 0;
    for (int i = s.size() - 1; i >= 0; -- i) {
        int now = pre + (s[i] - '0') - mis;
        pre = 0;
        if (now < 0) {
            if ((-now) % 2 == 0) pre = (-now) / 2;
            if ((-now) % 2 == 1) pre = (-now) / 2 + 1;
            pre = -pre;
            now %= 2;
        }
        if (now) ans[i] = '1', mis ++;
//        cout << "mis: " << mis << " pre: " << pre << "\n";
    }
    reverse(ans.begin(), ans.end());
    cout << ans << "\n";
    return 0;
}
