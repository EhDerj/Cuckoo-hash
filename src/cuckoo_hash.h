// Cuckoo hashing implementation

#ifndef cuckoo_hash_h
#define cuckoo_hash_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <wchar.h>

typedef struct {
    void* key;
    void* value;

} hash_record_t;

typedef struct {
    hash_record_t* records;
    size_t size;
    size_t key_count;
    int (*CMP)(void*,void*) ;	// compare function    
} hashtable_t;

#define HASH_MAXLOOP 10

typedef void (*hashtable_func)(void* key, void* value);

// Interface
hashtable_t* hashtable_new(size_t init_size);
void hashtable_resize(hashtable_t* self, size_t size);
void hashtable_grow(hashtable_t* self);
void hashtable_insert(hashtable_t* self, hash_record_t* v);
void hashtable_put(hashtable_t* self, void* key, void* value);
void* hashtable_get_raw(hashtable_t* self, void* key);
void* hashtable_get(hashtable_t* self, char* key);
void hashtable_print(hashtable_t* self);
void hashtable_foreach(hashtable_t* self, hashtable_func func);
void hashtable_free(hashtable_t* self);
int hashCompareStr(void* left,void*right);
int hashCompareWStr(void* left,void*right);

#endif
