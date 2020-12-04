#include <bits/stdc++.h>
using namespace std;

int main () {
    int n; cin >> n;
    n >>= 1;
    set<int> st;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            st.insert(i);
            st.insert(n / i);
        }
    }
    vector<int> v;
    for (int i: st) v.push_back(i);
    int nn = (int)v.size();
    cout << nn << endl;
    for (int i = 0 ; i < nn; ++i) {
        cout << v[i] << " \n"[i == nn - 1];
    }
}

