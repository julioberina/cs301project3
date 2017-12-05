#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

const float inf = (1.0 / 0.0); // infinity
vector<vector<float>> createTable(vector<string>& data);
void loadData(vector<vector<float>>& table, vector<string>& data);
int termCount(string str);
vector<float> strToFV(string str);
void outputTable(vector<vector<float>>& table);
void solveDDT(vector<vector<float>>& table); // Newton divided difference table solver
void outputPolynomial(vector<vector<float>>& table);
void outputLagrangePolynomial(vector<vector<float>>& table);
vector<float> multiplyPolynomial(vector<float> a, vector<float> b);

int main()
{
    string file = "";
    cout << "Enter file to input:  ";
    getline(cin, file);
    cout << endl;

    ifstream iFile(file);
    if (iFile.fail()) return 1; // exit if file cannot be opened
    string input = "";
    vector<string> data;
    vector<vector<float>> table;

    while (getline(iFile, input))
        data.push_back(input);

    iFile.close();
    table = createTable(data);
    loadData(table, data);
    solveDDT(table);
    outputTable(table);
    cout << endl;
    outputPolynomial(table);
    cout << endl;
    outputLagrangePolynomial(table);

    return 0;
}

vector<vector<float>> createTable(vector<string>& data)
{
    vector<vector<float>> result;
    int size = termCount(data[0]);

    for (int r = 0; r < size; ++r)
    {
        vector<float> row;
        for (int c = 0; c < (size+1); ++c)
            row.push_back(inf);

        result.push_back(row);
    }

    return result;
}

void loadData(vector<vector<float>>& table, vector<string>& data)
{
    vector<float> x = strToFV(data[0]);
    vector<float> fx = strToFV(data[1]);

    for (int r = 0; r < x.size(); ++r)
    {
        table[r][0] = x[r];
        table[r][1] = fx[r];
    }
}

int termCount(string str)
{
    int counter = 0;

    for (int i = 0; i < str.size(); ++i)
        counter = (str[i] == ' ') ? counter+1 : counter;

    return (counter + 1);
}

vector<float> strToFV(string str)
{
    float input = 0.0;
    vector<float> fv;
    stringstream ss;
    ss << str;

    while (!ss.eof())
    {
        ss >> input;
        fv.push_back(input);
    }

    return fv;
}

void outputTable(vector<vector<float>>& table)
{
    // display table labels
    for (int label = 0; label < table[0].size(); ++label)
    {
        if (label == 0)
            cout << "x\t";
        else
        {
            cout << "f[";
            for (int count = 1; count < label; ++count)
                cout << ",";
            cout << "]\t";
        }
    }

    cout << endl;
    // display table data
    for (int r = 0; r < table.size(); ++r)
    {
        for (int c = 0; c < table[r].size(); ++c)
        {
            if (table[r][c] != inf)
                cout << table[r][c] << "\t";
        }

        cout << endl;
    }
}

void solveDDT(vector<vector<float>>& table)
{
    int gap = 1, currentCol = 2;
    float xt = 0.0, xb = 0.0; // xb = bottom x, xt = top x

    for (int n = (table[0].size() - 2); n > 0; --n) // vertical traversals affected by this loop
    {
        for (int i = 0; i < n; ++i)
        {
            xb = table[i+gap][0];
            xt = table[i][0];
            table[i][currentCol] = (table[i+1][currentCol-1] - table[i][currentCol-1]) / (xb-xt);
        }

        ++gap;
        ++currentCol;
    }
}

void outputPolynomial(vector<vector<float>>& table)
{
    int xsub = 0;

    cout << "Interpolating polynomial is:  " << endl;

    for (int c = 1; c < table[0].size(); ++c)
    {
        cout << table[0][c];
        for (int x = 0; x < xsub; ++x)
        {
            if (table[x][0] > 0)
                cout << "(x-" << table[x][0] << ")";
            else if (table[x][0] < 0)
                cout << "(x+" << (table[x][0] * -1) << ")";
            else
                cout << "(x)";
        }

        ++xsub;
        if (c != (table[0].size() - 1))
            cout << " + ";
    }

    cout << endl;
}

void outputLagrangePolynomial(vector<vector<float>>& table)
{
    vector<float> x;
    vector<float> y;
    vector<float> lagrange;
    float coeff = 0.0;
    float denominator = 1;
    int lindex = 0;

    for (int i = 0; i < table.size(); ++i)
    {
        x.push_back(table[i][0]);
        y.push_back(table[i][1]);
        lagrange.push_back(0);
    }

    for (int i = 0; i < y.size(); ++i)
    {
        vector<float> xprod;
        coeff = y[i];
        for (int j = 0; j < x.size(); ++j)
        {
            if (j == i) continue;
            vector<float> poly;
            denominator *= (x[i] - x[j]);
            poly.push_back((x[j] * -1));
            poly.push_back(1);

            if (xprod.empty())
                xprod = poly;
            else
                xprod = multiplyPolynomial(xprod, poly);
        }

        coeff = coeff / denominator;
        denominator = 1;
        // append each polynomial coefficient to Lagrange polynomial result
        for (int j = 0; j < xprod.size(); ++j)
        {
            xprod[j] *= coeff;
            lagrange[j] += xprod[j];
        }
    }

    lindex = lagrange.size() - 1; // last index of Lagrange polynomial;
    cout << "Simplified polynomial is:" << endl;
    for (int n = lindex; n >= 0; --n)
    {
        if (lagrange[n] < 0 && n < lindex)
            cout << (lagrange[n] * -1);
        else
            cout << lagrange[n];

        if (n > 0)
        {
            cout << "x" << ((n > 1) ? ("^" + to_string(n)) : "");
            if (lagrange[n-1] < 0)
                cout << " - ";
            else
                cout << " + ";
        }
    }

    cout << endl;
}

vector<float> multiplyPolynomial(vector<float> a, vector<float> b)
{
    int m = a.size();
    int n = b.size();
    vector<float> prod;

    for (int i = 0; i < (m+n-1); ++i)
        prod.push_back(0);

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
            prod[i+j] += (a[i]*b[j]);
    }

    return prod;
}
