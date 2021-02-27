#include <stdio.h>

int is_leap(int y) {
    if(!(y % 400))
        return 1;
    if(!(y % 100))
        return 0;
    if(!(y % 4))
        return 1;
    return 0;
}
int calender[100001];
int main() {
    int q, y;
    // 2021: not leap, 1/1 Fri.
    // 1000: not leap, 1/1 Wed.
    int start_day = 3, leap = 0, prev_leap = 0;
    calender[1000] = 3;
    for(int i = 1000; i < 100000; i++) {
        // for next start_day: use prev_leap
        // for calender state: use leap
        prev_leap = leap;
        leap = is_leap(i+1);
        if(prev_leap)
            start_day = (start_day + 366) % 7;
        else
            start_day = (start_day + 365) % 7;
        calender[i+1] = start_day + leap * 7;
        //printf("%d's calender is %d\n", i+1, calender[i+1]);
    }

    scanf("%d", &q);
    while(q--) {
        scanf("%d", &y);
        for(int i = y+1; i <= 100000; i++) {
            if(calender[i] == calender[y]) {
                printf("%d\n", i);
                break;
            }
        }
    }
    return 0;
}
