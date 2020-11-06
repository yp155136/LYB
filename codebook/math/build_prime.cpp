// MAX, eb
void build_prime(int min_fc[], vector<int> &P){
    for(int i = 2; i < MAX; ++ i){
        if(min_fc[i] == 0) min_fc[i] = i , P.eb(i);
        for(auto j : P){
            if(i * j >= MAX) break;
            min_fc[i * j] = j;
            if(i % j == 0) break;
        }
    }
}
