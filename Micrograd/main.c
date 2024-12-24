#include <stdio.h>
#include "value.h"
#include "lib/collections/hashTable/src/hashTable.h"

int main(void) {
    Value* a = value_create(2.0);
    Value* b = value_create(-3.0);
    Value* c = value_create(10);
    
    value_print(value_add(value_mul(a, b), c));
    
    HashTable* hashTable = hashTable_init();
    
    for (size_t i = 0; i < 100; i++) {
        hashTable_add(hashTable, i);
    }

    hashTable_print(hashTable);
    return 0;
}
