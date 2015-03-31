/* Alexander Edwards
 * CISP 430 Wednesday 6-9pm
 * Spring 2015
 * assignment #3
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_
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

/*******************************************************************************
 * It's best implementation not be in a header file but for ease of compiling  *
 * I kept in the header. I may move the implementation into a separate file.   *
 * That being said pretend it isn't here.                                      *
 *******************************************************************************/

// ====================== HashFunction ==============================
// ==================================================================
template <typename T>
int HashTable<T>::hashFunction(const STR80 key){
	int intermediate_value = (int) key[0]; //(int) key[1] + (int) key[3] + (int) key[5]; // TODO
	int hash_index = intermediate_value % primaryBuckets;
	return hash_index;
}
// ======================= constructor ==============================
// ==================================================================
template <typename T>
HashTable<T>::HashTable(int MAXBUCKETS, int MAXSLOTS, int primaries){
	primaryBuckets = primaries;
	nextAvailableBucket = primaryBuckets;
	maxBuckets = MAXBUCKETS;
	maxSlots = MAXSLOTS;
	array = new BUCKET<T>[MAXBUCKETS];
	for(int i = 0; i<MAXBUCKETS; i++){
		array[i].slots = new SLOT<T>[MAXSLOTS];
		array[i].count = 0;
		array[i].overflow = -1;
	}
}
// ======================= hasFreeSlot() ============================
// ==================================================================
template <typename T>
bool HashTable<T>::hasFreeSlot(int hashIndex){
	return (array[hashIndex].count < maxSlots);
}
// ======================= hasOverFlow() ============================
// ==================================================================
template <typename T>
bool HashTable<T>::hasOverflow(int hashIndex){
	if(array[hashIndex].overflow == -1)
		return false;
	else
		return true;
}
// ======================= insertHere   =============================
// ==================================================================
template <typename T>
void HashTable<T>::insertHere( const STR80 key, T data, int hashIndex){
	if(hasFreeSlot(hashIndex)){
		int slotIndex = array[hashIndex].count;
		strcpy( array[hashIndex].slots[slotIndex].key, key);
		array[hashIndex].slots[slotIndex].data = data;
		array[hashIndex].count++;
	}
	else{
		if(hasOverflow(hashIndex))
			insertHere(key,data,array[hashIndex].overflow);
		else {
			array[hashIndex].overflow = nextAvailableBucket;
			insertHere(key, data, nextAvailableBucket);
			nextAvailableBucket++;
		}
	}
}
// =======================     insert   =============================
// ==================================================================
template <typename T>
void HashTable<T>::insert(const STR80 key, T data){
	int hashIndex = hashFunction(key);
	insertHere(key, data, hashIndex);
}

// ============================= find ===============================
// ==================================================================
template <typename T>
bool HashTable<T>::find( const STR80 key, int hashIndex){
	if( array[hashIndex].count == 0){
		return false;
	}
	else {
		for(int i=0; i<array[hashIndex].count; i++){
			if(strcmp(array[hashIndex].slots[i].key, key) == 0){
				return true;
			}
		}
		if(array[hashIndex].overflow > -1){
			return find(key, array[hashIndex].overflow);
		}
		else
			return false;
	}
}

// =========================== Search ===============================
// ==================================================================
template <typename T>
bool HashTable<T>::search(const STR80 key){
	int hashIndex = hashFunction(key);
	return find(key, hashIndex);
}

template <typename T>
T* HashTable<T>::getDataHelper(const STR80 key, int hashIndex){
	for(int i=0; i<array[hashIndex].count; i++){
		if(strcmp(array[hashIndex].slots[i].key, key) == 0){
			return &array[hashIndex].slots[i].data;
		}
	}
	if(array[hashIndex].overflow > -1){
			return getDataHelper(key, array[hashIndex].overflow);
		}
	else
		return nullptr;
}

// =========================== getData ==============================
// ==================================================================

template <typename T>
T* HashTable<T>::getData(const STR80 key){
	if(search(key)){
		int hashIndex = hashFunction(key);
		for(int i=0; i<array[hashIndex].count; i++){
			if(strcmp(array[hashIndex].slots[i].key, key) == 0){
				return &array[hashIndex].slots[i].data;
			}
		}
		if(array[hashIndex].overflow > -1){
			return getDataHelper(key, array[hashIndex].overflow);
		}
	}
	return nullptr;
}


// ==== destructor ======
template <typename T>
HashTable<T>::~HashTable() {
	for(int i = 0; i < maxBuckets; i++){
		delete [] array[i].slots;
	}
	delete [] array;
}
#endif /* HASHTABLE_H_ */
