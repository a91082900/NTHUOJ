#include "function.h"

special_power::special_power(int n) {
    this->n = n;
}
int special_power::fpow(int x) {
    return fpow(x, 880301);
}
int special_power::fpow(int x, int m) {
    long long ans = 1;
    for(int i = 0; i < n; i++) {
        ans = (ans * (x % m)) % m;
    }
    return static_cast<int>(ans);
}
int special_power::fpow() {
    //2^n % 880301
    return fpow(2);
}
string special_power::fpow(string s) {
    string ans = "";
    for(int i = 0; i < s.size(); i++) {
        for(int j = 0; j < n; j++)
            ans += s[i];
    }
    return ans;
}
string special_power::fpow(string s, int m) {
    string ans = "";
    int len = 0;
    for(int i = 0; i < s.size(); i++) {
        for(int j = 0; j < n; j++) {
            ans += s[i];
            if(++len >= m) {
                return ans;
            }
        }
    }
    return ans;
}
