#include "test_value.h"
#include "../lib/collections/hashTable/test/test_hashTable.h"

void run_hashTable_tests(TestStats* stats) {
    RUN_TEST(test_hashTable_init_success, stats);
    RUN_TEST(test_hashTable_init_alt_success, stats);
    RUN_TEST(test_hashTable_init_alt_zero_capacity, stats);
    RUN_TEST(test_hashTable_init_alt_large_capacity, stats);
    
    RUN_TEST(test_hashTable_init_buckets_initialized_to_null, stats);
    RUN_TEST(test_hashTable_init_alt_buckets_initialized_to_null, stats);
    RUN_TEST(test_hashTable_init_multiple_instances, stats);
    RUN_TEST(test_hashTable_init_alt_multiple_instances, stats);
    RUN_TEST(test_hashTable_init_alt_very_small_capacity, stats);
    RUN_TEST(test_hashTable_init_memory_alignment, stats);
    RUN_TEST(test_hashTable_init_alt_max_size_minus_one, stats);
    
    RUN_TEST(test_hashTable_add_single_value, stats);
    RUN_TEST(test_hashTable_add_multiple_values, stats);
    RUN_TEST(test_hashTable_add_duplicate_value, stats);
    RUN_TEST(test_hashTable_add_to_null_table, stats);
    RUN_TEST(test_hashTable_add_trigger_resize, stats);
    RUN_TEST(test_hashTable_add_nearly_equal_values, stats);
    RUN_TEST(test_hashTable_add_collision_handling, stats);
    RUN_TEST(test_hashTable_add_to_bucket_null_bucket, stats);
    
    RUN_TEST(test_hash_function_nearly_equal_values, stats);
    RUN_TEST(test_hash_function_different_values, stats);
    RUN_TEST(test_hash_function_edge_cases, stats);
    RUN_TEST(test_hash_function_distribution, stats);
    
    RUN_TEST(test_hashTable_resize_basic, stats);
    RUN_TEST(test_hashTable_resize_empty, stats);
    RUN_TEST(test_hashTable_resize_with_collisions, stats);
    RUN_TEST(test_hashTable_resize_maintains_order, stats);
    RUN_TEST(test_hashTable_resize_nearly_equal_values, stats);
    RUN_TEST(test_hashTable_resize_multiple_times, stats);
    RUN_TEST(test_hashTable_resize_large_dataset, stats);
    
    RUN_TEST(test_hashTable_contains_single_value, stats);
    RUN_TEST(test_hashTable_contains_null_table, stats);
    RUN_TEST(test_hashTable_contains_nearly_equal_values, stats);
    RUN_TEST(test_hashTable_contains_after_collision, stats);
    RUN_TEST(test_hashTable_contains_empty_table, stats);
    RUN_TEST(test_hashTable_contains_after_resize, stats);
    RUN_TEST(test_hashTable_contains_edge_values, stats);
    RUN_TEST(test_hashTable_contains_very_small_values, stats);
    
    RUN_TEST(test_hashTable_remove_single_value, stats);
    RUN_TEST(test_hashTable_remove_non_existent, stats);
    RUN_TEST(test_hashTable_remove_from_null, stats);
    RUN_TEST(test_hashTable_remove_head_node, stats);
    RUN_TEST(test_hashTable_remove_middle_node, stats);
    RUN_TEST(test_hashTable_remove_nearly_equal_values, stats);
    RUN_TEST(test_hashTable_remove_all_values, stats);
    RUN_TEST(test_hashTable_remove_same_value_twice, stats);
    RUN_TEST(test_hashTable_remove_edge_values, stats);
}

void run_tests(TestStats* stats) {
    RUN_TEST(test_value_create_positive, stats);
    RUN_TEST(test_value_create_zero, stats);
    RUN_TEST(test_value_create_negative, stats);
    
    RUN_TEST(test_value_add_positive_numbers, stats);
    RUN_TEST(test_value_add_negative_numbers, stats);
    RUN_TEST(test_value_add_mixed_numbers, stats);
    RUN_TEST(test_value_add_zeros, stats);
    RUN_TEST(test_value_add_null_inputs, stats);
    
    RUN_TEST(test_value_mul_positive_numbers, stats);
    RUN_TEST(test_value_mul_negative_numbers, stats);
    RUN_TEST(test_value_mul_mixed_numbers, stats);
    RUN_TEST(test_value_mul_by_zero, stats);
    RUN_TEST(test_value_mul_zeros, stats);
    RUN_TEST(test_value_mul_by_one, stats);
    RUN_TEST(test_value_mul_null_inputs, stats);
    
    RUN_TEST(test_value_tanh_null_input, stats);
    RUN_TEST(test_value_tanh_zero_input, stats);
    RUN_TEST(test_value_tanh_positive_input, stats);
    RUN_TEST(test_value_tanh_negative_input, stats);
    RUN_TEST(test_value_tanh_large_values, stats);
    RUN_TEST(test_value_tanh_chained_ops, stats);
}
int main(void) {
    TestStats stats = {0, 0, 0};
    run_tests(&stats);
    run_hashTable_tests(&stats);
    PRINT_SUMMARY(stats);
    return stats.failed > 0 ? 1 : 0;
}
