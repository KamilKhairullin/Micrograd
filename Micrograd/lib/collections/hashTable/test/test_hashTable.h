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

bool test_hashTable_resize_basic(void);
bool test_hashTable_resize_empty(void);
bool test_hashTable_resize_with_collisions(void);
bool test_hashTable_resize_maintains_order(void);
bool test_hashTable_resize_nearly_equal_values(void);
bool test_hashTable_resize_multiple_times(void);
bool test_hashTable_resize_large_dataset(void);

bool test_hashTable_contains_single_value(void);
bool test_hashTable_contains_null_table(void);
bool test_hashTable_contains_nearly_equal_values(void);
bool test_hashTable_contains_after_collision(void);
bool test_hashTable_contains_empty_table(void);
bool test_hashTable_contains_after_resize(void);
bool test_hashTable_contains_edge_values(void);
bool test_hashTable_contains_very_small_values(void);

bool test_hashTable_remove_single_value(void);
bool test_hashTable_remove_non_existent(void);
bool test_hashTable_remove_from_null(void);
bool test_hashTable_remove_head_node(void);
bool test_hashTable_remove_middle_node(void);
bool test_hashTable_remove_nearly_equal_values(void);
bool test_hashTable_remove_all_values(void);
bool test_hashTable_remove_same_value_twice(void);
bool test_hashTable_remove_edge_values(void);

bool test_hashTable_get_all_items_null_table(void);
bool test_hashTable_get_all_items_empty_table(void);
bool test_hashTable_get_all_items_single_value(void);
bool test_hashTable_get_all_items_multiple_values(void);
bool test_hashTable_get_all_items_collision(void);

#endif
