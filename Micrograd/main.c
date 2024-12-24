#include <stdio.h>
#include "value.h"
#include "lib/collections/hashTable/src/hashTable.h"

int main(void) {
    Value* a = value_create(2.0);
    Value* b = value_create(-3.0);
    Value* c = value_create(10);
    
    value_print(value_add(value_mul(a, b), c));
    
    HashTable* hashTable = hashTable_init();
    hashTable_add(hashTable, 1);
    hashTable_add(hashTable, 2);
    hashTable_add(hashTable, 3);
    hashTable_add(hashTable, 4);
    hashTable_add(hashTable, 5);
    hashTable_add(hashTable, 6);
    hashTable_add(hashTable, 7);
    hashTable_add(hashTable, 8);
    hashTable_add(hashTable, 9);
//    hashTable_add(hashTable, 10);
    hashTable_add(hashTable, 11);
    hashTable_add(hashTable, 12);
    hashTable_add(hashTable, 13);
    hashTable_add(hashTable, 14);

    hashTable_print(hashTable);
    return 0;
}
