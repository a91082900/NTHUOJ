#include <iostream>

using namespace std;
int board[11][11] = {0}; // 0 for nothing, 1 for rock, 2 for queen
int M, N, cnt = 0;

bool check(int i_chk, int j_chk, bool isqueen) { // m, n means the remain number of queens and rocks
    for(int i = 0; i < i_chk; i++) {
        for(int j = 0; j < M+N; j++) {
            if(board[i][j] == 1) { // check vertically
                if(j == j_chk)
                    return false;
                if((i+j) == (i_chk+j_chk) && isqueen) // if queen is placed it will threaten this rock
                    return false;
                else if((i-j) == (i_chk-j_chk) && isqueen)
                    return false;
            }
            else if(board[i][j] == 2) { // check obliquely
                if(j == j_chk)
                    return false;
                if((i+j) == (i_chk+j_chk))
                    return false;
                else if((i-j) == (i_chk-j_chk))
                    return false;
            }
        }
    }

    for(int i = 0; i < M+N; i++) {
        for(int j = 0; j < M+N; j++) {
            //cout << board[i][j] << " \n"[j==M+N-1];
        }
    }
    //cout << "placed an " << (isqueen ? "queen": "rock") << " at (" << i_chk << ", " << j_chk << ")\n\n";

    return true;
}
void backtrace(int line) {
    //cout << "backtrace for line " << line << "\n";
    for(int k = 0; k < M+N; k++) {
        board[line][k] = 0;
    }
}
void queen(int line, int m, int n) {
    for(int j = 0; j < M+N; j++) {
        if(m > 0 && check(line, j, true)) {
            if(line == M+N-1) {
                cnt++;
                // backtracing
                backtrace(line);
                return;
            }
            board[line][j] = 2;
            queen(line+1, m-1, n);
            backtrace(line);
        }
        if(n > 0 && check(line, j, false)) {
            if(line == M+N-1) {
                cnt++;
                // backtracing
                backtrace(line);
                return;
            }
            board[line][j] = 1;
            queen(line+1, m, n-1);
            backtrace(line);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> M >> N;
    if(M == 0) {
        int ans = 1;
        while(N>0) {
            ans*= N;
            N--;
        }
        cout << ans << '\n';
        return 0;
    }
    queen(0, M, N);
    cout << cnt << '\n';
    return 0;
}
