#ifndef value_h
#define value_h

#include <stdio.h>
#include "../lib/collections/hashTable/src/hashTable.h"
#include "../lib/collections/arrayList/arrayList.h"
#include <string.h>

typedef struct Value {
    double data;
    HashTable* prev;
    char* operation;
    char* label;
    double grad;
    double uid;
} Value;

Value* value_create(double data);

Value* value_create_alt(double data, Value* left, Value* right, char* operation);

Value* value_create_labled(double data, char* label);

Value* value_add(Value* a, Value* b);

Value* value_sub(Value* a, Value* b);

Value* value_sub_raw(Value* a, double b);

Value* value_add_raw(Value* a, double b);

Value* value_mul(Value* a, Value* b);

Value* value_mul_raw(Value* a, double b);

Value* value_tanh(Value* a);

Value* value_exp(Value* a);

Value* value_power(Value* a, double power);

Value* value_div(Value* a, Value* b);

Value* value_div_raw(Value* a, double b);

void backward(Value* v);

void __backward(Value* v);

void build_topo(Value* v, HashTable* visited, ArrayList* topo);

void backward_add(Value* a, Value* b, Value* result);

void backward_mul(Value* a, Value* b, Value* result);

void backward_tanh(Value* a, Value* result);

void backward_exp(Value* a, Value* result);

void backward_pow(Value* a, Value* power, Value* result);

void value_print(Value* v);

void value_vizualize_trace(Value* value);

void __value_vizualize_trace(Value* value, int depth, char* prefix);

#endif
