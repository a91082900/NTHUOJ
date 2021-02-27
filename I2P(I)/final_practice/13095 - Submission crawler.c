#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100001
typedef struct {
    int id, solved, penalty, tried[10], problems[10];
} User;

User users[MAX + 5];
int n = 0;

int cmp(const void*, const void*);
int main() {
    char s[101], problem, status[101];
    int user, h, m;
    for(int i = 0; i < 10; i++) {
        fgets(s, 101, stdin);
    }
    while(1) {
        scanf("%s", s);
        if(strcmp(s, "</tbody>") == 0)
            break;
        scanf(" <td> %d:%d </td>", &h, &m);
        //printf(":%d\n", h*60+m);
        scanf(" <td> %d </td>", &user);
        //printf(":%d\n", user);
        scanf(" <td> %c </td>", &problem);
        //printf(":%c\n", problem);
        scanf(" <td> ");
        fgets(status, 101, stdin);
        //printf("%s\n", status);
        fgets(s, 101, stdin); // </tr>

        if(!users[user].id) {
            if(user == 0)
                users[0].id = -1;
            else
                users[user].id = user;
        }
        if(!users[user].problems[problem-'A']) {
            if(status[0] == 'A') {
                users[user].solved++;
                if(h == 0 && m == 0 && users[user].tried[problem-'A'] == 0) {
                    users[user].problems[problem-'A'] = -1;
                }
                else {
                    users[user].problems[problem-'A'] = h*60 + m + 20*users[user].tried[problem-'A'];
                    users[user].penalty += users[user].problems[problem-'A'];
                }
            }
            users[user].tried[problem-'A']++;
        }

        //printf("\nNext Loop\n");
    }
    //printf("HERE\n");
    scanf("%s", s);
    //printf("HERE2\n");
    qsort(users, MAX, sizeof(User), cmp);
    for(int i = 0; i < MAX; i++) {
        if(users[i].id) {
            /*
            4 2/80 1/9 -/- -/- -/- -/- -/- -/- -/- -/- 2 89
            3 1/21 -/- -/- -/- -/- -/- -/- -/- -/- -/- 1 21
            7 -/- -/- -/- 1/- -/- -/- -/- -/- -/- -/- 0 0
            */
            if(users[i].id == -1)
                users[i].id = 0;
            printf("%d ", users[i].id);
            for(int j = 0; j < 10; j++) {
                if(users[i].tried[j])
                    printf("%d/", users[i].tried[j]);
                else
                    printf("-/");
                if(users[i].problems[j]) {
                    if(users[i].problems[j] == -1)
                        printf("0 ");
                    else
                        printf("%d ", users[i].problems[j]);
                }
                else
                    printf("- ");
            }
            printf("%d %d\n", users[i].solved, users[i].penalty);
        }
    }
    return 0;
}

int cmp(const void *user_a, const void *user_b) {
    User a = *(User *) user_a;
    User b = *(User *) user_b;
    if(a.id == 0 && b.id == 0)
        return 0;
    else if(b.id == 0)
        return -1;
    else if(a.id == 0)
        return 1;

    if(a.solved > b.solved)
        return -1;
    else if(b.solved > a.solved)
        return 1;
    else {
        if(a.penalty < b.penalty)
            return -1;
        else if(b.penalty < a.penalty)
            return 1;
        else {
            if(a.id < b.id)
                return -1;
            else
                return 1;
        }
    }
}
