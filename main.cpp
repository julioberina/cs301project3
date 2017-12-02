#include <iostream>
#include "fraction.h"
using namespace std;

int main()
{
    fraction one_third(1, 3);
    fraction one_half(1, 2);
    fraction three_halves(1.5f);

    cout << "Fraction: " << one_third.numerator() << "/" << one_third.denominator() << endl;
    cout << "Half: " << one_half << endl;
    cout << "Three-halfs: " << three_halves << endl;

    return 0;
}
