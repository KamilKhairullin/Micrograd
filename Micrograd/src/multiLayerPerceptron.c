#include "multiLayerPerceptron.h"
 
MultiLayerPerceptron* mlp_create(size_t first_layer_input_size, size_t* number_of_neurons_on_each_layer, size_t number_of_layers) {
    MultiLayerPerceptron* mlp = malloc(sizeof(MultiLayerPerceptron));
    mlp->layers = malloc(sizeof(Layer) * number_of_layers);
    mlp->layers_width = number_of_layers;
    for (size_t i = 0; i < number_of_layers; i++) {
        size_t neuron_input_size;
        if (i == 0) {
            neuron_input_size = first_layer_input_size;
        } else {
            neuron_input_size = mlp->layers[i - 1]->neurons_size;
        }
        mlp->layers[i] = layer_create(neuron_input_size, number_of_neurons_on_each_layer[i]);
    }
    return mlp;
}

void mlp_print(MultiLayerPerceptron* mlp) {
    for (size_t i = 0; i < mlp->layers_width; i++) {
        printf("layer %zu\n", i);
        layer_print(mlp->layers[i]);
    }
}

Value** mlp_call(MultiLayerPerceptron* mlp, Value** x) {
    for (size_t i = 0; i < mlp->layers_width; i++) {
        x = layer_call(mlp->layers[i], x);
    }
    return x;
}
