#include <stdio.h>
char s[500005], c[6];
int main() {
    fgets(s, 500005, stdin);
    int idx = 0, back = 0;
    while(fgets(c, 5, stdin) != NULL) {
        if(back) {
            if(c[0] == '\\' && c[1] == 'b') {
                back--;
                printf("%d\n", back==0);
            }
            else {
                back++;
                printf("0\n");
            }
        }
        else {
            if(c[0] == s[idx]) {
                idx++;
                printf("1\n");
            }
            else if(c[0] == '\\' && c[1] == 'b') {
                if(idx > 0)
                    idx--;
                printf("1\n");
            }
            else {
                back++;
                printf("0\n");
            }
        }
    }
    if(s[idx] == '\n' && !back)
        printf("Correct\n");
    else
        printf("Incorrect\n");
}
