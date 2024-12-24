#ifndef hashTable_h
#define hashTable_h

#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
    double value;
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

bool hashTable_add(HashTable* hashTable, double value);

bool hashTable_add_to_bucket(Bucket* bucket, double value);

bool hashTable_remove(HashTable* hashTable, double value);

bool hashTable_contains(HashTable* hashTable, double value);

void hashTable_print(HashTable* hashTable);

#endif
