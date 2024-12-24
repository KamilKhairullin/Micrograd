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

bool test_hashTable_init_buckets_initialized_to_null(void) {
    // Given/When
    HashTable* hashTable = hashTable_init();
    
    // Then
    ASSERT_NOT_NULL(hashTable);
    for (size_t i = 0; i < hashTable->capacity; i++) {
        ASSERT(hashTable->buckets[i].head == NULL,
               "Each bucket's head should be initialized to NULL");
    }
    
    // Cleanup
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_init_alt_buckets_initialized_to_null(void) {
    // Given
    size_t test_capacity = 5;
    
    // When
    HashTable* hashTable = hashTable_init_alt(test_capacity);
    
    // Then
    ASSERT_NOT_NULL(hashTable);
    for (size_t i = 0; i < test_capacity; i++) {
        ASSERT(hashTable->buckets[i].head == NULL,
               "Each bucket's head should be initialized to NULL");
    }
    
    // Cleanup
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_init_multiple_instances(void) {
    // Given/When
    HashTable* hashTable1 = hashTable_init();
    HashTable* hashTable2 = hashTable_init();
    
    // Then
    ASSERT_NOT_NULL(hashTable1);
    ASSERT_NOT_NULL(hashTable2);
    ASSERT(hashTable1 != hashTable2, "Different instances should have different addresses");
    ASSERT(hashTable1->buckets != hashTable2->buckets,
           "Different instances should have different bucket arrays");
    
    // Cleanup
    hashTable_deinit(hashTable1);
    hashTable_deinit(hashTable2);
    return true;
}

bool test_hashTable_init_alt_multiple_instances(void) {
    // Given
    size_t capacity1 = 5;
    size_t capacity2 = 10;
    
    // When
    HashTable* hashTable1 = hashTable_init_alt(capacity1);
    HashTable* hashTable2 = hashTable_init_alt(capacity2);
    
    // Then
    ASSERT_NOT_NULL(hashTable1);
    ASSERT_NOT_NULL(hashTable2);
    ASSERT(hashTable1 != hashTable2, "Different instances should have different addresses");
    ASSERT(hashTable1->buckets != hashTable2->buckets,
           "Different instances should have different bucket arrays");
    ASSERT(hashTable1->capacity == capacity1, "First hashtable should maintain its capacity");
    ASSERT(hashTable2->capacity == capacity2, "Second hashtable should maintain its capacity");
    
    // Cleanup
    hashTable_deinit(hashTable1);
    hashTable_deinit(hashTable2);
    return true;
}

bool test_hashTable_init_alt_very_small_capacity(void) {
    // Given/When
    HashTable* hashTable = hashTable_init_alt(1);
    
    // Then
    ASSERT_NOT_NULL(hashTable);
    ASSERT_NOT_NULL(hashTable->buckets);
    ASSERT(hashTable->capacity == 1, "Capacity should be 1");
    ASSERT(hashTable->size == 0, "Initial size should be 0");
    ASSERT(hashTable->buckets[0].head == NULL, "Single bucket should be initialized to NULL");
    
    // Cleanup
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_init_memory_alignment(void) {
    // Given/When
    HashTable* hashTable = hashTable_init();
    
    // Then
    ASSERT_NOT_NULL(hashTable);
    // Check if the HashTable struct is properly aligned
    ASSERT((uintptr_t)hashTable % sizeof(void*) == 0,
           "HashTable struct should be properly aligned");
    // Check if the buckets array is properly aligned
    ASSERT((uintptr_t)hashTable->buckets % sizeof(void*) == 0,
           "Buckets array should be properly aligned");
    
    // Cleanup
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_init_alt_max_size_minus_one(void) {
    // Given
    size_t almost_max_size = SIZE_MAX - 1;
    
    // When
    HashTable* hashTable = hashTable_init_alt(almost_max_size);
    
    // Then
    ASSERT_NULL(hashTable);  // Should fail due to memory constraints
    
    return true;
}


