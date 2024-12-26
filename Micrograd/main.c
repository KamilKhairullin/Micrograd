#include <stdio.h>
#include "value.h"
#include "neuron.h"
#include "utils.h"
#include "lib/collections/hashTable/src/hashTable.h"
#include <time.h>

int main(void) {
    srand((unsigned int)time(NULL));
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
//    Value* e = value_exp(value_mul_raw(n, 2));
//    e->label = "e";
//    Value* o = value_div(value_sub_raw(e, 1), value_add_raw(e, 1));
//    o->label = "o";
//    backward(o);
//    value_vizualize_trace(o);
    
    printf("%.04f\n", rnd(-1, 1));
    Neuron* n = neuron_create(2);
    Value* x1 = value_create_labled(2.0, "x1");
    Value* x2 = value_create_labled(3.0, "x2");

    Value** x = malloc(sizeof(Value) * 2);
    x[0] = x1;
    x[1] = x2;
    Value* out = neuron_call(n, x);
    backward(out);
    value_vizualize_trace(out);
    return 0;
}
