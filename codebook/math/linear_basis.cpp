const int MAX_M = 500; //maximum number of variable
typedef bitset<MAX_M+1> bst;
struct linear_basis{
	int m;
	bst mat[MAX_M];
	linear_basis(int _m):m(_m){
		for(int i = 0; i < _m; ++ i) mat[i].reset();
	}
	// True means "No solution"
	int add_constraint(bst now) {
		for(int j = 0; j < m; ++ j) {
			if(now[j]){
				if(mat[j][j])   now ^= mat[j];
				else{
					mat[j] = now;
					for(int k = j + 1; k < m; ++ k)
						if(mat[j][k])
							mat[j] ^= mat[k];
					for(int k = 0; k < j; ++ k)
						if(mat[k][j])
							mat[k] ^= mat[j];
					return 0;
				}
			}
		}
		return now[m];
	}
	// get one possible solution
	bst get_ans() {
		bst rt; rt.reset();
		for(int i = 0; i < m; ++ i)
			if(mat[i][i] && mat[i][m])
				rt[i] = 1;
		return rt;
	}
};
/* usage : 
1. Init it with # of variables
2. Adding constraint with format x1,x2...,xm,C
3. get_ans return one possible solution
*/