#include <iostream>
#include "function.h"

Polynomial::Polynomial() {
    this->greatestPower = 0;
    for(int i = 0; i < 101; i++)
        coefficients[i] = 0;
}
Polynomial::Polynomial(const int greatestPower, const int coefficients[51]) {
    this->greatestPower = greatestPower;

    for(int i = 100; i > greatestPower; i--) {
        this->coefficients[i] = 0;
    }
    for(int i = greatestPower; i >= 0; i--) {
        this->coefficients[i] = coefficients[i];
    }
}
Polynomial Polynomial::add(const Polynomial b) const {
    int addGreatest;
    int coeff[100];
    if(b.greatestPower > this->greatestPower)
        addGreatest = b.greatestPower;
    else
        addGreatest = this->greatestPower;

    for(int i = addGreatest; i >= 0; i--) {
        coeff[i] = this->coefficients[i] + b.coefficients[i];
    }
    return Polynomial(addGreatest, coeff);
}
Polynomial Polynomial::subtract(const Polynomial b) const {
    int subGreatest;
    int coeff[51];
    if(b.greatestPower > this->greatestPower)
        subGreatest = b.greatestPower;
    else
        subGreatest = this->greatestPower;
    for(int i = subGreatest; i >= 0; i--) {
        //std::cout << "a[" << i << "] = " << this->coefficients[i] << '\n';
        //std::cout << "b[" << i << "] = " << b.coefficients[i] << '\n';
        coeff[i] = this->coefficients[i] - b.coefficients[i];
    }
    while(!coeff[subGreatest])
        subGreatest--;
    return Polynomial(subGreatest, coeff);
}
Polynomial Polynomial::multiplication(const Polynomial b) const {
    int mulGreatest = this->greatestPower + b.greatestPower;
    int coeff[101] = {0};
    for(int i = 0; i <= this->greatestPower; i++) {
        for(int j = 0; j <= b.greatestPower; j++) {
            coeff[i+j] += this->coefficients[i] * b.coefficients[j];
        }
    }
    return Polynomial(mulGreatest, coeff);
}
void Polynomial::output() const {
    for(int i = greatestPower; i >= 0; i--) {
        std::cout << this->coefficients[i] << (i == 0 ? "": " ");
    }
}
