#ifndef TEST_VALUE_H
#define TEST_VALUE_H

#include "../lib/test/test_framework.h"
#include "../src/value.h"

void value_destroy(Value* value);
bool test_value_create_positive(void);
bool test_value_create_zero(void);
bool test_value_create_negative(void);
bool test_value_create_null(void);

bool test_value_add_positive_numbers(void);
bool test_value_add_negative_numbers(void);
bool test_value_add_mixed_numbers(void);
bool test_value_add_zeros(void);
bool test_value_add_null_inputs(void);

bool test_value_mul_positive_numbers(void);
bool test_value_mul_negative_numbers(void);
bool test_value_mul_mixed_numbers(void);
bool test_value_mul_by_zero(void);
bool test_value_mul_zeros(void);
bool test_value_mul_by_one(void);
bool test_value_mul_null_inputs(void);

bool test_value_tanh_null_input(void);
bool test_value_tanh_zero_input(void);
bool test_value_tanh_positive_input(void);
bool test_value_tanh_negative_input(void);
bool test_value_tanh_large_values(void);
bool test_value_tanh_chained_ops(void);

bool test_value_exp_null_input(void);
bool test_value_exp_zero(void);
bool test_value_exp_one(void);
bool test_value_exp_negative_one(void);
#endif
