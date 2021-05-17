#include "function.h"
#include <sstream>
using namespace std;
void RleCodec::encode() {
    char prev;
    string enc_str = "";
    stringstream ss;
    int cnt = 1;
    if(code_str.size())
        prev = code_str[0];
    for(int i = 1;  i < code_str.size(); i++) {
        if(code_str[i] == prev)
            cnt++;
        else {
            if(cnt > 2) {
                ss << cnt;
                ss << prev;
            }
            else if(cnt == 2) {
                ss << prev << prev;
            }
            else {
                ss << prev;
            }
            prev = code_str[i];
            cnt = 1;
        }
    }

    if(cnt > 2) {
        ss << cnt;
        ss << prev;
    }
    else if(cnt == 2) {
        ss << prev << prev;
    }
    else {
        ss << prev;
    }

    ss >> code_str;
    encoded = true;
}

void RleCodec::decode() {
    string num, result = "";
    stringstream ss;
    int cnt = 1;
    for(int i = 0; i < code_str.size(); i++) {
        if(code_str[i] >= '0' && code_str[i] <= '9') {
            num += code_str[i];
        }
        else {
            if(num.size()) {
                ss << num;
                ss >> cnt;
                ss.str("");
                ss.clear();
            }
            result += string(cnt, code_str[i]);
            num = "";
            cnt = 1;
        }
    }
    code_str = result;
    encoded = false;
}
