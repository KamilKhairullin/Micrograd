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
#endif
