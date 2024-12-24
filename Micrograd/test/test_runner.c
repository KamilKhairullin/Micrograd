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
}
int main(void) {
    TestStats stats = {0, 0, 0};
    run_tests(&stats);
    run_hashTable_tests(&stats);
    PRINT_SUMMARY(stats);
    return stats.failed > 0 ? 1 : 0;
}
