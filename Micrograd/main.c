#include <stdio.h>
#include "value.h"
#include "lib/collections/hashTable/src/hashTable.h"

int main(void) {
    Value* x1 = value_create_labled(2.0, "x1");
    Value* x2 = value_create_labled(0.0, "x2");
    
    Value* w1 = value_create_labled(-3.0, "w1");
    Value* w2 = value_create_labled(1.0, "w2");

    Value* b = value_create_labled(6.8813735870195432, "b");
    
    Value* x1w1 = value_mul(x1, w1);
    x1w1->label = "x1*w1";
    
    Value* x2w2 = value_mul(x2, w2);
    x2w2->label = "x2*w2";
    
    Value* x1w1x2w2 = value_add(x1w1, x2w2);
    x1w1x2w2->label = "x1*w1 + x2*w2";
    
    Value* n = value_add(x1w1x2w2, b);
    n->label = "n";
    
//    Value* o = value_tanh(n);
//    o->label = "0";
    
    
    Value* e = value_exp(value_mul_raw(n, 2));
    e->label = "e";
    Value* o = value_div(value_sub_raw(e, 1), value_add_raw(e, 1));
    o->label = "o";
    backward(o);
    value_vizualize_trace(o);
//
//    Value* a = value_create_labled(2.0, "a");
//    Value* b = value_create_labled(4.0, "b");
//    Value* c = value_div(a, b);
//    c->label = "c";
//    backward(c);
//    value_vizualize_trace(c);

//    Value* a = value_create_labled(-2.0, "a");
//    Value* b = value_create_labled(3.0, "b");
//    Value* d = value_mul(a, b); d->label = "d";
//    Value* e = value_add(a, b); e->label = "e";
//    Value* f = value_mul(d, e); f->label = "f";
//    backward(f);
//    value_vizualize_trace(f);
    return 0;
}
