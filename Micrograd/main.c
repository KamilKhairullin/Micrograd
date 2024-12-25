#include <stdio.h>
#include "value.h"
#include "lib/collections/hashTable/src/hashTable.h"

int main(void) {
//    Value* x1 = value_create_labled(2.0, "x1");
//    Value* x2 = value_create_labled(0.0, "x2");
//    
//    Value* w1 = value_create_labled(-3.0, "w1");
//    Value* w2 = value_create_labled(1.0, "w2");
//
//    Value* b = value_create_labled(6.8813735870195432, "b");
//    
//    Value* x1w1 = value_mul(x1, w1);
//    x1w1->label = "x1*w1";
//    
//    Value* x2w2 = value_mul(x2, w2);
//    x2w2->label = "x2*w2";
//    
//    Value* x1w1x2w2 = value_add(x1w1, x2w2);
//    x1w1x2w2->label = "x1*w1 + x2*w2";
//    
//    Value* n = value_add(x1w1x2w2, b);
//    n->label = "n";
//    
//    Value* o = value_tanh(n);
//    o->label = "0";
//    
//    backward(o);
//    value_vizualize_trace(o, 0, "");
    
    Value* a = value_create_labled(3.0, "a");
    Value* b = value_add(a, a);
    b->label = "b";
    backward(b);
    value_vizualize_trace(b, 0, "");
    return 0;
}
