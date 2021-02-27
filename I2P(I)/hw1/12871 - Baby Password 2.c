#include <stdio.h>

int main() {
    int c, d;
    scanf("%c %d", &c, &d);
    if(c >= 'A' && c <= 'Z') { // originally uppercase
        c = c- 'A' + 'a' - d;

        if(c > 'z') c -= 26;
        else if(c < 'a') c += 26;
    }
    else {
        c = c - 'a' + 'A' - d;
        if(c > 'Z') c -= 26;
        else if(c < 'A') c += 26;
    }

    printf("%c\n", c);
    return 0;
}
