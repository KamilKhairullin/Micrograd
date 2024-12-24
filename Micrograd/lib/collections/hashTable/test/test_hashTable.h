#ifndef test_hashTable_h
#define test_hashTable_h

#include <stdio.h>
#include <stdbool.h>

bool test_hashTable_init_success(void);
bool test_hashTable_init_alt_success(void);
bool test_hashTable_init_alt_zero_capacity(void);
bool test_hashTable_init_alt_large_capacity(void);

bool test_hashTable_init_buckets_initialized_to_null(void);
bool test_hashTable_init_alt_buckets_initialized_to_null(void);
bool test_hashTable_init_multiple_instances(void);
bool test_hashTable_init_alt_multiple_instances(void);
bool test_hashTable_init_alt_very_small_capacity(void);
bool test_hashTable_init_memory_alignment(void);
bool test_hashTable_init_alt_max_size_minus_one(void);

bool test_hashTable_add_single_value(void);
bool test_hashTable_add_multiple_values(void);
bool test_hashTable_add_duplicate_value(void);
bool test_hashTable_add_to_null_table(void);
bool test_hashTable_add_trigger_resize(void);
bool test_hashTable_add_nearly_equal_values(void);
bool test_hashTable_add_collision_handling(void);
bool test_hashTable_add_to_bucket_null_bucket(void);

bool test_hash_function_nearly_equal_values(void);
bool test_hash_function_different_values(void);
bool test_hash_function_edge_cases(void);
bool test_hash_function_distribution(void);
#endif