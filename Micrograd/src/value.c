#include <stdlib.h>
#include "value.h"

Value* value_create(double data) {
    Value* newValue = (Value*) malloc (sizeof(Value));
    if (newValue != NULL) {
        newValue->data = data;
    }
    return newValue;
}

void value_print(Value* v) {
    if (v == NULL) {
        printf("Value(NULL)\n");
        return;
    }
    printf("Value(data=%.1f)\n", v->data);
}

Value* value_add(Value* a, Value* b) {
    if (a == NULL || b == NULL) return NULL;
    return value_create(a->data + b->data);
}

Value* value_mul(Value* a, Value* b) {
    if (a == NULL || b == NULL) return NULL;
    return value_create(a->data * b->data);
}
