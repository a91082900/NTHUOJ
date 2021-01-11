#include <stdio.h>
#include <stdlib.h>
typedef struct cell {
    int n;
    struct cell *portal[4];
} Cell;

int main() {
    int q, op;
    int dir, val, idx = 0;
    Cell *now = (Cell *) malloc(sizeof(Cell)), *dp = now;
    now->n = 0;
    scanf("%d", &q);

    while(q--) {
        scanf("%d", &op);
        switch(op) {
            case 1:
                scanf("%d %d", &dir, &val);
                Cell *c = (Cell *) malloc(sizeof(Cell));
                now->portal[dir] = c;
                c->n = val;
                if(dir > 1)
                    c->portal[dir-2] = now;
                else
                    c->portal[dir+2] = now;
                break;
            case 2:
                scanf("%d", &dir);
                now = now->portal[dir];
                break;
            case 3:
                scanf("%d", &val);
                now->n = val;
                break;
            case 4:
                printf("%d\n", now->n);
                break;
            case 5:
                dp = now;
                break;
            case 6:
                now = dp;
                break;

        }
    }
    return 0;
}
