// Alexander Edwards


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
	for(int i = 0; i<array[hashIndex].count; i++){
		if(strcmp(array[hashIndex].slots[i].key, key) == 0 ){
			array[hashIndex].slots[i].data = data;
			return;
		}
	}
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
