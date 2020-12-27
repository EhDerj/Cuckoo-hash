
// Cuckoo hashing test

#include <stdio.h>
#include "cuckoo_hash.h"

// User space
void hash_print(void* key, void* value) {
    printf("%s -> %s\n", (char*)key, (char*)value);
}

void test1() {
    printf("Table 1:\n");
    hash_record_t r1;
    r1.key = "fluffykins";
    r1.value = "meow";

    hash_record_t r2;
    r2.key = "Hulk";
    r2.value = "ME SMASH!";

    hashtable_t* table = hashtable_new(8);
    hashtable_insert(table, &r1);
    hashtable_insert(table, &r2);
    hashtable_put(table, "Bruce Wayne", "BATMAN!");

    hashtable_foreach(table, hash_print);

    printf("Key count: %d\n", (int)table->key_count);
    void* value = hashtable_get(table, "Bruce Wayne");
    if(value) {
        printf("Found: %s\n", (char*)value);
    }

    hashtable_free(table);
}

void test2() {
    printf("\nTable 2:\n");
    hashtable_t* table = hashtable_new(8);
    hashtable_put(table, "fluffykins", "meow");
    hashtable_put(table, "adams", "42");
    hashtable_put(table, "giraffe", "neck");

    char* value = hashtable_get(table, "adams");
    if(value) {
        printf("The answer to life universe and everything is %s\n", value);
    }
    hashtable_foreach(table, hash_print);

    hashtable_free(table);
}


int main() {

    test1();
    test2();

    return 0;
}
