#include <stdio.h>
#include <math.h>
#include "value.h"
#include "neuron.h"
#include "layer.h"
#include "multiLayerPerceptron.h"
#include "utils.h"
#include "lib/collections/hashTable/src/hashTable.h"
#include <time.h>

Value* calculate_loss(Value** predicted, Value** desired, int size) {
    Value* squareLoss = value_create(0);
    for (int i = 0; i < size; i ++) {
        Value* yout = predicted[i];
        Value* ygt = desired[i];
        Value* sub = value_sub(yout, ygt);
        Value* squareLoss_i = value_power(sub, 2);
        squareLoss = value_add(squareLoss, squareLoss_i);
    }
    return squareLoss;
}

int main(void) {
    srand((unsigned int)time(NULL));
    
    int x_train_size = 12;
    int y_train_size = x_train_size;
    Value** x_train[] = {
        (Value*[]){
            value_create(0.4), value_create(0.6)
        },
        (Value*[]){
            value_create(0.1), value_create(0.5)
        },
        (Value*[]){
            value_create(0.2), value_create(0.3)
        },
        (Value*[]){
            value_create(0.5), value_create(0.2)
        },
        (Value*[]){
            value_create(0.3), value_create(0.4)
        },
        (Value*[]){
            value_create(0.1), value_create(0.2)
        },
        (Value*[]){
            value_create(0.2), value_create(0.6)
        },
        (Value*[]){
            value_create(0.3), value_create(0.6)
        },
        (Value*[]){
            value_create(0.1), value_create(0.4)
        },
        (Value*[]){
            value_create(0.4), value_create(0.5)
        },
        (Value*[]){
            value_create(0.2), value_create(0.4)
        },
        (Value*[]){
            value_create(0.1), value_create(0.6)
        }
    };
    
    
    Value* y_train[] = {
        value_create(1),
        value_create(0.6),
        value_create(0.5),
        value_create(0.7),
        value_create(0.7),
        value_create(0.3),
        value_create(0.8),
        value_create(0.9),
        value_create(0.5),
        value_create(0.9),
        value_create(0.6),
        value_create(0.7)
    };
    
    
    size_t input_size = 2;
    size_t layer_sizes[] = {2, 4, 4, 1};
    size_t number_of_layers = 4;
    MultiLayerPerceptron* mlp = mlp_create(input_size, layer_sizes, number_of_layers);
    
    Value* y_predicted[y_train_size];
    for (int i = 0; i < y_train_size; i++) {
        y_predicted[i] = value_create(0);
    }
    
    for (size_t k = 0; k < 250; k++) {
        // pass input and get prediction
        // calculate backward
        for (int i =0; i < x_train_size; i ++) {
            Value* prediction = mlp_call(mlp, x_train[i])[0];
            y_predicted[i] = prediction;
        }
        // get all parameters
        ArrayList* list = createArrayList(1024);
        mlp_params(mlp, list);

        for (int i = 0; i < list->size; i++) {
            Value* p = get(list, i);
            p->grad = 0;
        }
        
        Value* loss = calculate_loss(y_predicted, y_train, 4);
        backward(loss);
        value_print(loss);
        
        // tune params
        for (int i = 0; i < list->size; i++) {
            Value* p = get(list, i);
            p->data += -0.05 * p->grad;
        }
    }
    
    printf("predictions: \n");
    for (int i = 0; i < y_train_size; i++) {
        printf("was");
        printf(" %0.5f ", y_train[i] ->data);
        printf("predicted");
        printf("%0.5f \n", y_predicted[i] ->data);
    }

    printf("real prediction: \n");
    
    Value** real_x[]= {
        (Value*[]){
            value_create(0.3), value_create(0.5)
        },
        (Value*[]){
            value_create(0.1), value_create(0.3)
        },
        (Value*[]){
            value_create(0.2), value_create(0.5)
        },
        (Value*[]){
            value_create(0.17), value_create(0.13)
        }
    };
    
    Value* y_real[] = {
        value_create(0.7),
        value_create(0.4),
        value_create(0.7),
        value_create(0.3)
    };
    
    for (int i = 0; i < 4; i++) {
        Value* realPrediction = mlp_call(mlp, real_x[i])[0];
        printf("was");
        printf(" %0.5f ", y_real[i] ->data);
        printf("predicted");
        printf(" %0.5f \n", realPrediction->data);
    }
}

