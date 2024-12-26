#ifndef neuron_h
#define neuron_h

#include <stdio.h>
#include <string.h>
#include "value.h"

typedef struct Neuron {
    Value** weights;
    Value* bias;
    size_t inputSize;
} Neuron;

Neuron* neuron_create(size_t input_size);

void neuron_print(Neuron* n);

Value* neuron_call(Neuron* n, Value** x);

void neuron_params(Neuron* n, ArrayList* list);
#endif
