#include <stdio.h>
#include "value.h"
#include "lib/collections/hashTable/src/hashTable.h"

int main(void) {
    Value* a = value_create(2.0);
    Value* b = value_create(-3.0);
    Value* c = value_create(10);
    
    value_print(value_add(value_mul(a, b), c));
    return 0;
}
