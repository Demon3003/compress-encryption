#pragma once
#include <fstream>
#include <string>
using namespace std;

class RLE
{
    ifstream input;
    ofstream output;

    void printTheSame(char symbol1, unsigned int symbolCount);

    void printNotTheSame(string &);

    void readTheSame(char &,char &, unsigned int &);

    void readNotTheSame(char &,char &, string &);

    public:
        void rle(string fName);
        void rleUnarchiver(string fName);

};
