#ifndef value_h
#define value_h

#include <stdio.h>

typedef struct Value {
    double data;
} Value;

Value* value_create(double data);

void value_print(Value* v);
#endif
