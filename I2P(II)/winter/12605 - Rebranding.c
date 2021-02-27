#include <stdio.h>

char mapping[30], name[200005];
int main() {
    for(int i = 0; i < 26; i++) {
        mapping[i] = i + 'a';
    }

    int n, m;
    char x, y;
    scanf("%d %d ", &n, &m);
    fgets(name, 200001, stdin);
    //printf("\"%s\"\n\n", name);
    for(int i = 0; i < m; i++) {
        scanf(" %c %c", &x, &y);
        if(x == y)
            continue;
        for(int i = 0; i < 26; i++) {
            if(mapping[i] == x) {
                mapping[i] = y;
                for(int j = i+1; j < 26; j++) {
                    if(mapping[j] == y) {
                        mapping[j] = x;
                        break;
                    }
                }
                break;
            }
            if(mapping[i] == y) {
                mapping[i] = x;
                for(int j = i+1; j < 26; j++) {
                    if(mapping[j] == x) {
                        mapping[j] = y;
                        break;
                    }
                }
                break;
            }
        }
    }
    /*for(int i = 0; i < 26; i++) {
        printf("%c -> %c\n", i+'a', mapping[i]);
    }*/
    for(int i = 0; i < n; i++) {
        printf("%c", mapping[name[i]-'a']);
    }
    printf("\n");
    return 0;
}
