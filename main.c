
// Cuckoo hashing test

#include <stdio.h>
#include <cuckoo_hash.h>

// User space
void hash_print(void* key, void* value) {
    printf("%s -> %s\n", (char*)key, (char*)value);
}


int main() {
    void* key1 = (void*)"fluffykins";

    hash_record_t r1;
    r1.key = key1;
    r1.value = "meow";

    hash_record_t r2;
    r2.key = "crockford";
    r2.value = "SEMICOLONS!";

    hashtable_t* table = hashtable_new(8);
    hashtable_insert(table, &r1);
    hashtable_insert(table, &r2);
    hashtable_put(table, "alex", "nerd");

    hashtable_foreach(table, hash_print);

    printf("Key count: %d\n", (int)table->key_count);
    void* value = hashtable_get(table, key1);
    if(value) {
        printf("Found: %s\n", (char*)value);
    }

    hashtable_free(table);
    return 0;
}
