#include <stdio.h>

char a[105], b[105];
int result[102] = {0};
int cmp(int la, int lb) {
    if(lb > la)
        return 1;
    else if(la > lb)
        return -1;
    else {
        for(int i = 0; i < la; i++) {
            if(b[i] > a[i])
                return 1;
            else if(a[i] > b[i])
                return -1;
        }
        return 0;
    }
}
int sub(char* large, char* little, int l_large, int l_little) { // large - little

    int borrow = 0;
    for(int i = 1; i <= l_little; i++) {
        if(large[l_large-i] - borrow < little[l_little-i]) {
            //printf("large[%d] - little[%d] = %d\n", l_large-i, l_little-i, large[l_large-i] - little[l_little-i] + 10 - borrow);
            result[i-1] = large[l_large-i] - little[l_little-i] + 10 - borrow;
            borrow = 1;
        }
        else {
            //printf("large[%d] - little[%d] = %d\n", l_large-i, l_little-i, large[l_large-i] - little[l_little-i] - borrow);
            result[i-1] = large[l_large-i] - little[l_little-i] - borrow;
            borrow = 0;
        }
    }
    int i;
    for(i = l_little+1; i <= l_large; i++) {
        if(large[l_large-i] - borrow < '0') {
            //printf("large[%d] = %d\n", l_large-i, large[l_large-i] - '0' - borrow + 10);
            result[i-1] = large[l_large-i] + 10 - borrow - '0';
            borrow = 1;
        }
        else {
            //printf("large[%d] = %d\n", l_large-i, large[l_large-i] - '0' - borrow);
            result[i-1] = large[l_large-i] - borrow - '0';
            borrow = 0;
        }
    }
    return i-1;
}

int main() {

    int la, lb, size;
    scanf("%d %s %d %s", &la, a, &lb, b);
    int cmp_val = cmp(la, lb);
    if(cmp_val < 0) {
        size = sub(a, b, la, lb);
    }
    else if(cmp_val > 0) {
        size = sub(b, a, lb, la);
        printf("-");
    }
    else {
        printf("0");
        return 0;
    }
    int flag = 1;
    for(int i = size; i >= 0; i--) {
        if(result[i] == 0 && flag)
            continue;
        flag = 0;
        printf("%d", result[i]);
    }
    return 0;
}
