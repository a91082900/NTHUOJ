#include "function.h"
#define abs(x) ((x > 0) ? x : -(x))
void msort(long long* s[], int len) {

    if(len == 1)
        return;

    int half = len/2;
    msort(s, half);
    msort(s+half, len-half);
    long long m[505], l_idx = 0, r_idx = 0;
    for(int i = 0; i < len; i++) {
        if(l_idx != half && (r_idx == len-half || *(s[l_idx]) <= *(s[half+r_idx]))) {
            m[i] = *(s[l_idx]);
            l_idx++;
        }
        else {
            m[i] = *(s[half+r_idx]);
            r_idx++;
        }
    }
    for(int i = 0; i < len; i++) {
        *s[i] = m[i];
    }
}

void array2d_sort(int row, int col, long long arr[][500]) {
    // type of arr is (int*)[500]
    // arr[row-1][0]
    // arr[row-2][0], arr[row-1][1]
    // arr[row-3][0], arr[row-2][1], arr[row-1][2]
    // ...
    // arr[0][0], arr[1][1], ..., arr[][]
    // arr[0][1], arr[1][2], ...
    // length of each diagnal <= min(row, col)
    long long* a[505];
    int length = 1, tmp = 0;
    int i = 0;
    for(; i < row+col-1 && length < row && length < col; i++) {

        for(int j = 0; j < length; j++) {
            a[j] = &arr[row-1-i+j][j];
        }
        msort(a, length);
        length++;
    }

    for(; i < row+col-1 && (row+col-1) - i >= length; i++) {
        for(int j = 0; j < length; j++) {
            //printf("(%d, %d)\n", row-col, abs(row-col));
            if(row > col)
                a[j] = &arr[abs(row-col)+j-tmp][j];
            else
                a[j] = &arr[j][j+tmp];
        }
        msort(a, length);
        tmp++;
    }
    for(; i < row+col-1; i++) {
        length--;
        for(int j = 0; j < length; j++) {
            a[j] = &arr[j][col-length+j];
        }
        msort(a, length);
    }

}
