#include <stdio.h>
#include "value.h"

int main(int argc, const char * argv[]) {
    printf("Hello, World!\n");
    Value* v1 = value_create(2.0);
    Value* v2 = value_create(-3.0);
    Value* v3 = value_add(v1, v2);
    value_print(v3);
    return 0;
}
