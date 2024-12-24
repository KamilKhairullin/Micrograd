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

#define LOAD_FACTOR_THRESHOLD 0.75
#define EPSILON 1e-11

bool test_hashTable_add_single_value(void) {
    // Given
    HashTable* hashTable = hashTable_init();
    double value = 42.0;
    
    // When
    bool result = hashTable_add(hashTable, value);
    
    // Then
    ASSERT(result, "Adding single value should succeed");
    ASSERT(hashTable->size == 1, "Size should be 1 after adding one element");
//    ASSERT(hashTable_contains(hashTable, value), "Added value should be found in table");
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_add_multiple_values(void) {
    // Given
    HashTable* hashTable = hashTable_init();
    double values[] = {1.0, 2.0, 3.0, 4.0};
    size_t num_values = sizeof(values) / sizeof(values[0]);
    
    // When
    bool all_added = true;
    for (size_t i = 0; i < num_values; i++) {
        all_added &= hashTable_add(hashTable, values[i]);
    }
    
    // Then
    ASSERT(all_added, "All values should be added successfully");
    ASSERT(hashTable->size == num_values, "Size should match number of added elements");
    for (size_t i = 0; i < num_values; i++) {
//        ASSERT(hashTable_contains(hashTable, values[i]), "Each added value should be found");
    }
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_add_duplicate_value(void) {
    // Given
    HashTable* hashTable = hashTable_init();
    double value = 42.0;
    
    // When
    bool first_add = hashTable_add(hashTable, value);
    bool second_add = hashTable_add(hashTable, value);
    
    // Then
    ASSERT(first_add, "First add should succeed");
    ASSERT(!second_add, "Second add of same value should fail");
    ASSERT(hashTable->size == 1, "Size should still be 1 after duplicate add attempt");
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_add_to_null_table(void) {
    // Given
    HashTable* hashTable = NULL;
    
    // When
    bool result = hashTable_add(hashTable, 42.0);
    
    // Then
    ASSERT(!result, "Adding to NULL hash table should fail");
    
    return true;
}

bool test_hashTable_add_trigger_resize(void) {
    // Given
    HashTable* hashTable = hashTable_init_alt(2);  // Small initial capacity
    double values[] = {1.0, 2.0, 3.0};  // Adding 3 values should trigger resize
    size_t initial_capacity = hashTable->capacity;
    
    // When
    for (size_t i = 0; i < 3; i++) {
        hashTable_add(hashTable, values[i]);
    }
    
    // Then
    ASSERT(hashTable->capacity > initial_capacity, "Capacity should have increased");
    for (size_t i = 0; i < 3; i++) {
//        ASSERT(hashTable_contains(hashTable, values[i]),
//               "Values should still exist after resize");
    }
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_add_nearly_equal_values(void) {
    // Given
    HashTable* hashTable = hashTable_init();
    double value1 = 1.0;
    double value2 = 1.0 + EPSILON/2;  // Should be considered equal
    
    // When
    bool first_add = hashTable_add(hashTable, value1);
    bool second_add = hashTable_add(hashTable, value2);
    
    // Then
    ASSERT(first_add, "First add should succeed");
    ASSERT(!second_add, "Second add of nearly equal value should fail");
    ASSERT(hashTable->size == 1, "Size should be 1");
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_add_collision_handling(void) {
    // Given
    HashTable* hashTable = hashTable_init_alt(1);  // Force collisions with size 1
    double values[] = {1.0, 2.0, 3.0};  // All will hash to same bucket
    
    // When
    bool all_added = true;
    for (size_t i = 0; i < 3; i++) {
        all_added &= hashTable_add(hashTable, values[i]);
    }
    
    // Then
    ASSERT(all_added, "All values should be added despite collisions");
    ASSERT(hashTable->size == 3, "Size should be 3");
    for (size_t i = 0; i < 3; i++) {
//        ASSERT(hashTable_contains(hashTable, values[i]),
//               "Each value should be found despite collisions");
    }
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_add_to_bucket_null_bucket(void) {
    // Given
    Bucket* bucket = NULL;
    
    // When
    bool result = hashTable_add_to_bucket(bucket, 42.0);
    
    // Then
    ASSERT(!result, "Adding to NULL bucket should fail");
    
    return true;
}

bool test_hash_function_nearly_equal_values(void) {
    // Given
    size_t capacity = 100;
    double value1 = 1.0;
    double value2 = 1.0 + 0.5e-11;  // Difference smaller than epsilon
    double value3 = 1.0 + 2e-11;   // Still smaller than epsilon
    
    // When
    size_t hash1 = hash_function(value1, capacity);
    size_t hash2 = hash_function(value2, capacity);
    size_t hash3 = hash_function(value3, capacity);
    
    // Then
    ASSERT(hash1 == hash2,
           "Nearly equal values should have same hash");
    ASSERT(hash1 == hash3,
           "Nearly equal values should have same hash");
    
    return true;
}

bool test_hash_function_different_values(void) {
    // Given
    size_t capacity = 100;
    double value1 = 1.0;
    double value2 = 1.0 + 2e-7;  // Difference larger than epsilon
    
    // When
    size_t hash1 = hash_function(value1, capacity);
    size_t hash2 = hash_function(value2, capacity);
    
    // Then
    ASSERT(hash1 != hash2,
           "Significantly different values should have different hashes");
    
    return true;
}

bool test_hash_function_edge_cases(void) {
    // Given
    size_t capacity = 100;
    double very_small1 = 1e-11;
    double very_small2 = 2e-11;  // Difference is 1e-11
    double zero = 0.0;
    double negative_zero = -0.0;
    
    // When/Then
    ASSERT(hash_function(very_small1, capacity) == hash_function(very_small2, capacity),
           "Very small numbers within epsilon should hash same");
    ASSERT(hash_function(zero, capacity) == hash_function(negative_zero, capacity),
           "Zero and negative zero should hash same");
    
    return true;
}

bool test_hash_function_distribution(void) {
    // Given
    size_t capacity = 10;
    size_t counts[10] = {0};
    int num_values = 1000;
    
    // When
    for (int i = 0; i < num_values; i++) {
        double value = i * 1.1;  // Using non-integer values
        size_t hash = hash_function(value, capacity);
        counts[hash]++;
    }
    
    // Then
    // Check if distribution is reasonably uniform
    double expected = num_values / capacity;
    double chi_squared = 0.0;
    for (size_t i = 0; i < capacity; i++) {
        double diff = counts[i] - expected;
        chi_squared += (diff * diff) / expected;
    }
    
    // Chi-squared test with 9 degrees of freedom at 0.05 significance level
    // Critical value is approximately 16.919
    ASSERT(chi_squared < 16.919,
           "Hash function should distribute values uniformly");
    
    return true;
}
