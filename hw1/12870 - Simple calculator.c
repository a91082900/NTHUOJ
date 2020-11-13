#include <stdio.h>

int main() {
    double a, b, res;
    char op;
    scanf("%lf%c%lf", &a, &op, &b);
    if(op == '+') res = a+b;
    else if(op == '-') res = a-b;
    else if(op == '*') res = a*b;
    else {
        if(b == 0.0) {
            printf("Error\n");
            return 0;
        }
        res = a/b;
    }

    printf("%.3lf\n", res);
    return 0;
}
