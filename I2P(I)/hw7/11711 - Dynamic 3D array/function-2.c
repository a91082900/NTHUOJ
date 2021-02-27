#include <stdlib.h>
#include "function.h"

unsigned*** new_3d_array(unsigned n,unsigned m,unsigned k) {
    unsigned ***arr = malloc(n*sizeof(unsigned **) + n*m*sizeof(unsigned *) + n*m*k*sizeof(unsigned));
    unsigned **ptr = (unsigned **) (arr + n);
    for(int i = 0; i < n; i++, ptr+=m) {
        arr[i] = ptr;

        unsigned *p = (unsigned *) ((unsigned **)(arr + n) + n * m) + i * m * k;
        for(int j = 0; j < m; j++, p+=k) {
            arr[i][j] = p;
        }
    }

    return arr;
}
void delete_3d_array(unsigned ***arr) {
    free(arr);
}
