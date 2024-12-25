#ifndef hashTable_h
#define hashTable_h

#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
    struct Value* value;
    struct Node* next;
} Node;

typedef struct Bucket {
    struct Node* head;
} Bucket;

typedef struct HashTable {
    size_t capacity;
    size_t size;
    Bucket* buckets;
} HashTable;

HashTable* hashTable_init(void);

HashTable* hashTable_init_alt(size_t capacity);

bool hashTable_resize(HashTable* hashTable);

void hashTable_deinit(HashTable* hashTable);

void hashTable_deinit_buckets(HashTable* hashTable);

bool hashTable_add(HashTable* hashTable, struct Value* value);

bool hashTable_add_to_bucket(Bucket* bucket, struct Value* value);

bool hashTable_remove(HashTable* hashTable, struct Value* value);

bool hashTable_contains(HashTable* hashTable, struct Value* value);

void hashTable_print(HashTable* hashTable);

void hashTable_print_short(HashTable* hashTable);

struct Value** hashTable_get_all_items(HashTable* hashTable);

size_t hash_function(struct Value* value, size_t capacity);

#endif
