#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "fraction.h"
using namespace std;

int termCount(string str);
vector<vector<fraction>> loadData(vector<string>& data);
vector<fraction> strToFV(string str); // string to fraction vector

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

    ifstream iFile("input.txt");
    if (iFile.fail()) return 1; // exit if file cannot be opened
    string input = "";
    vector<string> data;
    vector<vector<fraction>> table;

    while (getline(iFile, input))
        data.push_back(input);

    iFile.close();
    table = loadData(data);

    for (int x = 0; x < table.size(); ++x)
    {
        for (int y = 0; y < table[x].size(); ++y)
        {
            if (table[x][y].denominator() != 0)
                cout << table[x][y] << "\t";
            else
                cout << "   \t";
        }

        cout << endl;
    }

    return 0;
}

int termCount(string str)
{
    int counter = 0;

    for (int i = 0; i < str.length(); ++i)
        counter = (str[i] == ' ') ? (counter+1) : counter;

    return (counter+1);
}


vector<vector<fraction>> loadData(vector<string>& data) // loads data in str to std::vectors
{
    int rowCount = termCount(data[0]);
    vector<vector<fraction>> table;
    vector<fraction> row; // row of the table
    fraction nullfrac(0, 0);

    for (int r = 0; r < rowCount; ++r)
    {
        vector<fraction> row;
        for (int c = 0; c < (rowCount+1); ++c)
            row.push_back(nullfrac);

        table.push_back(row);
    }

    vector<fraction> x = strToFV(data[0]); // x-values
    vector<fraction> fx = strToFV(data[1]); // y-values (f(x) values)

    for (int r = 0; r < rowCount; ++r)
    {
        table[r][0] = x[r];
        table[r][1] = fx[r];
    }

    return table;
}

vector<fraction> strToFV(string str)
{
    int start = 0, end = 0;
    float input = 0.0;
    stringstream ss;
    vector<fraction> result;
    ss << str;

    while (!ss.eof())
    {
        ss >> input;
        fraction frac(input);
        result.push_back(frac);
    }

    return result;
}
