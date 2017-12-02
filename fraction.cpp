#include "fraction.h"

// private method implementations

int fraction::gcd(int a, int b)
{
    int temp = 0;

    // Make sure a and b are positive
    a = (a < 0) ? (a * -1) : a;
    b = (b < 0) ? (b * -1) : b;

    while (b != 0)
    {
        temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

int fraction::flen(float fnum)
{
    int length = 7;
    int intOfFnum = fnum * 1000000; // 10^7, floats go up to 7 digits precision

    while ((intOfFnum % 10) == 0)
    {
        intOfFnum /= 10;
        --length;
    }

    return length;
}

// public method implementations

fraction::fraction(int n, int d)
{
    num = n;
    den = d;
}

fraction::fraction(float fnum)
{
    float fpart = 0, ipart = 0;
    int whole = 0, tenden = 0, tennum = 0, fplen = 0;

    fpart = modf(fnum, &ipart);
    whole = (int)ipart; // whole number part of mixed fraction
    fplen = flen(fpart);
    tennum = fpart * pow(10, fplen);
    tenden = pow(10, fplen);
    num = tenden * whole + tennum;
    den = tenden;

    reduce();
}

fraction::fraction(double dnum) : fraction::fraction((float)dnum) {}

int fraction::numerator() const
{
    return num;
}

int fraction::denominator() const
{
    return den;
}

void fraction::reduce()
{
    int factor = gcd(num, den); // number that num and den have in common

    num /= factor;
    den /= factor;
}

ostream& operator<<(ostream& outs, const fraction& frac)
{
    if (frac.denominator() == 1)
        outs << frac.numerator();
    else
        outs << frac.numerator() << "/" << frac.denominator();
    return outs;
}

fraction operator+(const fraction& f1, const fraction& f2)
{
    int tempnum = (f1.numerator() * f2.denominator()) + (f2.numerator() * f1.denominator());
    fraction result(tempnum, f1.denominator() * f2.denominator());
    result.reduce();
    return result;
}

fraction operator-(const fraction& f1, const fraction& f2)
{
    int tempnum = (f1.numerator() * f2.denominator()) - (f2.numerator() * f1.denominator());
    fraction result(tempnum, f1.denominator() * f2.denominator());
    result.reduce();
    return result;
}

fraction operator*(const fraction& f1, const fraction& f2)
{
    fraction result(f1.numerator() * f2.numerator(), f1.denominator() * f2.denominator());
    result.reduce();
    return result;
}

fraction operator/(const fraction& f1, const fraction& f2)
{
    fraction result(f1.numerator() * f2.denominator(), f1.denominator() * f2.numerator());
    result.reduce();
    return result;
}
