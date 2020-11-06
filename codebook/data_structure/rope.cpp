#include <ext/rope>
using namespace __gnu_cxx;
int main() {
	rope<int> v;	// can be cout directly if it's char
	rope<int> v1(v);
	rope<int> v2(arr, arr + 10); //int arr[100];
	v.find(3); // return the first positoin of 3
	v.push_back(4); v.pop_back();
	//append not for iterator
	v.insert(pos, s); // pos can be iterator, integer. s can be rope, int, array 
	v.replace(pos, len, s); // (pos, len) can be (it1, it2). s is same as insert.
	v.erase(pos, len); // or v.erase(it1, it2)
	v2 = v.substr(pos, len); // same as erase
	v.copy(pos, len, arr); // int arr[100]; (pos, len) can be omitted
	v[0], v[1]
	auto it1 = v.mutable_begin(), it2 = v.mutable_end();
}
