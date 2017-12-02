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
    void reduce();
    int gcd(int a, int b);
    int flen(float fnum); // length of float
public:
    fraction(int n = 0, int d = 1);
    fraction(float fnum);
    int numerator() const;
    int denominator() const;
};

ostream& operator<<(ostream& outs, const fraction& frac);

#endif
