#include "test_hashTable.h"
#include "../src/hashTable.h"
#include "../../../../lib/test/test_framework.h"
#include <stdbool.h>

#define LOAD_FACTOR_THRESHOLD 0.75
#define EPSILON 1e-16

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

bool test_hashTable_add_single_value(void) {
    // Given
    HashTable* hashTable = hashTable_init();
    double value = 42.0;
    
    // When
    bool result = hashTable_add(hashTable, value);
    
    // Then
    ASSERT(result, "Adding single value should succeed");
    ASSERT(hashTable->size == 1, "Size should be 1 after adding one element");
    ASSERT(hashTable_contains(hashTable, value), "Added value should be found in table");
    
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
        ASSERT(hashTable_contains(hashTable, values[i]), "Each added value should be found");
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
        ASSERT(hashTable_contains(hashTable, values[i]),
               "Values should still exist after resize");
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
        ASSERT(hashTable_contains(hashTable, values[i]),
               "Each value should be found despite collisions");
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
    double value2 = 1.0 + 0.5 * EPSILON;  // Difference smaller than epsilon
    double value3 = 1.0 + 2 * EPSILON;   // Still smaller than epsilon
    
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
    double very_small1 = 1 * EPSILON;
    double very_small2 = 2 * EPSILON;  // Difference is 1e-11
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

bool test_hashTable_resize_basic(void) {
    // Given
    HashTable* hashTable = hashTable_init_alt(2);  // Start with small capacity
    double values[] = {1.0, 2.0};
    size_t initial_capacity = hashTable->capacity;
    
    hashTable_add(hashTable, values[0]);
    hashTable_add(hashTable, values[1]);
    bool resize_result = hashTable_resize(hashTable);
    
    // Then
    ASSERT(resize_result, "Resize should return true");
    ASSERT(hashTable->capacity == initial_capacity * 2 * 2,
           "Capacity should double after resize");
    ASSERT(hashTable->size == 2, "Size should remain the same after resize");
    for (size_t i = 0; i < 2; i++) {
        ASSERT(hashTable_contains(hashTable, values[i]),
               "Values should still exist after resize");
    }
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_resize_empty(void) {
    // Given
    HashTable* hashTable = hashTable_init_alt(2);
    size_t initial_capacity = hashTable->capacity;
    
    // When
    bool resize_result = hashTable_resize(hashTable);
    
    // Then
    ASSERT(resize_result, "Resize should return true");
    ASSERT(hashTable->capacity == initial_capacity * 2,
           "Capacity should double after resize");
    ASSERT(hashTable->size == 0, "Size should remain 0 after resize");
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_resize_with_collisions(void) {
    // Given
    HashTable* hashTable = hashTable_init_alt(1);  // Force collisions
    double values[] = {1.0, 2.0, 3.0};  // All hash to same bucket initially
    
    // When
    for (size_t i = 0; i < 3; i++) {
        hashTable_add(hashTable, values[i]);
    }
    bool resize_result = hashTable_resize(hashTable);
    
    // Then
    ASSERT(resize_result, "Resize should return true");
    ASSERT(hashTable->size == 3, "Size should remain same after resize");
    for (size_t i = 0; i < 3; i++) {
        ASSERT(hashTable_contains(hashTable, values[i]),
               "Values should still exist after resize");
    }
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_resize_maintains_order(void) {
    // Given
    HashTable* hashTable = hashTable_init_alt(2);
    double values[] = {1.0, 1.1, 1.2, 1.3};  // Values that might hash to same bucket
    
    // When
    for (size_t i = 0; i < 4; i++) {
        hashTable_add(hashTable, values[i]);
    }
    bool resize_result = hashTable_resize(hashTable);
    
    // Then
    ASSERT(resize_result, "Resize should return true");
    ASSERT(hashTable->size == 4, "Size should remain same after resize");
    for (size_t i = 0; i < 4; i++) {
        ASSERT(hashTable_contains(hashTable, values[i]),
               "Values should still exist after resize");
    }
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_resize_nearly_equal_values(void) {
    // Given
    HashTable* hashTable = hashTable_init_alt(2);
    double value1 = 1.0;
    double value2 = 1.0 + 1.5 * EPSILON;  // Nearly equal value
    
    // When
    hashTable_add(hashTable, value1);
    hashTable_add(hashTable, value2);  // Should not actually add due to near equality
    bool resize_result = hashTable_resize(hashTable);
    
    // Then
    ASSERT(resize_result, "Resize should return true");
    ASSERT(hashTable->size == 1, "Size should remain 1 after resize");
    ASSERT(hashTable_contains(hashTable, value1),
           "Original value should exist after resize");
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_resize_multiple_times(void) {
    // Given
    HashTable* hashTable = hashTable_init_alt(2);
    size_t initial_capacity = hashTable->capacity;
    
    // When
    bool first_resize = hashTable_resize(hashTable);
    size_t first_resize_capacity = hashTable->capacity;
    bool second_resize = hashTable_resize(hashTable);
    
    // Then

ASSERT(first_resize && second_resize, "Both resizes should succeed");
    ASSERT(hashTable->capacity == initial_capacity * 4,
           "Capacity should quadruple after two resizes");
    ASSERT(first_resize_capacity == initial_capacity * 2,
           "First resize should double capacity");
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_resize_large_dataset(void) {
    // Given
    HashTable* hashTable = hashTable_init_alt(2);
    size_t num_values = 1000;
    double* values = malloc(num_values * sizeof(double));
    
    // When
    for (size_t i = 0; i < num_values; i++) {
        values[i] = i * 1.1;
        hashTable_add(hashTable, values[i]);
    }
    bool resize_result = hashTable_resize(hashTable);
    
    // Then
    ASSERT(resize_result, "Resize should return true");
    ASSERT(hashTable->size == num_values,
           "Size should match number of inserted values");
    for (size_t i = 0; i < num_values; i++) {
        ASSERT(hashTable_contains(hashTable, values[i]),
               "Each value should still exist after resize");
    }
    
    free(values);
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_contains_single_value(void) {
    // Given
    HashTable* hashTable = hashTable_init();
    double value = 42.0;
    
    // When
    hashTable_add(hashTable, value);
    
    // Then
    ASSERT(hashTable_contains(hashTable, value),
           "Should find added value");
    ASSERT(!hashTable_contains(hashTable, 43.0),
           "Should not find non-existent value");
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_contains_null_table(void) {
    // Given
    HashTable* hashTable = NULL;
    
    // When/Then
    ASSERT(!hashTable_contains(hashTable, 42.0),
           "Should return false for NULL table");
    
    return true;
}

bool test_hashTable_contains_nearly_equal_values(void) {
    // Given
    HashTable* hashTable = hashTable_init();
    double value = 1.0;
    double nearly_equal = 1.0 + EPSILON/2;
    double different = 1.0 + EPSILON*10;
    
    // When
    hashTable_add(hashTable, value);
    
    // Then
    ASSERT(hashTable_contains(hashTable, nearly_equal),
           "Should find nearly equal value");
    ASSERT(!hashTable_contains(hashTable, different),
           "Should not find significantly different value");
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_contains_after_collision(void) {
    // Given
    HashTable* hashTable = hashTable_init_alt(1);  // Force collisions
    double values[] = {1.0, 2.0, 3.0};  // Will all hash to same bucket
    
    // When
    for (size_t i = 0; i < 3; i++) {
        hashTable_add(hashTable, values[i]);
    }
    
    // Then
    for (size_t i = 0; i < 3; i++) {
        ASSERT(hashTable_contains(hashTable, values[i]),
               "Should find all values despite collisions");
    }
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_contains_empty_table(void) {
    // Given
    HashTable* hashTable = hashTable_init();
    
    // When/Then
    ASSERT(!hashTable_contains(hashTable, 42.0),
           "Empty table should not contain any values");
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_contains_after_resize(void) {
    // Given
    HashTable* hashTable = hashTable_init_alt(2);
    double values[] = {1.0, 2.0, 3.0, 4.0};  // Enough to trigger resize
    
    // When
    for (size_t i = 0; i < 4; i++) {
        hashTable_add(hashTable, values[i]);
    }
    
    // Then
    for (size_t i = 0; i < 4; i++) {
        ASSERT(hashTable_contains(hashTable, values[i]),
               "Should find all values after resize");
    }
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_contains_edge_values(void) {
    // Given
    HashTable* hashTable = hashTable_init();
    double edge_values[] = {
        0.0,
        -0.0,
        1.79769e+308,
        -1.79769e+308,
        2.2250738585072014e-308,
        -2.2250738585072014e-308,
    };
    
    // When
    for (size_t i = 0; i < sizeof(edge_values)/sizeof(edge_values[0]); i++) {
        hashTable_add(hashTable, edge_values[i]);
    }
    
    // Then
    for (size_t i = 0; i < sizeof(edge_values)/sizeof(edge_values[0]); i++) {
        ASSERT(hashTable_contains(hashTable, edge_values[i]),
               "Should handle edge values correctly");
    }
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_contains_very_small_values(void) {
    // Given
    HashTable* hashTable = hashTable_init();
    double tiny_value = 1e-9;
    double slightly_larger = 1.1e-9;
    
    // When
    hashTable_add(hashTable, tiny_value);
    
    // Then
    ASSERT(hashTable_contains(hashTable, tiny_value),
           "Should find very small value");
    ASSERT(!hashTable_contains(hashTable, slightly_larger),
           "Should distinguish between different very small values");
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_remove_single_value(void) {
    // Given
    HashTable* hashTable = hashTable_init();
    double value = 42.0;
    hashTable_add(hashTable, value);
    size_t initial_size = hashTable->size;
    
    // When
    bool remove_result = hashTable_remove(hashTable, value);
    
    // Then
    ASSERT(remove_result, "Remove should return true for existing value");
    ASSERT(!hashTable_contains(hashTable, value),
           "Value should not exist after removal");
    ASSERT(hashTable->size == initial_size - 1,
           "Size should decrease after removal");
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_remove_non_existent(void) {
    // Given
    HashTable* hashTable = hashTable_init();
    hashTable_add(hashTable, 42.0);
    size_t initial_size = hashTable->size;
    
    // When
    bool remove_result = hashTable_remove(hashTable, 43.0);
    
    // Then
    ASSERT(!remove_result, "Remove should return false for non-existent value");
    ASSERT(hashTable->size == initial_size,
           "Size should not change when removal fails");
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_remove_from_null(void) {
    // Given
    HashTable* hashTable = NULL;
    
    // When
    bool remove_result = hashTable_remove(hashTable, 42.0);
    
    // Then
    ASSERT(!remove_result, "Remove should return false for NULL table");
    
    return true;
}

bool test_hashTable_remove_head_node(void) {
    // Given
    HashTable* hashTable = hashTable_init_alt(1);  // Force collisions
    double values[] = {1.0, 2.0, 3.0};
    for (size_t i = 0; i < 3; i++) {
        hashTable_add(hashTable, values[i]);
    }
    
    // When
    bool remove_result = hashTable_remove(hashTable, values[2]); // Remove head
    
    // Then
    ASSERT(remove_result, "Should successfully remove head node");
    ASSERT(!hashTable_contains(hashTable, values[2]),
           "Removed value should not exist");
    ASSERT(hashTable_contains(hashTable, values[0]) &&
           hashTable_contains(hashTable, values[1]),
           "Other values should still exist");
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_remove_middle_node(void) {
    // Given
    HashTable* hashTable = hashTable_init_alt(1);  // Force collisions
    double values[] = {1.0, 2.0, 3.0};
    for (size_t i = 0; i < 3; i++) {
        hashTable_add(hashTable, values[i]);
    }
    
    // When
    bool remove_result = hashTable_remove(hashTable, values[1]); // Remove middle
    
    // Then
    ASSERT(remove_result, "Should successfully remove middle node");
    ASSERT(!hashTable_contains(hashTable, values[1]),
           "Removed value should not exist");
    ASSERT(hashTable_contains(hashTable, values[0]) &&
           hashTable_contains(hashTable, values[2]),
           "Other values should still exist");
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_remove_nearly_equal_values(void) {
    // Given
    HashTable* hashTable = hashTable_init();
    double value = 1.0;
    double nearly_equal = 1.0 + EPSILON/2;

hashTable_add(hashTable, value);
    
    // When
    bool remove_result = hashTable_remove(hashTable, nearly_equal);
    
    // Then
    ASSERT(remove_result, "Should remove nearly equal value");
    ASSERT(!hashTable_contains(hashTable, value),
           "Original value should not exist after removal");
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_remove_all_values(void) {
    // Given
    HashTable* hashTable = hashTable_init();
    double values[] = {1.0, 2.0, 3.0, 4.0};
    for (size_t i = 0; i < 4; i++) {
        hashTable_add(hashTable, values[i]);
    }
    
    // When
    bool all_removed = true;
    for (size_t i = 0; i < 4; i++) {
        all_removed &= hashTable_remove(hashTable, values[i]);
    }
    
    // Then
    ASSERT(all_removed, "Should successfully remove all values");
    ASSERT(hashTable->size == 0, "Size should be 0 after removing all values");
    for (size_t i = 0; i < 4; i++) {
        ASSERT(!hashTable_contains(hashTable, values[i]),
               "No values should exist after removal");
    }
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_remove_same_value_twice(void) {
    // Given
    HashTable* hashTable = hashTable_init();
    double value = 42.0;
    hashTable_add(hashTable, value);
    
    // When
    bool first_remove = hashTable_remove(hashTable, value);
    bool second_remove = hashTable_remove(hashTable, value);
    
    // Then
    ASSERT(first_remove, "First remove should succeed");
    ASSERT(!second_remove, "Second remove should fail");
    ASSERT(hashTable->size == 0, "Size should be 0 after removal");
    
    hashTable_deinit(hashTable);
    return true;
}

bool test_hashTable_remove_edge_values(void) {
    // Given
    HashTable* hashTable = hashTable_init();
    double edge_values[] = {
        0.0,
        -0.0,
        1.79769e+308,
        -1.79769e+308,
        2.2250738585072014e-308,
        -2.2250738585072014e-308,
    };
    
    // When/Then
    for (size_t i = 0; i < sizeof(edge_values)/sizeof(edge_values[0]); i++) {
        hashTable_add(hashTable, edge_values[i]);
        ASSERT(hashTable_remove(hashTable, edge_values[i]),
               "Should successfully remove edge values");
        ASSERT(!hashTable_contains(hashTable, edge_values[i]),
               "Edge value should not exist after removal");
    }
    
    hashTable_deinit(hashTable);
    return true;
}
