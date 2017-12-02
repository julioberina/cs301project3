#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include "fraction.h"
using namespace std;

int main()
{
    /*
    fraction one_third(1, 3);
    fraction one_half(1, 2);
    fraction three_halves(1.5f);
    fraction pie(3.14);

    cout << "Fraction: " << one_third.numerator() << "/" << one_third.denominator() << endl;
    cout << "Half: " << one_half << endl;
    cout << "Three-halfs: " << three_halves << endl;
    cout << "Pie: " << pie << endl;

    cout << one_third * one_half << endl; // 1/6
    cout << one_third / one_half << endl; // 2/3
    cout << one_third + one_half << endl; // 5/6
    cout << three_halves - one_half << endl; // 1
    */

    stringstream ss;
    ifstream iFile("input.txt");
    if (iFile.fail()) return 1; // exit if file cannot be opened
    string input = "";

    while (!iFile.eof())
    {
        getline(iFile, input);
        cout << input << endl;
        ss << input;
    }

    iFile.close();

    return 0;
}
