#include <random>
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int lb, int ub)
{ return uniform_int_distribution<int>(lb, ub)(rng); }
double rand_double(double lb, double ub)
{ return uniform_real_distribution<double>(lb, ub)(rng); }
