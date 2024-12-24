#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <setjmp.h>

// Colors for terminal output
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Test statistics
typedef struct {
    int total;
    int passed;
    int failed;
} TestStats;

static jmp_buf test_jump_buf;

static void signal_handler(int sig) __attribute__((used));
static void signal_handler(int sig) {
    longjmp(test_jump_buf, sig);
}


// Assertion macros
#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            printf(ANSI_COLOR_RED "❌ FAILED: %s\n" ANSI_COLOR_RESET \
                   "    Line %d: %s\n", __func__, __LINE__, message); \
            return false; \
        } \
    } while (0)

#define ASSERT_EQUAL_INT(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            printf(ANSI_COLOR_RED "❌ FAILED: %s\n" ANSI_COLOR_RESET \
                   "    Line %d: Expected %d, but got %d\n", \
                   __func__, __LINE__, expected, actual); \
            return false; \
        } \
    } while (0)

#define ASSERT_EQUAL_DOUBLE(expected, actual, epsilon) \
    do { \
        if (fabs((expected) - (actual)) > epsilon) { \
            printf(ANSI_COLOR_RED "❌ FAILED: %s\n" ANSI_COLOR_RESET \
                   "    Line %d: Expected %f, but got %f\n", \
                   __func__, __LINE__, expected, actual); \
            return false; \
        } \
    } while (0)

#define ASSERT_NULL(ptr) \
    ASSERT((ptr) == NULL, "Expected NULL pointer")

#define ASSERT_NOT_NULL(ptr) \
    ASSERT((ptr) != NULL, "Expected non-NULL pointer")

// Test runner

#define RUN_TEST(test_func, stats) \
    do { \
        printf("Running %s... ", #test_func); \
        (stats)->total++; \
        signal(SIGSEGV, signal_handler); \
        signal(SIGABRT, signal_handler); \
        signal(SIGFPE, signal_handler); \
        if (setjmp(test_jump_buf) == 0) { \
            if (test_func()) { \
                printf(ANSI_COLOR_GREEN "✓ PASSED\n" ANSI_COLOR_RESET); \
                (stats)->passed++; \
            } else { \
                printf(ANSI_COLOR_RED "✗ FAILED\n" ANSI_COLOR_RESET); \
                (stats)->failed++; \
            } \
        } else { \
            printf(ANSI_COLOR_RED "✗ CRASHED\n" ANSI_COLOR_RESET); \
            (stats)->failed++; \
        } \
        signal(SIGSEGV, SIG_DFL); \
        signal(SIGABRT, SIG_DFL); \
        signal(SIGFPE, SIG_DFL); \
    } while (0)


#define PRINT_SUMMARY(stats) \
    do { \
        printf("\nTest Summary:\n"); \
        printf("Total: %d\n", stats.total); \
        printf(ANSI_COLOR_GREEN "Passed: %d\n" ANSI_COLOR_RESET, stats.passed); \
        printf(ANSI_COLOR_RED "Failed: %d\n" ANSI_COLOR_RESET, stats.failed); \
    } while(0)

#endif
