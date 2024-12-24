#include <stdlib.h>
#include "value.h"

Value* value_create(double data) {
    Value* newValue = (Value*) malloc (sizeof(Value));
    if (newValue != NULL) {
        newValue->data = data;
        newValue->prev = NULL;
        newValue->operation = '\0';
        newValue->label = NULL;
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
        newValue->label = NULL;
    }
    return newValue;
}

Value* value_create_labled(double data, char* label) {
    Value* newValue = (Value*) malloc (sizeof(Value));
    if (newValue != NULL) {
        newValue->data = data;
        newValue->prev = NULL;
        newValue->operation = '\0';
        newValue->label = label;
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

void value_vizualize_trace(Value* value, int depth, char* prefix) {
    if (value == NULL) return;
    
    printf("%s", prefix);
    
    if(depth == 0 && value->operation == '\0') {
        printf("    %s | %.2f\n", value->label, value->data);
    } else if (depth == 0) {
        printf("    %s | %.2f (%c)\n", value->label, value->data, value->operation);
    } else if (value->operation == '\0') {
        printf("└── %s | %.2f\n", value->label,  value->data);
    } else {
        printf("└── %s | %.2f (%c)\n", value->label, value->data, value->operation);
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
