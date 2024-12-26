#include <stdio.h>
#include "value.h"
#include "neuron.h"
#include "layer.h"
#include "multiLayerPerceptron.h"
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
    
    Value* x1 = value_create_labled(2.0, "x1");
    Value* x2 = value_create_labled(3.0, "x2");
    Value* x3 = value_create_labled(-1.0, "x3");
    Value** x = malloc(sizeof(Value) * 3);
    x[0] = x1;
    x[1] = x2;
    x[2] = x3;

    size_t number_of_layers = 4;
    size_t* number_of_neurons_each_layer = malloc(sizeof(size_t) * number_of_layers);
    number_of_neurons_each_layer[0] = 3;
    number_of_neurons_each_layer[1] = 4;
    number_of_neurons_each_layer[2] = 4;
    number_of_neurons_each_layer[3] = 1;
    
    MultiLayerPerceptron* mlp = mlp_create(3, number_of_neurons_each_layer, number_of_layers);
    Value* out = mlp_call(mlp, x)[0];
    mlp_print(mlp);
    backward(out);
//    value_vizualize_trace(out);
    return 0;
}
