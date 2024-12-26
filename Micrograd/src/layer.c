#include "layer.h"

Layer* layer_create(size_t neuron_input_size, size_t number_of_neurons) {
    Layer* layer = malloc(sizeof(Layer));
    if(layer == NULL) return NULL;
    layer->neurons_size = number_of_neurons;
    layer->neurons = malloc(sizeof(Neuron) * number_of_neurons);
    if(layer->neurons == NULL) return NULL;
    
    for (size_t i = 0; i < number_of_neurons; i++) {
        layer->neurons[i] = neuron_create(neuron_input_size);
    }
    return layer;
}

Value** layer_call(Layer* l, Value** x) {
    size_t neurons_size = l->neurons_size;
    Value** out = malloc(sizeof(Value) * neurons_size);
    for (size_t i = 0; i < neurons_size; i++) {
        out[i] = neuron_call(l->neurons[i], x);
    }
    return out;
}

void layer_print(Layer* l) {
    for(size_t i = 0; i < l->neurons_size; i++) {
        printf("  neuron %zu\n", i);
        neuron_print(l->neurons[i]);
    }
}
