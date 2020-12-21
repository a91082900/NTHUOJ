#include "function.h"
#include <stdlib.h>
#include <string.h>
char* name_start;
Monkey* CreateMonkeyArray(int length) {
    Monkey* monkeys = malloc(length * sizeof(Monkey));
    char* names = malloc(length * 55 * sizeof(char));
    name_start = names;
    for(int i = 0; i < length; i++) {
        monkeys[i].name = names + 55*i;
    }

    return monkeys;
}
void FreeMonkeyArray(Monkey* monkeys, int length) {

    free(name_start);
    free(monkeys);
}
void SetVal(Monkey* monkeys, int i, int num, char* name) {
    //printf("Set %d to (%d, %s)\n", i, num, name);
    monkeys[i].num = num;
    strcpy(monkeys[i].name, name);
    //printf("%d : (%d, %s)\n", i, monkeys[i].num, monkeys[i].name);
}
int Compare(Monkey* monkeys, int i , int j) {
    if(monkeys[j].num > monkeys[i].num)
        return 1;
    else if(monkeys[j].num < monkeys[i].num)
        return 0;
    else
        return strcmp(monkeys[j].name, monkeys[i].name);

}
void Swap(Monkey* monkeys, int i , int j) {
    Monkey tmp = monkeys[i];
    monkeys[i] = monkeys[j];
    monkeys[j] = tmp;
}


