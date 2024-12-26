#ifndef multiLayerPerceptron_h
#define multiLayerPerceptron_h

#include <stdio.h>
#include "layer.h"
#include "value.h"

typedef struct MultiLayerPerceptron {
    Layer** layers;
    size_t layers_width;
} MultiLayerPerceptron;

MultiLayerPerceptron* mlp_create(size_t first_layer_input_size, size_t* number_of_neurons_on_each_layer, size_t number_of_layers);

void mlp_print(MultiLayerPerceptron* mlp);

Value** mlp_call(MultiLayerPerceptron* mlp, Value** x);

#endif
