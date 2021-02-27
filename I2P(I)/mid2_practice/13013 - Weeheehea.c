#include <stdio.h>
int strs[5200] = {};
int main() {
    int n, offset = -1, num = 0;
    char tmp[15];
    scanf("%d", &n);
    while(n--) {
        scanf("%s", tmp);
        offset = -1, num = 0;
        for(int i = 0; i < 10; i++) {
            if(tmp[i] == 'x')
                offset = i * 512;
            else if(tmp[i] == '1') {
                //printf("i = %d, num += 2^%d\n", i, (i - (bit != -1)));
                num += 1 << (i - (offset != -1));
            }
        }
        //printf("bit = %d, num = %d\n", bit, num);
        strs[offset + num] += 1;
    }
    int ans = 0;
    for(int i = 0; i < 5120; i++) {
        if(strs[i])
            ans++;
    }
    printf("%d\n", ans);
    return 0;
}
