/*
 * HashTable.h
 *
 *  Created on: Mar 10, 2015
 *      Author: alex
 */
#include <string.h>
#ifndef HASHTABLE_H_
#define HASHTABLE_H_

// ===================== Type definitions ===========================
// ==================================================================
typedef char STR10[10+1];     // type definition for key identifiers

typedef char STR20[20+1];     // type definition for data

typedef struct SLOT{          // type definition for slot, which contains
	STR10 key;                // the key and data to be looked up
	STR20 data;
} SLOT;

typedef struct BUCKET{        // type definition for buckets which
	SLOT *slots;              // contain slots and links to other buckets
	int overflow;             // overflow int refers to another bucket
	int count;                // count int keeps track of how many slots are filled
} BUCKET;



// ==== class definition =====
class HashTable {
private:
	BUCKET *array;
	int maxBuckets;// maximum number of buckets in hashtable
	int primaryBuckets;// number of primary buckets in hashtable
	int nextAvailableBucket; // keeps track of next overflow buckets index
	int maxSlots;  // maximum number of slots in bucket
public:
	int hashFunction(STR10 key);
	bool hasFreeSlot(int hashIndex);
	bool hasOverflow(int hashIndex);
	void insert(STR10 key, STR20 data);
	void insertHere(STR10 key, STR20 data, int hashIndex);
	bool search(STR10 key);
	STR20* getDataHelper(STR10 key, int hashIndex);
	STR20* getData(STR10 key);
	bool find(STR10 key, int hashIndex);
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
int HashTable::hashFunction(STR10 key){
	int intermediate_value = (int) key[1] + (int) key[3] + (int) key[5]; // TODO
	int hash_index = intermediate_value % primaryBuckets;
	return hash_index;
}
// ======================= constructor ==============================
// ==================================================================
HashTable::HashTable(int MAXBUCKETS, int MAXSLOTS, int primaries){
	primaryBuckets = primaries;
	nextAvailableBucket = primaryBuckets;
	maxBuckets = MAXBUCKETS;
	maxSlots = MAXSLOTS;
	array = new BUCKET[MAXBUCKETS];
	for(int i = 0; i<MAXBUCKETS; i++){
		array[i].slots = new SLOT[MAXSLOTS];
		array[i].count = 0;
		array[i].overflow = -1;
	}
}
// ======================= hasFreeSlot() ============================
// ==================================================================
// supports InsertIntoHT
bool HashTable::hasFreeSlot(int hashIndex){
	return (array[hashIndex].count < maxSlots);
}
// ======================= hasOverFlow() ============================
// ==================================================================
// supports InsertIntoHT
bool HashTable::hasOverflow(int hashIndex){
	if(array[hashIndex].overflow == -1)
		return false;
	else
		return true;
}
// ======================= insertHere   =============================
// ==================================================================
void HashTable::insertHere( STR10 key, STR20 data, int hashIndex){
	if(hasFreeSlot(hashIndex)){
		int slotIndex = array[hashIndex].count;
		strcpy( array[hashIndex].slots[slotIndex].key, key);
		strcpy(array[hashIndex].slots[slotIndex].data, data);
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
void HashTable::insert( STR10 key, STR20 data){
	int hashIndex = hashFunction(key);
	insertHere(key, data, hashIndex);
}

// ============================= find ===============================
// ==================================================================
bool HashTable::find( STR10 key, int hashIndex){
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
bool HashTable::search(STR10 key){
	int hashIndex = hashFunction(key);
	return find(key, hashIndex);
}
STR20* HashTable::getDataHelper(STR10 key, int hashIndex){
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
STR20* HashTable::getData(STR10 key){
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
HashTable::~HashTable() {
	for(int i = 0; i < maxBuckets; i++){
		delete [] array[i].slots;
	}
	delete [] array;
}
#endif /* HASHTABLE_H_ */
