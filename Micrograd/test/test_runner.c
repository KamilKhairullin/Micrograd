#include "test_value.h"

void run_tests(TestStats* stats) {
    RUN_TEST(test_value_create_positive, stats);
    RUN_TEST(test_value_create_zero, stats);
    RUN_TEST(test_value_create_negative, stats);
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
