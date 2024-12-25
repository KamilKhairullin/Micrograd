#include "hashTable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../../../../src/value.h"

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR_THRESHOLD 0.8
#define EPSILON 1e-15

size_t hash_function(Value* value, size_t capacity) {
    double rounded_value = round(value->data * 1e15) / 1e15;
    if (rounded_value == -0) {
        rounded_value = 0;
    }
    unsigned long long bits;
    memcpy(&bits, &rounded_value, sizeof(double));
    bits = ((bits >> 32) ^ bits) * 0x45d9f3b;
    bits = ((bits >> 32) ^ bits) * 0x45d9f3b;
    bits = (bits >> 32) ^ bits;

    return bits % capacity;
}


HashTable* hashTable_init(void) {
    return hashTable_init_alt(INITIAL_CAPACITY);
}

HashTable* hashTable_init_alt(size_t capacity) {
    HashTable* hashTable = malloc(sizeof(HashTable));
    if (hashTable == NULL) return NULL;
    if (capacity < 1) return NULL;

    hashTable->size = 0;
    hashTable->capacity = capacity;
    hashTable->buckets = calloc(capacity, sizeof(Bucket));
    
    if (hashTable->buckets == NULL) {
        free(hashTable);
        return NULL;
    }
    return hashTable;
}

void hashTable_deinit(HashTable* hashTable) {
    if (hashTable == NULL) return;
    hashTable_deinit_buckets(hashTable);
    free(hashTable);
    return;
}

void hashTable_deinit_buckets(HashTable* hashTable) {
    for(size_t i = 0; i < hashTable->capacity; i++) {
        Bucket* bucket = &hashTable->buckets[i];
        Node* currentNode = bucket->head;
        
        while(currentNode != NULL) {
            Node* nextNode = currentNode->next;
            free(currentNode);
            currentNode = nextNode;
        }
    }
    free(hashTable->buckets);
    return;
}

bool hashTable_resize(HashTable* hashTable) {
    size_t newCapacity = hashTable->capacity * 2;
    Bucket* newBuckets = calloc(newCapacity, sizeof(Bucket));
    size_t newSize = 0;
    
    for(size_t i = 0; i < hashTable->capacity; i++) {
        Bucket* bucket = &hashTable->buckets[i];
        Node* currentNode= bucket->head;
        while(currentNode != NULL) {
            Value* value = currentNode->value;
            size_t index = hash_function(value, newCapacity);
            hashTable_add_to_bucket(&newBuckets[index], value);
            newSize++;
            Node* nextNode = currentNode->next;
            currentNode = nextNode;
        }
    }
    
    hashTable_deinit_buckets(hashTable);
    hashTable->buckets = newBuckets;
    hashTable->capacity = newCapacity;
    hashTable->size = newSize;
    return true;
}

bool hashTable_add(HashTable* hashTable, Value* value) {
    if (hashTable == NULL) return false;
    if (value == NULL) return false;
    // check if resize needed
    double loadPercent = (double)(hashTable->size+1) / (double)hashTable->capacity;
    if(loadPercent > LOAD_FACTOR_THRESHOLD) {
        hashTable_resize(hashTable);
    }
    
    size_t index = hash_function(value, hashTable->capacity);
    Bucket* bucket = &hashTable->buckets[index];
    bool addToBucketResult = hashTable_add_to_bucket(bucket, value);
    if (!addToBucketResult) return false;
    hashTable->size++;
    return true;
}

bool hashTable_add_to_bucket(Bucket* bucket, Value* value) {
    if (bucket == NULL) return false;
    Node* headNode = bucket->head;
    // check if value already exists
    Node* iterator = headNode;
    while(iterator != NULL) {
        if (fabs(iterator->value->data - value->data) < EPSILON) {
            return false;
        }
        iterator = iterator->next;
    }
    
    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) return false;
    
    newNode->value = value;
    newNode->next = headNode;
    bucket->head = newNode;
    return true;
}

bool hashTable_contains(HashTable* hashTable, Value* value) {
    if (hashTable == NULL) return false;
    size_t index = hash_function(value, hashTable->capacity);
    Bucket* bucket = &hashTable->buckets[index];
    Node* iterator = bucket->head;
    
    while(iterator != NULL) {
        if (fabs(iterator->value->data - value->data) < EPSILON) {
            return true;
        }
        iterator = iterator->next;
    }
    return false;
}

bool hashTable_remove(HashTable* hashTable, Value* value) {
    if (hashTable == NULL) return false;
    size_t index = hash_function(value, hashTable->capacity);
    Bucket* bucket = &hashTable->buckets[index];
    Node* iterator = bucket->head;
    Node* prev = NULL;
    
    while(iterator != NULL) {
        if (fabs(iterator->value->data - value->data) < EPSILON) {
            if (prev == NULL) {
                bucket->head = iterator->next;
            } else {
                prev->next = iterator->next;
            }
            free(iterator);
            hashTable->size--;
            return true;
        }
        prev = iterator;
        iterator = iterator->next;
    }
    return false;
}

void hashTable_print(HashTable* hashTable) {
    if (hashTable == NULL) {
        printf("Value(NULL)\n");
        return;
    }
    printf("HashTable(size=%zu, capacity=%zu)\n", hashTable->size, hashTable->capacity);
    for(size_t i = 0; i < hashTable->capacity; i++) {
        Bucket* bucket = &hashTable->buckets[i];
        Node* head = bucket->head;
        if (head != NULL) {
            printf("-- Bucket(index=%zu)\n", i);
            while(head != NULL) {
                Node* nextNode= head->next;
                printf("---- %.1f\n", head->value->data);
                head = nextNode;
            }
        }
    }
}

void hashTable_print_short(HashTable* hashTable) {
    if (hashTable == NULL) {
        printf("Value(NULL)\n");
        return;
    }
    printf("{ ");
    for(size_t i = 0; i < hashTable->capacity; i++) {
        Bucket* bucket = &hashTable->buckets[i];
        Node* head = bucket->head;
        if (head != NULL) {
            while(head != NULL) {
                Node* nextNode = head->next;
                printf("%.1f ", head->value->data);
                head = nextNode;
            }
        }
    }
    printf("}\n");
}

