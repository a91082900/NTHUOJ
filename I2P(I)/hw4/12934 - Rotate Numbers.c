#include <stdio.h>

char n[105], res[105];
int main() {
    scanf("%s", n);
    int size = 100;
    for(;;size--) {
        if(n[size-1])
            break;
    }
    //printf("%d\n", size);
    for(int i = 1; i <= size; i++) {
        char c = 0;
        int flag = 1;
        switch(n[size-i]) {
            case '0':
                c = '0';
                break;
            case '1':
                c = '1';
                break;
            case '6':
                c = '9';
                break;
            case '8':
                c = '8';
                break;
            case '9':
                c = '6';
                break;
            case '2':
            case '3':
            case '4':
            case '5':
            case '7':
                flag = 0;
                break;

        }
        if(!flag) {
            printf("No\n");
            return 0;
        }
        else {
            res[i-1] = c;
        }
    }

    int zeroflag = 1;
    for(int i = 0; i < size; i++) {
        if(res[i] == '0' && zeroflag)
            continue;
        printf("%c", res[i]);
        zeroflag = 0;
    }
    printf("\n");

    return 0;
}
