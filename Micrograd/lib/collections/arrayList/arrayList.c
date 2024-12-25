#include "arrayList.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../../src/value.h"

ArrayList* createArrayList(int initialCapacity) {
    ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
    list->array = (Value**)malloc(sizeof(Value*) * initialCapacity);
    list->size = 0;
    list->capacity = initialCapacity;
    return list;
}

void add(ArrayList* list, Value* element) {
    ensureCapacity(list);
    list->array[list->size] = element;
    list->size++;
}

Value* get(ArrayList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Index out of bounds\n");
        exit(1);
    }
    return list->array[index];
}

void removeElement(ArrayList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Index out of bounds\n");
        exit(1);
    }

    for (int i = index; i < list->size - 1; i++) {
        list->array[i] = list->array[i + 1];
    }
    list->size--;
}

void ensureCapacity(ArrayList* list) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->array = (Value**)realloc(list->array, sizeof(Value*) * list->capacity);
        if (list->array == NULL) {
            printf("Memory reallocation failed\n");
            exit(1);
        }
    }
}

void printList(ArrayList* list) {
    printf("[");
    for (int i = 0; i < list->size; i++) {
        printf("%.2f", list->array[i]->data);
        if (list->array[i]->label) {
            printf("(%s)", list->array[i]->label);
        }
        if (i < list->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void destroy(ArrayList* list) {
    // Note: This doesn't free the Value structs themselves,
    // as they might be used elsewhere
    free(list->array);
    free(list);
}

int size(ArrayList* list) {
    return list->size;
}

int isEmpty(ArrayList* list) {
    return list->size == 0;
}

void clearList(ArrayList* list) {
    list->size = 0;
}

int contains(ArrayList* list, Value* element) {
    for (int i = 0; i < list->size; i++) {
        if (list->array[i] == element) {
            return 1;
        }
    }
    return 0;
}
