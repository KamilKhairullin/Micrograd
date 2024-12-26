#ifndef layer_h
#define layer_h

#include <stdio.h>
#include "neuron.h"


typedef struct Layer {
    Neuron** neurons;
    size_t neurons_size;
} Layer;

Layer* layer_create(size_t neuron_input_size, size_t number_of_neurons);

void layer_print(Layer* l);

Value** layer_call(Layer* l, Value** x);

void layer_params(Layer* l, ArrayList* list);
#endif /* layer_h */

