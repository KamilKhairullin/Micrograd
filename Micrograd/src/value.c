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
        newValue->grad = 0.0;
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

Value* value_mul(Value* a, Value* b) {
    if (a == NULL || b == NULL) return NULL;
    return value_create_alt(a->data * b->data, a, b, "*");
}

Value* value_tanh(Value* a) {
    if (a == NULL) return NULL;
    double n = a->data;
    double t = (exp(2 * n) - 1) / (exp(2 * n) + 1);
    return value_create_alt(t, a, NULL, "tanh");
}


void value_vizualize_trace(Value* value, int depth, char* prefix) {
    if (value == NULL) return;
    
    printf("%s", prefix);
    
    if(depth == 0 && strcmp(value->operation, "") == 0) {
        printf("    %s | %.2f | grad: %0.1f\n", value->label, value->data, value->grad);
    } else if (depth == 0) {
        printf("    %s | %.2f (%s) | grad: %0.1f\n", value->label, value->data, value->operation, value->grad);
    } else if (strcmp(value->operation, "") == 0) {
        printf("└── %s | %.2f| grad: %0.1f\n", value->label,  value->data, value->grad);
    } else {
        printf("└── %s | %.2f (%s) | grad: %0.1f\n", value->label, value->data, value->operation, value->grad);
    }
      
    if (value->prev != NULL) {
        char* new_prefix = malloc(strlen(prefix) + 4);
        strcpy(new_prefix, prefix);
        strcat(new_prefix, "    ");
        
        for (size_t i = 0; i < value->prev->capacity; i++) {
            Node* current = value->prev->buckets[i].head;
            while (current != NULL) {
                Value* childValue = (Value*)current->value;
                value_vizualize_trace(childValue, depth + 1, new_prefix);
                current = current->next;
            }
        }
        
        free(new_prefix);
    }
}
