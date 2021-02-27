#include <stdio.h>

int tmp, max = 0, min = (int) 1e9;
int main() {
    int n;
    scanf("%d", &n);

    for(int i = 0; i <= n; i++) {
        scanf("%d", &tmp);
        if(tmp > max)
            max = tmp;
        if(tmp < min)
            min = tmp;
    }
    printf("%d\n", 2*(max - min));
    return 0;
}
