#pragma once
#include <string>
#include <fstream>
using namespace std;

class RC4
{
    ifstream input;
    ofstream output;

    void init_block(unsigned char s[],string);

    char keyStream(int&,int &, unsigned char S[]);

    void Encode(int&,int &, unsigned char s[]);

    void RC4_main(string fName,string fNameOutput,string newKey);

    public:

        void rc4_encoding(string fName,string newKey);
        void rc4_decoding(string fName,string newKey);
};
