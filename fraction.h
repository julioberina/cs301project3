#ifndef FRACTION_H
#define FRACTION_H
#include <ostream>
#include <cmath>
using namespace std;

class fraction
{
private:
    int num;
    int den;
    int gcd(int a, int b);
    int flen(float fnum); // length of float
public:
    fraction(int n = 0, int d = 1);
    fraction(float fnum);
    fraction(double dnum);
    int numerator() const;
    int denominator() const;
    void reduce();
};

ostream& operator<<(ostream& outs, const fraction& frac);
fraction operator+(const fraction& f1, const fraction& f2);
fraction operator-(const fraction& f1, const fraction& f2);
fraction operator*(const fraction& f1, const fraction& f2);
fraction operator/(const fraction& f1, const fraction& f2);

#endif
