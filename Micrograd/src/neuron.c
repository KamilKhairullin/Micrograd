#include "neuron.h"
#include "value.h"
#include "utils.h"

Neuron* neuron_create(size_t inputSize) {
    Neuron* neuron = malloc(sizeof(Neuron));
    if(neuron == NULL) return NULL;
    
    neuron->weights = (Value**)malloc(sizeof(Value*) * inputSize);
    neuron->bias = value_create_labled(rnd(-1, 1), "b");
    neuron->inputSize = inputSize;
    for (size_t i = 0; i < inputSize; i++) {
        char* label = malloc(sizeof(char) * 8);
        sprintf(label, "w_%zu", i + 1);
        neuron->weights[i] = value_create_labled(rnd(-1, 1), label);
    }
    return neuron;
}

void neuron_print(Neuron* n) {
    printf("   bias: ");
    value_print(n->bias);
    for (size_t i = 0; i < n->inputSize; i++) {
        printf("   weight_%zu: ", i);
        value_print(n->weights[i]);
    }
}

Value* neuron_call(Neuron* n, Value** x) {
    Value* sum = value_create(n->bias->data);

    for (size_t i = 0; i < n->inputSize; i++) {
        Value* wixi = value_mul(n->weights[i], x[i]);
        sum = value_add(sum, wixi);
    }
    Value* out = value_tanh(sum);
    return out;
}

void neuron_params(Neuron* n, ArrayList* list) {
    for (size_t i = 0; i < n->inputSize; i++) {
        add(list, n->weights[i]);
    }
    add(list, n->bias);
}
