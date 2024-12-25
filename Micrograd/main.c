#include <stdio.h>
#include "value.h"
#include "lib/collections/hashTable/src/hashTable.h"

int main(void) {
    Value* a = value_create_labled(2.0, "a");
    Value* b = value_create_labled(-3.0, "b");
    Value* c = value_create_labled(10, "c");
    Value* d = value_add(value_mul(a, b), c);
    d->label = "d";
    Value* f = value_create_labled(-2.0, "f");
    Value* l = value_mul(d, f);
    l->label = "l";
    Value* m = value_tanh(l);
    m->label = "m"; 
    value_vizualize_trace(m, 0, "");
    return 0;
}
