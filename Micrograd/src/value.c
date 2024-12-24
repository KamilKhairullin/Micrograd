#include <stdlib.h>
#include "value.h"

Value* value_create(double data) {
    Value* newValue = (Value*) malloc (sizeof(Value));
    if (newValue != NULL) {
        newValue->data = data;
        newValue->prev = NULL;
        newValue->operation = '\0';
    }
    return newValue;
}

Value* value_create_alt(double data, Value* left, Value* right, char operation) {
    Value* newValue = (Value*) malloc (sizeof(Value));
    HashTable* set = hashTable_init();
    hashTable_add(set, left);
    hashTable_add(set, right);
    if (newValue != NULL) {
        newValue->data = data;
        newValue->prev = set;
        newValue->operation = operation;
    }
    return newValue;
}

void value_print(Value* v) {
    if (v == NULL) {
        printf("Value(NULL)\n");
        return;
    }
    printf("Value(data=%.1f, operation=%c)\n", v->data, v->operation);
    hashTable_print_short(v->prev);
}

Value* value_add(Value* a, Value* b) {
    if (a == NULL || b == NULL) return NULL;
    return value_create_alt(a->data + b->data, a, b, '+');
}

Value* value_mul(Value* a, Value* b) {
    if (a == NULL || b == NULL) return NULL;
    return value_create_alt(a->data * b->data, a, b, '*');
}
