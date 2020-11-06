const int ZVALUE_SIZE = ;
struct Z_VALUE{
    string s;
    int l = 0 , r = 0 , z[ZVALUE_SIZE];
    void solve(){
        REP(i , 0 , s.size()){
            z[i] = max(min(z[i - l] , r - i) , 0LL);
            while(i + z[i] < s.size() && s[z[i]] == s[i + z[i]]){
                l = i , r = i + z[i];
                z[i] ++;
            }
        }
    }
};
