#ifndef value_h
#define value_h

#include <stdio.h>

typedef struct Value {
    double data;
} Value;

Value* value_create(double data);

Value* value_add(Value* a, Value* b);

Value* value_mul(Value* a, Value* b);

void value_print(Value* v);
#endif
