#include <functional>
#include <iostream>
#include <cstring>

template <typename K, typename V, size_t Z=4096, typename H=std::hash<K>>
class onstack_map {
	H h = H();
	std::pair<K,V> store[Z];
	uint8_t state[Z];

	static const uint8_t unUsed = 0;
	static const uint8_t inUse = 1;
	static const uint8_t deleted = 2;


	size_t sz=0;
	size_t hashMod=Z;

public:
	onstack_map(){
		memset(state, unUsed, hashMod);
	}

	onstack_map(size_t mxSz) {
		int pow = 0;
		for(;mxSz;mxSz>>=1) ++pow;
		pow += 2;
		hashMod = (1<<pow);
		if(hashMod > Z) std::cout << "ERROR underlying array not big enough " << hashMod << " vs " << Z << std::endl;
		memset(state, unUsed, hashMod);
	}

	void clear() {
		sz=0;
		memset(state, unUsed, hashMod);
	}

	size_t size(){
		return sz;
	}

	void erase(K key){
		size_t hKey = h(key)%hashMod;
		for(size_t i=0; i<hashMod; ++i) {
			size_t idx = (hKey+i)%hashMod;
			if(state[idx] == unUsed)
				return;
			else if(state[idx] == deleted && store[idx].first == key)
				return;
			else if(state[idx] == inUse && store[idx].first == key) {
				--sz;
				state[idx] = deleted;
				return;
			}
		}
	}

	V& operator[](const K& key){
		size_t toInsert = hashMod;
		size_t hKey = h(key)%hashMod;
		for(size_t i=0; i<hashMod; ++i) {
			size_t idx = (hKey+i)%hashMod;
			if(state[idx] == unUsed) {
				if(toInsert < hashMod) idx = toInsert;
				state[idx] = inUse;
				store[idx].first = key;
				++sz;
				return store[idx].second;
			} else if(state[idx] == deleted && store[idx].first == key) {
				state[idx] = inUse;
				++sz;
				return store[idx].second;
			} else if(state[idx] == inUse && store[idx].first == key)
				return store[idx].second;
			else if(state[idx] == deleted && toInsert == hashMod) {
				toInsert = idx;
			}
		}


		std::cout << "ERROR hash full" << std::endl;
		return store[hashMod-1].second;

	}

	size_t count(K key) {
		size_t hKey = h(key)%hashMod;
		for(size_t i=0; i<hashMod; ++i) {
			size_t idx = (hKey+i)%hashMod;

			if(state[idx] == unUsed) return 0;
			else if(store[idx].first == key) return !(state[idx] == deleted);

		}
		return 0;
	}
};

