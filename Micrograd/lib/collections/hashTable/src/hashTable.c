#include "hashTable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR_THRESHOLD 0.8

static size_t hash_function(double value, size_t capacity) {
    unsigned long long bits;
    memcpy(&bits, &value, sizeof(double));
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
            double value = currentNode->value;
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

bool hashTable_add(HashTable* hashTable, double value) {
    if (hashTable == NULL) return false;
    
    // check if resize needed
    double loadPercent = (double)(hashTable->size+1) / (double)hashTable->capacity;
    if(loadPercent > LOAD_FACTOR_THRESHOLD) {
        hashTable_resize(hashTable);
    }
    
    size_t index = hash_function(value, hashTable->capacity);
    Bucket* bucket = &hashTable->buckets[index];
    hashTable_add_to_bucket(bucket, value);
    hashTable->size++;
    return true;
}

bool hashTable_add_to_bucket(Bucket* bucket, double value) {
    Node* headNode = bucket->head;
    // check if value already exists
    Node* iterator = headNode;
    while(iterator != NULL) {
        if (fabs(iterator->value - value) < 1e-10) {
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
                printf("---- %.1f\n", head->value);
                head = nextNode;
            }
        }
    }
}

