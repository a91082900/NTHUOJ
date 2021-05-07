#include "function.h"
#include <cstring>

using namespace oj;

BigInt::BigInt(char *s) {
    _val = new char[1100];
    strcpy(_val, s);
}

BigInt::~BigInt() {
    delete[] _val;
}

BigInt& BigInt::operator++() { // ++B
    int sz = strlen(_val);
    int i = sz-1;
    while(_val[i] == '9' && i >= 0) {
        _val[i] = '0';
        i--;
    }
    if(i != -1)
        _val[i] += 1;
    else {
        char *new_val = new char[1100];
        strcpy(new_val, "1");
        strcat(new_val, _val);
        delete[] _val;
        _val = new_val;
    }
    return *this;
}
BigInt BigInt::operator++(int) { // B++
    BigInt temp(_val);
    operator++();
    return temp;
}
BigInt& BigInt::operator--() { // --B
    int sz = strlen(_val);
    int i = sz-1;
    if(sz == 1 && _val[0] == '0')
        return *this;
    else if(sz == 1 && _val[0] == '1') {
        _val[0] = '0';
        return *this;
    }
    while(_val[i] == '0' && i >= 0) {
        _val[i] = '9';
        i--;
    }
    if(i != 0 || _val[0] != '1')
        _val[i] -= 1;
    else {
        char *new_val = new char[1100];
        strcpy(new_val, _val+1);
        delete[] _val;
        _val = new_val;
    }
    return *this;
}

BigInt BigInt::operator--(int) { // B--
    BigInt temp(_val);
    operator--();
    return temp;
}

char* BigInt::to_s() {
    return _val;
}
