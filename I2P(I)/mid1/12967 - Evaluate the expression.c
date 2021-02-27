#include<stdio.h>

int main(){
    long long answer = 0, num = 0;
    int sign = 1;
    int reverse = 0;
    while(1){
        char a;
        switch(a = getchar()){
        case '\n':
            printf("%lld\n",answer);
            return 0;
        case '+':
            sign = 1;
            break;

        case '-':
            sign = 0;
            break;

        case '(':
            if(sign == 0){
                answer = -answer;
                reverse = 1;
                sign = 1;
            }
            break;

        case ')':
            if(reverse == 1){
                answer=-answer;
                reverse = 0;
            }
            break;

        default:
            ungetc(a, stdin);
            scanf("%lld", &num);
            //printf("read number: %d\n", num);
            if(sign){
                answer += num;
            }
            else {
                answer -= num;
            }
            break;
        }
    }
}
