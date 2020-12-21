typedef struct {
	long long numerator; 
	long long denominator; 
} Fraction;


Fraction CreateFrac(long long, long long);
void Reduction(Fraction*);
Fraction Add(Fraction, Fraction);
Fraction Sub(Fraction, Fraction);
Fraction Mul(Fraction, Fraction);
Fraction Div(Fraction, Fraction);
int Compare(Fraction, Fraction);
