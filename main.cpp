#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

const float inf = (1.0 / 0.0); // infinity
vector<vector<float>> createTable(vector<string>& data);
void loadData(vector<vector<float>>& table, vector<string>& data);
int termCount(string str);
vector<float> strToFV(string str);
void outputTable(vector<vector<float>>& table);
void solveDDT(vector<vector<float>>& table); // Newton divided difference table solver

int main()
{
    /*
    float one_third(1, 3);
    float one_half(1, 2);
    float three_halves(1.5f);
    float pie(3.14);

    cout << "float: " << one_third.numerator() << "/" << one_third.denominator() << endl;
    cout << "Half: " << one_half << endl;
    cout << "Three-halfs: " << three_halves << endl;
    cout << "Pie: " << pie << endl;

    cout << one_third * one_half << endl; // 1/6
    cout << one_third / one_half << endl; // 2/3
    cout << one_third + one_half << endl; // 5/6
    cout << three_halves - one_half << endl; // 1
    */
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
    int r = 0, c = 0;
    int currCol = 2; // current column in table
    float xtop = 0.0, xdown = 0.0;

    for (int n = (table[0].size() - 2); n > 0; --n)
    {
        for (int i = 0; i < n; ++i)
        {
            r = i;
            c = currCol;

            // traverse table to retrieve xdown
            while (c > 1)
            {
                --c;
                if (r < (table.size() - 1)) ++r;
            }
            xdown = table[r][c-1];

            r = i;
            c = currCol;

            // traverse table to retrieve xtop
            while (c > 1)
            {
                --c;
                if (r > 0 && c > 1) --r;
            }
            xtop = table[r][c-1];

            table[i][currCol] = (table[i+1][currCol-1] - table[i][currCol-1]) / (xdown - xtop);
        }

        ++currCol;
    }
}
