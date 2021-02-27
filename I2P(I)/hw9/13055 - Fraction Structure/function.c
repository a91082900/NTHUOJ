#include "function.h"

Fraction CreateFrac(long long numerator, long long demoninator) {
    Fraction f;
    f.numerator = numerator;
    f.denominator = demoninator;
    return f;
}

long long gcd(long long a, long long b) {
    long long tmp;
    while(b) {
        a %= b;
        tmp = a;
        a = b;
        b = tmp;
    }
    return a;
}

long long lcm(long long a, long long b) {
    return a*b/gcd(a, b);
}

void Reduction(Fraction* f) {
    long long g = gcd(f->numerator, f->denominator);
    f->numerator = f->numerator / g;
    f->denominator = f->denominator / g;
}
Fraction Add(Fraction a, Fraction b) {
    long long l = lcm(a.denominator, b.denominator);
    a.numerator *= (l/a.denominator);
    b.numerator *= (l/b.denominator);
    Fraction f = {a.numerator+b.numerator, l};
    Reduction(&f);
    return f;
}
Fraction Sub(Fraction a, Fraction b) {
    long long l = lcm(a.denominator, b.denominator);
    a.numerator *= (l/a.denominator);
    b.numerator *= (l/b.denominator);
    Fraction f = {a.numerator-b.numerator, l};
    Reduction(&f);
    return f;
}
Fraction Mul(Fraction a, Fraction b) {
    Fraction f = {a.numerator*b.numerator, a.denominator*b.denominator};
    Reduction(&f);
    return f;
}
Fraction Div(Fraction a, Fraction b) {
    Fraction f = {a.numerator*b.denominator, a.denominator*b.numerator};
    Reduction(&f);
    return f;
}
int Compare(Fraction a, Fraction b) {
    double decimal_a = (double) a.numerator / a.denominator;
    double decimal_b = (double) b.numerator / b.denominator;
    return decimal_a > decimal_b;
}
