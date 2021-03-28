#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int data;
    struct node *left, *right;
} Node;
long long sumLevel[10000];
int countLevel[10000];

void printInfix(Node *root) {
    if(root == NULL)
        return;
    printInfix(root->left);
    printf("%d ", root->data);
    printInfix(root->right);
}

int main() {
    Node *root = NULL, *ptr;
    int n, tmp, maxLevel = 0;
    scanf("%d", &n);
    if(n--) {
        scanf("%d", &tmp);
        root = malloc(sizeof(Node));
        root->data = tmp;
        root->left = root->right = NULL;
        sumLevel[1] += root->data;
        countLevel[1]++;
        maxLevel++;
    }
    int depth, same = 0;

    while(n-->0) {
        depth = 1;
        same = 0;
        ptr = root;
        scanf("%d", &tmp);
        while(1) {
            if(tmp > ptr->data) {
                depth++;
                if(ptr->right != NULL) {
                    ptr = ptr->right;
                }
                else {
                    ptr->right = malloc(sizeof(Node));
                    ptr = ptr->right;
                    break;
                }
            }
            else if(tmp < ptr->data) {
                depth++;
                if(ptr->left != NULL) {
                    ptr = ptr->left;
                }
                else {
                    ptr->left = malloc(sizeof(Node));
                    ptr = ptr->left;
                    break;
                }
            }
            else { // =
                same = 1;
                break;
            }
        }
        if(same)
            continue;
        ptr->data = tmp;
        ptr->left = ptr->right = NULL;
        sumLevel[depth] += ptr->data;
        countLevel[depth]++;
        if(depth > maxLevel)
            maxLevel = depth;
    }

    /*for(int i = 1; i <= 4; i++)
        printf("%d: %lld\n", i, sumLevel[i]);*/
    int q, num;

    char command[10];
    scanf("%d", &q);
    while(q--) {
        scanf("%s", command);
        if(command[0] == 'P') {
            if(root == NULL)
                printf("NULL");
            else
                printInfix(root);
            printf("\n");
        }
        else if(command[0] == 'S') {
            scanf("%d", &num);
            printf("%lld\n", sumLevel[num]);
        }
        else if(command[0] == 'A') {
            scanf("%d", &num);
            if(countLevel[num] == 0)
                printf("0\n");
            else
                printf("%.3f\n", (double) sumLevel[num] / countLevel[num]);
        }
        else { // getmax
            printf("%d\n", maxLevel);
        }
    }
    return 0;
}
