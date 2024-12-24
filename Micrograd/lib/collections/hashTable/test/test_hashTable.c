#include "test_hashTable.h"
#include "../src/hashTable.h"
#include "../../../../lib/test/test_framework.h"
#include <stdbool.h>

bool test_hashTable_init_success(void) {
    // Given/When
    HashTable* hashTable = hashTable_init();
    
    // Then
    ASSERT_NOT_NULL(hashTable);
    ASSERT_NOT_NULL(hashTable->buckets);
    ASSERT(hashTable->capacity == 16, "Capacity should be INITIAL_CAPACITY");
    ASSERT(hashTable->size == 0, "Initial size should be 0");
    
    // Cleanup
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_init_alt_success(void) {
    // Given
    size_t test_capacity = 20;
    
    // When
    HashTable* hashTable = hashTable_init_alt(test_capacity);
    
    // Then
    ASSERT_NOT_NULL(hashTable);
    ASSERT_NOT_NULL(hashTable->buckets);
    ASSERT(hashTable->capacity == test_capacity, "Capacity should match input");
    ASSERT(hashTable->size == 0, "Initial size should be 0");
    
    // Cleanup
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_init_alt_zero_capacity(void) {
    // Given/When
    HashTable* hashTable = hashTable_init_alt(0);
    
    // Then
    ASSERT_NULL(hashTable);

    // Cleanup
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_init_alt_large_capacity(void) {
    // Given
    size_t large_capacity = 1000000;
    
    // When
    HashTable* hashTable = hashTable_init_alt(large_capacity);
    
    // Then
    ASSERT_NOT_NULL(hashTable);
    ASSERT_NOT_NULL(hashTable->buckets);
    ASSERT(hashTable->capacity == large_capacity, "Capacity should match large input");
    ASSERT(hashTable->size == 0, "Initial size should be 0");
    
    // Cleanup
    hashTable_deinit(hashTable);
    return true;
}
