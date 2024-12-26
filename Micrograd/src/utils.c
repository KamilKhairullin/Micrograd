#include "utils.h"
#include <stdlib.h>
#include <time.h>

static int seed_initialized = 0;

double rnd(int minNumber, int maxNumber) {
    if (!seed_initialized) {
        srand((size_t)clock() * time(NULL));
        seed_initialized = 1;
    }
    
    return minNumber + ((double)rand() / (double)RAND_MAX) * (maxNumber - minNumber);
}


