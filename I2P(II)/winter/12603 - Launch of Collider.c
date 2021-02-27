#include <stdio.h>
typedef struct {
    int x1, x2;
} pair;

pair pairs[100005];
int nums[200005];
int main() {
    int n, idx = 0;
    scanf("%d", &n);
    char tmp, prev = '\0';
    for(int i = 0; i < n; i++) {
        scanf(" %c", &tmp);
        if(tmp == 'L' && prev == 'R') {
            pairs[idx].x1 = i-1;
            pairs[idx++].x2 = i;
        }
        prev = tmp;
    }
    for(int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    int shortest = (int) 2e9;
    for(int i = 0; i < idx; i++) {
        if(nums[pairs[i].x2] - nums[pairs[i].x1] < shortest)
            shortest = nums[pairs[i].x2] - nums[pairs[i].x1];
    }

    if(shortest == (int) 2e9)
        printf("-1\n");
    else
        printf("%d\n", shortest/2);
    return 0;
}
