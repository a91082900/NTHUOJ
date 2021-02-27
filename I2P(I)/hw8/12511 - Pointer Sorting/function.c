#include "function.h"
#include <stdlib.h>
#include <math.h>


void msort(int* s, int len) {
    if(len == 1)
        return;
    if(len == 2) {
        if(s[0] > s[1]){
            int tmp = s[0];
            s[0] = s[1];
            s[1] = tmp;
        }
        return;
    }
    
    int half = len/2;
    msort(s, half);
    msort(s+half, len-half);
    int m[len], l_idx = 0, r_idx = 0;
    for(int i = 0; i < len; i++) {
        if(l_idx != half && (r_idx == len-half || s[l_idx] <= *(s+half+r_idx))) {
            m[i] = s[l_idx];
            l_idx++;
        }
        else {
            m[i] = *(s+half+r_idx);
            r_idx++;
        }
    }
    for(int i = 0; i < len; i++) {
        s[i] = m[i];
    }
}

int** s(int* ptr, int len) {
    msort(ptr, len);
    int side = sqrt(len), cnt = 0;

    int** mat = (int **) malloc(side * sizeof(int *) + len * sizeof(int));
    int* p = (int *) (mat+side);
    for(int i = 0; i < side; i++, p+=side) {
        mat[i] = p;
        for(int j = 0; j < side; j++) {
            mat[i][j] = ptr[cnt++];
        }
    }
    return mat;
}