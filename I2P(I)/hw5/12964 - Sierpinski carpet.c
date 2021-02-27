#include <stdio.h>

char carpet[2200][2200];
int pow(int base, int exp) {
    if(exp == 0)
        return 1;
    else if(exp == 1)
        return base;
    if(exp % 2) {
        return base*pow(base, exp-1);
    }
    else {
        int tmp = pow(base, exp/2);
        return tmp*tmp;
    }
}
void fill_sharp(int side, int i, int j) {
    for(int k = 0; k < side; k++)
        for(int l = 0; l < side; l++)
            carpet[i+k][j+l] = '#';
}
void construct(int n, int i, int j) {
    if(n == 1) {
        for(int k = 0; k < 3; k++) {
            for(int l = 0; l < 3; l++) {
                if(k == 1 && l == 1) {
                    carpet[k+i][l+j] = '#';
                }
                else {
                    carpet[k+i][l+j] = '.';
                }
            }
        }
    }
    else {
        for(int k = 0; k < 3; k++) {
            for(int l = 0; l < 3; l++) {
                int side = pow(3, n-1);
                if(k == 1 && l == 1) {
                    fill_sharp(side, i+side, j+side);
                }

                else {
                    construct(n-1, i+k*side, j+l*side);
                }
            }
        }
    }

}
int main() {
    int n, side;
    scanf("%d", &n);
    construct(n, 0, 0);
    side = pow(3, n);
    for(int i = 0; i < side; i++) {
        for(int j= 0; j < side; j++) {
            printf("%c", carpet[i][j]);
        }
        printf("\n");
    }
    return 0;
}
