#ifndef _HASH_H_
#define _HASH_H_

typedef struct d_hashCDT *d_hash_t;
typedef unsigned int (*d_hash_fnc_t)(void*);
typedef unsigned int (*d_hash_eqfnc_t)(void *, void *);

d_hash_t d_hash_new(d_hash_fnc_t fnc, d_hash_eqfnc_t eq_fnc);

int d_hash_insert(d_hash_t hash, void *key, void *elem);

unsigned d_hash_size(d_hash_t hash);

void* d_hash_fetch(d_hash_t hash, void *key);

void* d_hash_delete(d_hash_t hash, void *key);

void** d_hash_keys(d_hash_t hash);

void d_hash_destroy(d_hash_t hash);



#endif