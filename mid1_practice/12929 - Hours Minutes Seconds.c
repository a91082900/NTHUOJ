#include <stdio.h>
void calc(int M1, int D1, int h1, int m1, int s1, int M2, int D2, int h2, int m2, int s2) {
    int M = 0, D = 0, h = 0, m = 0, s = 0;
    s += s1 - s2;
    if(s < 0) {
        s += 60;
        m--;
    }

    m += m1 - m2;
    if(m < 0) {
        m += 60;
        h--;
    }

    h += h1 - h2;
    if(h < 0) {
        h += 24;
        D--;
    }

    D += D1 - D2;
    if(D < 0) {
        D += 30;
        M--;
    }

    M += M1 - M2;

    printf("%d %d\n%02d:%02d:%02d\n", M, D, h, m, s);

}
int main() {
    int M1, D1, h1, m1, s1;
    int M2, D2, h2, m2, s2;
    int aflag = 0;
    scanf("%d/%d %d:%d:%d", &M1, &D1, &h1, &m1, &s1);
    scanf("%d/%d %d:%d:%d", &M2, &D2, &h2, &m2, &s2);
    //printf("%d\n%d\n%d\n%d\n%d\n", M1, D1, h1, m1, s1);

    while(1) {
        if(M1 > M2) {
            aflag = 1;
            break;
        }
        else if(M1 < M2) {
            aflag = 0;
            break;
        }

        if(D1 > D2) {
            aflag = 1;
            break;
        }
        else if(D1 < D2) {
            aflag = 0;
            break;
        }

        if(h1 > h2) {
            aflag = 1;
            break;
        }
        else if(h1 < h2) {
            aflag = 0;
            break;
        }

        if(m1 > m2) {
            aflag = 1;
            break;
        }
        else if(m1 < m2) {
            aflag = 0;
            break;
        }

        if(s1 > s2) {
            aflag = 1;
            break;
        }
        else {
            aflag = 0;
            break;
        }
    }

    if(aflag) calc(M1, D1, h1, m1, s1, M2, D2, h2, m2, s2);
    else calc(M2, D2, h2, m2, s2, M1, D1, h1, m1, s1);
    return 0;
}
