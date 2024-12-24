#include <stdlib.h>
#include "test_value.h"

void value_destroy(Value* value) {
    if (value != NULL) {
        free(value);
    }
}

bool test_value_create_positive(void) {
    double data = 42.0;
    
    // When
    Value* value = value_create(data);
    
    // Then
    ASSERT_NOT_NULL(value);
    ASSERT_EQUAL_DOUBLE(data, value->data, 0.0001);
    
    value_destroy(value);
    return true;
}

bool test_value_create_zero(void) {
    // Given
    double data = 0.0;
    
    // When
    Value* value = value_create(data);
    
    // Then
    ASSERT_NOT_NULL(value);
    ASSERT_EQUAL_DOUBLE(data, value->data, 0.0001);
    
    value_destroy(value);
    return true;
}

bool test_value_create_negative(void) {
    // Given
    double data = -15.5;
    
    // When
    Value* value = value_create(data);
    
    // Then
    ASSERT_NOT_NULL(value);
    ASSERT_EQUAL_DOUBLE(data, value->data, 0.0001);
    
    value_destroy(value);
    return true;
}

bool test_value_add_positive_numbers(void) {
    // Given
    double a_data = 5.5;
    double b_data = 3.3;
    Value* a = value_create(a_data);
    Value* b = value_create(b_data);
    
    // When
    Value* result = value_add(a, b);
    
    // Then
    ASSERT_NOT_NULL(result);
    ASSERT_EQUAL_DOUBLE(a_data + b_data, result->data, 0.0001);
    
    value_destroy(a);
    value_destroy(b);
    value_destroy(result);
    return true;
}

bool test_value_add_negative_numbers(void) {
    // Given
    double a_data = -5.5;
    double b_data = -3.3;
    Value* a = value_create(a_data);
    Value* b = value_create(b_data);
    
    // When
    Value* result = value_add(a, b);
    
    // Then
    ASSERT_NOT_NULL(result);
    ASSERT_EQUAL_DOUBLE(a_data + b_data, result->data, 0.0001);
    
    value_destroy(a);
    value_destroy(b);
    value_destroy(result);
    return true;
}

bool test_value_add_mixed_numbers(void) {
    // Given
    double a_data = 5.5;
    double b_data = -3.3;
    Value* a = value_create(a_data);
    Value* b = value_create(b_data);
    
    // When
    Value* result = value_add(a, b);
    
    // Then
    ASSERT_NOT_NULL(result);
    ASSERT_EQUAL_DOUBLE(a_data + b_data, result->data, 0.0001);
    
    value_destroy(a);
    value_destroy(b);
    value_destroy(result);
    return true;
}

bool test_value_add_zeros(void) {
    // Given
    double a_data = 0.0;
    double b_data = 0.0;
    Value* a = value_create(a_data);
    Value* b = value_create(b_data);
    
    // When
    Value* result = value_add(a, b);
    
    // Then
    ASSERT_NOT_NULL(result);
    ASSERT_EQUAL_DOUBLE(0.0, result->data, 0.0001);
    
    value_destroy(a);
    value_destroy(b);
    value_destroy(result);
    return true;
}

bool test_value_add_null_inputs(void) {
    // Given
    Value* a = value_create(5.5);
    
    // When & Then
    Value* result1 = value_add(NULL, NULL);
    ASSERT_NULL(result1);
    
    Value* result2 = value_add(a, NULL);
    ASSERT_NULL(result2);
    
    Value* result3 = value_add(NULL, a);
    ASSERT_NULL(result3);
    
    value_destroy(a);
    return true;
}

bool test_value_mul_positive_numbers(void) {
    // Given
    double a_data = 5.5;
    double b_data = 3.3;
    Value* a = value_create(a_data);
    Value* b = value_create(b_data);
    
    // When
    Value* result = value_mul(a, b);
    
    // Then
    ASSERT_NOT_NULL(result);
    ASSERT_EQUAL_DOUBLE(a_data * b_data, result->data, 0.0001);
    
    value_destroy(a);
    value_destroy(b);
    value_destroy(result);
    return true;
}

bool test_value_mul_negative_numbers(void) {
    // Given
    double a_data = -5.5;
    double b_data = -3.3;
    Value* a = value_create(a_data);
    Value* b = value_create(b_data);
    
    // When
    Value* result = value_mul(a, b);
    
    // Then
    ASSERT_NOT_NULL(result);
    ASSERT_EQUAL_DOUBLE(a_data * b_data, result->data, 0.0001);
    
    value_destroy(a);
    value_destroy(b);
    value_destroy(result);
    return true;
}

bool test_value_mul_mixed_numbers(void) {
    // Given
    double a_data = 5.5;
    double b_data = -3.3;
    Value* a = value_create(a_data);
    Value* b = value_create(b_data);
    
    // When
    Value* result = value_mul(a, b);
    
    // Then
    ASSERT_NOT_NULL(result);
    ASSERT_EQUAL_DOUBLE(a_data * b_data, result->data, 0.0001);
    
    value_destroy(a);
    value_destroy(b);
    value_destroy(result);
    return true;
}

bool test_value_mul_by_zero(void) {
    // Given
    double a_data = 5.5;
    double b_data = 0.0;
    Value* a = value_create(a_data);
    Value* b = value_create(b_data);
    
    // When
    Value* result = value_mul(a, b);
    
    // Then
    ASSERT_NOT_NULL(result);
    ASSERT_EQUAL_DOUBLE(0.0, result->data, 0.0001);
    
    value_destroy(a);
    value_destroy(b);
    value_destroy(result);
    return true;
}

bool test_value_mul_zeros(void) {
    // Given
    double a_data = 0.0;
    double b_data = 0.0;
    Value* a = value_create(a_data);
    Value* b = value_create(b_data);
    
    // When
    Value* result = value_mul(a, b);
    
    // Then
    ASSERT_NOT_NULL(result);
    ASSERT_EQUAL_DOUBLE(0.0, result->data, 0.0001);
    
    value_destroy(a);
    value_destroy(b);
    value_destroy(result);
    return true;
}

bool test_value_mul_by_one(void) {
    // Given
    double a_data = 5.5;
    double b_data = 1.0;
    Value* a = value_create(a_data);
    Value* b = value_create(b_data);
    
    // When
    Value* result = value_mul(a, b);
    
    // Then
    ASSERT_NOT_NULL(result);
    ASSERT_EQUAL_DOUBLE(a_data, result->data, 0.0001);
    
    value_destroy(a);
    value_destroy(b);
    value_destroy(result);
    return true;
}

bool test_value_mul_null_inputs(void) {
    // Given
    Value* a = value_create(5.5);
    
    // When & Then
    Value* result1 = value_mul(NULL, NULL);
    ASSERT_NULL(result1);
    
    Value* result2 = value_mul(a, NULL);
    ASSERT_NULL(result2);
    
    Value* result3 = value_mul(NULL, a);
    ASSERT_NULL(result3);
    
    value_destroy(a);
    return true;
}
