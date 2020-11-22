#include <stdlib.h>
#include "function.h"

unsigned*** new_3d_array(unsigned n,unsigned m,unsigned k) {
    //printf("sizeof unsigned** = %d\nsizeof unsigned* = %d\nsizeof unsigned = %d\n", sizeof(unsigned**), sizeof(unsigned*), sizeof(unsigned));
    unsigned ***arr = malloc(n * sizeof(unsigned **));
    unsigned **arr2 = malloc(n * m * sizeof(unsigned *));
    unsigned *arr3 = malloc(n * m * k * sizeof(unsigned));

    for(int i = 0; i < n; i++) {
        arr[i] = arr2 + i * m;
        //printf("arr[%d]: %p\n", i, arr2+i*m);
        for(int j = 0; j < m; j++) {
            arr[i][j] = arr3 + i * m * k + j * k;
            //printf("arr[%d][%d]: %p\n", i, j, arr3+j*k);
        }
    }

    return arr;
}
void delete_3d_array(unsigned ***arr) {
    free(arr[0][0]);
    free(arr[0]);
    free(arr);
}
