#include <stdlib.h>
#include <math.h>
#include "value.h"

Value* value_create(double data) {
    Value* newValue = (Value*) malloc (sizeof(Value));
    if (newValue != NULL) {
        newValue->data = data;
        newValue->prev = NULL;
        newValue->operation = "";
        newValue->label = NULL;
        newValue->grad = 0.0;
        newValue->uid = rand() % (100000000 + 1 - 0) + 0;
    }
    return newValue;
}

Value* value_create_labled(double data, char* label) {
    Value* value = value_create(data);
    value->label = label;
    return value;
}

Value* value_create_alt(double data, Value* left, Value* right, char* operation) {
    Value* newValue = value_create(data);
    HashTable* set = hashTable_init();
    hashTable_add(set, left);
    hashTable_add(set, right);
    if (newValue != NULL) {
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
    printf("Value(data=%.1f, operation=%s)\n", v->data, v->operation);
    hashTable_print_short(v->prev);
}

Value* value_add(Value* a, Value* b) {
    if (a == NULL || b == NULL) return NULL;
    return value_create_alt(a->data + b->data, a, b, "+");
}

Value* value_sub(Value* a, Value* b) {
    if (a == NULL || b == NULL) return NULL;
    return value_add_raw(a, (-1) * b->data); 
}

Value* value_sub_raw(Value* a, double b) {
    if (a == NULL) return NULL;
    return value_add_raw(a, (-1) * b);
}

Value* value_add_raw(Value* a, double b) {
    return value_add(a, value_create(b));
}

Value* value_mul(Value* a, Value* b) {
    if (a == NULL || b == NULL) return NULL;
    return value_create_alt(a->data * b->data, a, b, "*");
}

Value* value_mul_raw(Value* a, double b) {
    return value_mul(a, value_create(b));
}

Value* value_tanh(Value* a) {
    if (a == NULL) return NULL;
    double n = a->data;
    double out = (exp(2 * n) - 1) / (exp(2 * n) + 1);
    return value_create_alt(out, a, NULL, "tanh");
}

Value* value_exp(Value* a) {
    if (a == NULL) return NULL;
    double out = exp(a->data);
    return value_create_alt(out, a, NULL, "exp");
}

Value* value_power(Value* a, double power) {
    if (a == NULL) return NULL;
    double out = pow(a->data, power);
    return value_create_alt(out, a, value_create(power), "pow");
}

Value* value_div(Value* a, Value* b) {
    if (a == NULL) return NULL;
    Value* b_powered = value_power(b, -1.0);
    return value_mul(a, b_powered);
}

Value* value_div_raw(Value* a, double b) {
    if (a == NULL) return NULL;
    
    return value_div(a, value_create(b));
}

void backward(Value* v) {
    ArrayList* topo = createArrayList(32);
    HashTable* visited = hashTable_init();
    build_topo(v, visited, topo);
    v->grad = 1.0;
    for (int i = topo->size - 1; i >= 0; i--) {
        __backward(get(topo, i));
    }
}

void build_topo(Value* v, HashTable* visited, ArrayList* topo) {
    if (!hashTable_contains(visited, v)) {
        hashTable_add(visited, v);
        Value** items = hashTable_get_all_items(v->prev);
        int prevSize;
        if(v->prev == NULL) {
            prevSize = 0;
        } else {
            prevSize = (int)v->prev->size;
        }
        for (int i = 0; i < prevSize; i++) {
            build_topo(items[i], visited, topo);
        }
        add(topo, v);
    }
}

void __backward(Value* v) {
    if (v->prev == NULL) return;
    if (v->prev->size == 0) return;
    char* operation = v->operation;
    Value** items = hashTable_get_all_items(v->prev);
    
    Value* left = NULL;
    Value* right = NULL;
    
    if (v->prev->size == 1) {
        left = items[0];
        right = items[0];
    } else {
        left = items[0];
        right = items[1];
    }
    if (strcmp(operation, "+") == 0) {
        backward_add(left, right, v);
    } else if (strcmp(operation, "*") == 0) {
        backward_mul(left, right, v);
    } else if (strcmp(operation, "tanh") == 0) {
        backward_tanh(left, v);
    } else if (strcmp(operation, "exp") == 0) {
        backward_exp(left, v);
    } else if (strcmp(operation, "pow") == 0) {
        backward_pow(left, right, v);
    }
}

void backward_add(Value* a, Value* b, Value* result) {
    a->grad += 1.0 * result->grad;
    b->grad += 1.0 * result->grad;
}

void backward_mul(Value* a, Value* b, Value* result) {
    a->grad += b->data * result->grad;
    b->grad += a->data * result->grad;
}

void backward_tanh(Value* a, Value* result) {
    a->grad += (1.0 - result->data * result->data) * result->grad;
}

void backward_exp(Value* a, Value* result) {
    a->grad += result->data * result->grad;
}

void backward_pow(Value* a, Value* power, Value* result) {
    a->grad += (power->data * pow(a->data, power->data - 1)) * result->grad;
}

void value_vizualize_trace(Value* value) {
    __value_vizualize_trace(value, 0, "");
}
void __value_vizualize_trace(Value* value, int depth, char* prefix) {
    if (value == NULL) return;
    
    printf("%s", prefix);
    
    if(depth == 0 && strcmp(value->operation, "") == 0) {
        printf("    %s | %.4f | grad: %0.4f\n", value->label, value->data, value->grad);
    } else if (depth == 0) {
        printf("    %s | %.4f (%s) | grad: %0.4f\n", value->label, value->data, value->operation, value->grad);
    } else if (strcmp(value->operation, "") == 0) {
        printf("└── %s | %.4f| grad: %0.4f\n", value->label,  value->data, value->grad);
    } else {
        printf("└── %s | %.4f (%s) | grad: %0.4f\n", value->label, value->data, value->operation, value->grad);
    }
      
    if (value->prev != NULL) {
        char* new_prefix = malloc(strlen(prefix) + 4);
        strcpy(new_prefix, prefix);
        strcat(new_prefix, "    ");
        
        for (size_t i = 0; i < value->prev->capacity; i++) {
            Node* current = value->prev->buckets[i].head;
            while (current != NULL) {
                Value* childValue = (Value*)current->value;
                __value_vizualize_trace(childValue, depth + 1, new_prefix);
                current = current->next;
            }
        }
        
        free(new_prefix);
    }
}
