// Compile with "g++ -std=c++11 -Wall -Wextra -Wconversion -Wshadow -fsanitize=undefined -Dlawfung"
#ifdef lawfung
#define debug(...) do {\
	fprintf(stderr, "%s - %d : (%s) = ", __PRETTY_FUNCTION__, __LINE__, #__VA_ARGS__);\
	_DO(__VA_ARGS__);\
}while(0)
template<typename I> void _DO(I&&x) {cerr << x << '\n';}
template<typename I, typename ...T> void _DO(I&&x,T&&...tail) {cerr << x << ", "; _DO(tail...);}
#define IOS
#else
#define debug(...)
#define IOS ios_base::sync_with_stdio(0);cin.tie(0)
#endif
