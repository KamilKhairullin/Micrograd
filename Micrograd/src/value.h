#ifndef value_h
#define value_h

#include <stdio.h>
#include "../lib/collections/hashTable/src/hashTable.h"
#include <string.h>

typedef struct Value {
    double data;
    HashTable* prev;
    char operation;
    char* label;
} Value;

Value* value_create(double data);

Value* value_create_alt(double data, Value* left, Value* right, char operation);

Value* value_create_labled(double data, char* label);

Value* value_add(Value* a, Value* b);

Value* value_mul(Value* a, Value* b);

void value_print(Value* v);

void value_vizualize_trace(Value* value, int depth, char* prefix);

#endif
