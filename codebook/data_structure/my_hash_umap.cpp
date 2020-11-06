struct KeyHasher {
	size_t operator()(const Key& k) const {
		return k.first + k.second * 100000;
	}
};
typedef unordered_map<Key, int, KeyHasher> map_t;
