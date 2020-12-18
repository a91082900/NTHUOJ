#include "function.h"
#include <stdlib.h>

int** malloc_ptr(int array_size) {
    int** ptr = (int **) malloc(array_size * sizeof(int *));
    return ptr;
}
void malloc_array(int **array, int array_size) {
    *array = (int *) malloc(array_size * sizeof(int));
}
void pointer_ptr_to_array(int *array, int **ptr,int N) {
    int cnt = 0, idx = 0;
    for(int i = 0; i < N; i++) {
        idx += cnt;
        ptr[i] = &array[idx];
        cnt++;
    }
}