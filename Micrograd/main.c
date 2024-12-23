#include <stdio.h>
#include "value.h"

int main(int argc, const char * argv[]) {
    printf("Hello, World!\n");
    Value* v = value_create(50.0);
    value_print(v);
    return 0;
}
