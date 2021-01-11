#include <stdio.h>
#include <stdlib.h>
typedef struct _node {
    int data, len;
    struct _node **children;
} Node;
int X[100005], Y[100005], cnt[100005];
Node *ptr[100005];
int result[100005];
int calc(int idx) {
    if(result[idx])
        return result[idx];
    int ans = 1;
    for(int i = 0; i < ptr[idx]->len; i++) {
        ans += calc(ptr[idx]->children[i]->data);
    }
    //result[idx] = ans;
    return ans;
}
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i < n; i++) {
        scanf("%d %d", &X[i], &Y[i]);
        cnt[X[i]]++;
        cnt[Y[i]]++;
    }
    for(int i = 1; i <= n; i++) {
        ptr[i] = calloc(1, sizeof(Node));
        ptr[i]->data = i;
        ptr[i]->children = calloc(cnt[i], sizeof(Node*));
    }
    for(int i = 1; i < n; i++) {
        ptr[X[i]]->children[ptr[X[i]]->len++] = ptr[Y[i]];
    }
    for(int i = 1; i <= n; i++) {
        printf("%d%c", calc(i)-1, " \n"[i==n]);
    }
    return 0;
}
