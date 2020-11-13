#include <stdio.h>

void hanoi(int n, char from, char to, char other) {
    if(n > 1) {
        hanoi(n-1, from, other, to);
        printf("move disk %d from rod %c to rod %c\n", n, from, to);
        hanoi(n-1, other, to, from);
    }
    else {
        printf("move disk 1 from rod %c to rod %c\n", from, to);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    hanoi(n, 'A', 'C', 'B');
    return 0;
}
