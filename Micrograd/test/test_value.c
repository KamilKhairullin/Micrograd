#include <stdlib.h>
#include "test_value.h"

bool test_value_create_positive(void) {
    double data = 42.0;
    
    // When
    Value* value = value_create(data);
    
    // Then
    ASSERT_NOT_NULL(value);
    ASSERT_EQUAL_DOUBLE(data, value->data, 0.0001);
    
    free(value);
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
    
    free(value);
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
    
    free(value);
    return true;
}
