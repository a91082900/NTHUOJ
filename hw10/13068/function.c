#include "function.h"

int cmp(const void* a, const void* b) {
    int *num_a = (int*) a;
    int *num_b = (int*) b;
    if(*num_a <*num_b)
        return 1;
    else if(*num_a > *num_b)
        return -1;
    else
        return 0;
}
