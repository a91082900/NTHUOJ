#include <stdio.h>
#include <stdlib.h>
#include "function.h"
int main(){
    int n, a;
    scanf("%d", &n);
    while(n--){
        scanf("%d", &a);
        add_node(a);
    }
    showtree(tree_head);
}
