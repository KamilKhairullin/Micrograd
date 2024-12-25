#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct HashTable HashTable;

typedef struct {
    struct Value** array;
    int size;
    int capacity;
} ArrayList;

ArrayList* createArrayList(int initialCapacity);
void add(ArrayList* list, struct Value* element);
struct Value* get(ArrayList* list, int index);
void removeElement(ArrayList* list, int index);
void destroy(ArrayList* list);
void ensureCapacity(ArrayList* list);
void printList(ArrayList* list);
int size(ArrayList* list);
int isEmpty(ArrayList* list);
void clearList(ArrayList* list);
int contains(ArrayList* list, struct Value* element);

#endif
