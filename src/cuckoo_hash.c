#include "cuckoo_hash.h"


void hashtable_resize(hashtable_t* self, size_t size) {
    self->records = realloc(self->records, sizeof(hash_record_t) * size);

    if(size > self->size) {
        size_t diff = (size - self->size) * sizeof(hash_record_t);
        memset(&self->records[self->size], 0, diff);
    }

    self->size = size;
}

void hashtable_grow(hashtable_t* self) {
    hashtable_resize(self, self->size * 2);
}

hashtable_t* hashtable_new(size_t init_size) {
    hashtable_t* self = calloc(sizeof(hashtable_t), 1);
    hashtable_resize(self, init_size);
    return self;
}

hash_record_t* hashtable_record1(hashtable_t* self, void* k) {
    intptr_t kk = (intptr_t)k;
    size_t pos = kk % self->size;
    return &self->records[pos];
}

hash_record_t* hashtable_record2(hashtable_t* self, void* k) {
    intptr_t kk = (intptr_t)k;
    size_t pos = (kk / self->size) % self->size;
    return &self->records[pos];
}

void hash_record_swap(hash_record_t* r1, hash_record_t* r2) {
    hash_record_t tmp = *r1;
    *r1 = *r2;
    *r2 = tmp;
}

// Helper function
void hashtable_put_rehash(hashtable_t* self, hash_record_t* v) {
    hash_record_t* r = hashtable_record1(self, v->key);
    if(!r->key) {
        hash_record_swap(r, v);
        self->key_count++;
        return;
    }

    if(r->key == v->key) {
        // Replace
        r->value = v->value;
        return;
    }

    r = hashtable_record2(self, v->key);
    if(!r->key) {
        hash_record_swap(r, v);
        self->key_count++;
        return;
    }

    if(r->key == v->key) {
        r->value = v->value;
        return;
    }

    hashtable_insert(self, v);
}

void hashtable_put(hashtable_t* self, void* key, void* value) {
    hash_record_t rec;
    rec.key = key;
    rec.value = value;
    hashtable_insert(self, &rec);
}

void hashtable_insert(hashtable_t* self, hash_record_t* v) {
    for(int n = 0; n < HASH_MAXLOOP; n++) {
        // Get the object at the requested index
        hash_record_t* record = hashtable_record1(self, v->key);

        // Request a swap
        hash_record_swap(v, record);

        // If swapped record is null,
        // we successfully added the key
        if(!v->key) {
            self->key_count++;
            return;
        }

        // Else, use the alternative hash for the swapped value
        // 1. Find the new index cell
        // 2. Swap index cells
        record = hashtable_record2(self, v->key);
        hash_record_swap(v, record);

        if(!v->key) {
            self->key_count++;
            return;
        }

        // If the newly replaced cell wasn't empty, repeat the process
    }

    // Failed?
    // Grow and rehash
    hashtable_grow(self);
    hashtable_put_rehash(self, v);
}

void* hashtable_get_raw(hashtable_t* self, void* key) {
    hash_record_t* r = hashtable_record1(self, key);
    if(key == r->key) return r->value;
    r = hashtable_record2(self, key);
    if(key == r->key) return r->value;
    return 0;
}

void* hashtable_get(hashtable_t* self, char* key) {
    hash_record_t* r = hashtable_record1(self, key);
    if(r->key && !strcmp(key, r->key)) return r->value;
    r = hashtable_record2(self, key);
    if(r->key && !strcmp(key, r->key)) return r->value;
    return 0;
}

void hashtable_print(hashtable_t* self) {
    for(size_t i = 0; i < self->size; i++) {
        hash_record_t* record = &self->records[i];
        if(record) {
            printf("%d: %p -> %p\n", (int)i, record->key, record->value);
        }
    }
}

void hashtable_foreach(hashtable_t* self, hashtable_func func) {
    for(size_t i = 0; i < self->size; i++) {
        hash_record_t* record = &self->records[i];
        if(record->key) func(record->key, record->value);
    }
}

void hashtable_free(hashtable_t* self) {
    free(self->records);
    free(self);
}
