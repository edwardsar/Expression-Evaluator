// Author: Alexander Edwards


#ifndef HASHTABLE_HPP_
#define HASHTABLE_HPP_
#include <string.h>


// ===================== Type definitions ===========================
// ==================================================================
typedef char STR80[80+1];     // type definition for key identifiers

template <typename T>
struct SLOT{          // type definition for slot, which contains
	STR80 key;                // the key and data to be looked up
	T data;
};

template <typename T>
struct BUCKET{        // type definition for buckets which
	SLOT<T> *slots;              // contain slots and links to other buckets
	int overflow;             // overflow int refers to another bucket
	int count;                // count int keeps track of how many slots are filled
};



// ==== class definition =====
template <typename T>
class HashTable {
private:
	BUCKET<T> *array;
	int maxBuckets;// maximum number of buckets in hashtable
	int primaryBuckets;// number of primary buckets in hashtable
	int nextAvailableBucket; // keeps track of next overflow buckets index
	int maxSlots;  // maximum number of slots in bucket
public:
	int hashFunction(const STR80 key);
	bool hasFreeSlot(int hashIndex);
	bool hasOverflow(int hashIndex);
	void insert(const STR80 key, T data);
	void insertHere(const STR80 key, T data, int hashIndex);
	bool search(const STR80 key);
	T* getDataHelper(const STR80 key, int hashIndex);
	T* getData(const STR80 key);
	bool find(const STR80 key, int hashIndex);
	HashTable(int MAXBUCKETS = 30, int MAXSLOTS = 20, int primaries = 20 );
	virtual ~HashTable();
};

#include "HashTable.cpp"

#endif
