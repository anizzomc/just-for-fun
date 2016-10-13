#include "hash.h"
#include <stdlib.h>

#define HASHINISIZE 3337
#define GROW_RATIO 2
#define BUSY_RATIO 0.6

/** Type status_t
	Flags the slot status,
	Empty: Physically Deleted
	Logical: Logically Deleted
	Busy: Occupied
*/
typedef enum {
	STATUS_EMPTY = 0, 
	STATUS_LOGICAL, 
	STATUS_BUSY
} status_t;

struct slot_t {
	status_t status;
	void *key;
	void *element;
};

struct d_hashCDT {
	struct slot_t* table;
	int element_count;
	int table_size;
	d_hash_fnc_t hash_fnc;
	d_hash_eqfnc_t eq_fnc;
};


static unsigned default_hash_fnc(void* key);
static unsigned default_eq_fnc(void *key1, void* key2);
static void grow(d_hash_t hash);
static d_hash_t do_hash_new(d_hash_fnc_t hash_fnc, d_hash_eqfnc_t eq_fnc, int size);
static int clear_table(struct slot_t table[], int slot, int size);

d_hash_t d_hash_new(d_hash_fnc_t fnc, d_hash_eqfnc_t eq_fnc) {
	return do_hash_new(fnc, eq_fnc, HASHINISIZE);
}

int d_hash_insert(d_hash_t hash, void* key, void* element){
	unsigned int slot, next;
	int i;

	grow(hash);

	slot = hash->hash_fnc(key) % hash->table_size;

	for(i = 0 ; i < hash->table_size ; i++){
		next = (slot+i) % hash->table_size;
		if(hash->table[next].status == STATUS_EMPTY){
			hash->table[next].key = key;
			hash->table[next].element = element;
			hash->table[next].status = STATUS_BUSY;
			hash->element_count++;
			return 1;
		}
		if(hash->table[next].status == STATUS_BUSY && hash->eq_fnc(key, hash->table[next].key)){
			hash->table[next].element = element;
			return 1;
		}
	}
	// TODO: Fail when a slot is not found
	return 0;
}


void* d_hash_fetch(d_hash_t hash, void* key){
	int i;
	int slot, next;

	next = slot = hash->hash_fnc(key) % hash->table_size;

	for (i = 0 ; i < hash->table_size && hash->table[next].status != STATUS_EMPTY; i++){
		next = (slot+i) % hash->table_size;

		if (hash->table[next].status == STATUS_BUSY && hash->eq_fnc(key, hash->table[next].key)){
			return hash->table[next].element;
		}
	}
	return NULL;
}

void* d_hash_delete(d_hash_t hash, void* key) {
	int i;
	int slot, next;
	void *ret = NULL;
	
	slot = next = hash->hash_fnc(key) % hash->table_size;
	
	for (i = 0 ; i < hash->table_size && hash->table[next].status != STATUS_EMPTY; i++)
	{
		next = (slot+i) % hash->table_size;
		ret = hash->table[next].element;

		if (hash->table[next].status == STATUS_BUSY && hash->eq_fnc(key, hash->table[next].key)) {
			if (hash->table[next + 1 % hash->table_size].status == STATUS_EMPTY) {	
				hash->table[next].status = STATUS_EMPTY;
				hash->element_count--;
				hash->element_count -= clear_table(hash->table, next, hash->table_size);
			}
			else {
				hash->table[next].status = STATUS_LOGICAL;	
			}
			break;
		}
	}
	return ret;
}

unsigned d_hash_size(d_hash_t hash) {
	return hash->element_count;
}

void** d_hash_keys(d_hash_t hash) {
	int i, j;
	void** ret = malloc(sizeof(void*)*d_hash_size(hash));

	for(i = 0, j = 0 ; i < hash->table_size ;i++) {
		if(hash->table[i].status == STATUS_BUSY) {
			ret[j++] = hash->table[i].key;
		}
	}

	return ret;
}

void d_hash_destroy(d_hash_t hash){
	free(hash->table);
	free(hash);
}

static d_hash_t do_hash_new(d_hash_fnc_t hash_fnc, d_hash_eqfnc_t eq_fnc, int size) {
	d_hash_t hash;
	int i;
	
	hash = malloc(sizeof(struct d_hashCDT));
	hash->table = malloc(size*sizeof(struct slot_t));

	hash->element_count = 0;
	hash->table_size = size;
	hash->hash_fnc = (hash_fnc == NULL)? default_hash_fnc : hash_fnc;
	hash->eq_fnc = (eq_fnc == NULL)? default_eq_fnc : eq_fnc;

	for(i = 0 ; i < hash->table_size ; i++)
		hash->table[i].status = STATUS_EMPTY;

	return hash;
}


static void grow(d_hash_t hash){
	d_hash_t new_hash;
	int i;

	if((((double)hash->element_count)/hash->table_size) < BUSY_RATIO) {
		return;
	}

	new_hash = do_hash_new(hash->hash_fnc, hash->eq_fnc, hash->table_size*GROW_RATIO);

	for (i = 0 ; i < hash->table_size ; i++){
		if (hash->table[i].status == STATUS_BUSY) {
			d_hash_insert(new_hash, hash->table[i].key, hash->table[i].element);		
		}
	}


	free(hash->table);
	hash->table = new_hash->table;

	hash->table_size = new_hash->table_size;
	hash->element_count = new_hash->element_count;

	free(new_hash);

}
static int clear_table(struct slot_t table[], int slot, int size){
	int i;
	
	for (i = 1 ; table[(slot-i) % size].status == STATUS_LOGICAL && i < size ; i++)
		table[(slot-i-1) % size].status = STATUS_EMPTY;
	
	return i-1;
}

static unsigned default_hash_fnc(void* key) {
	return (unsigned)key;
}

static unsigned default_eq_fnc(void *key1, void* key2) {
	return key1 == key2;
}

