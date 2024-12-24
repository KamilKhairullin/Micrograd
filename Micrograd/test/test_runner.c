#include "test_value.h"

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

void print_summary(TestStats stats) {
    printf("\nTest Summary:\n");
    printf("Total: %d\n", stats.total);
    printf(ANSI_COLOR_GREEN "Passed: %d\n" ANSI_COLOR_RESET, stats.passed);
    printf(ANSI_COLOR_RED "Failed: %d\n" ANSI_COLOR_RESET, stats.failed);
}

int main(void) {
    TestStats stats = {0, 0, 0};
    printf("\nRunning tests...\n\n");
    
    run_tests(&stats);
    print_summary(stats);
    return stats.failed > 0 ? 1 : 0;
}
