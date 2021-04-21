#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;
    int cnt = 0;
    for(int i = 0; i < s.size(); i++) {
        if(i+1 < s.size() && s[i] == s[i+1] && s[i] != '*') {
            cnt++;
            s[i+1] = '*';
        }
        if(i+2 < s.size() && s[i] == s[i+2] && s[i] != '*') {
            cnt++;
            s[i+2] = '*';
        }
    }

    cout << cnt << '\n';
    return 0;
}
