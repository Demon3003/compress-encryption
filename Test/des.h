#pragma once
#include <fstream>
#include<string>
#include <vector>
using namespace std;

class DES
{
    ifstream input;
    ofstream output;
    vector<bool> block, key;
    vector<vector<bool> > keys;
    string buffer;
    int length;

    void fillOutBlock(vector<bool>&);

    void wideKey();

    void swapForKey(vector<bool> & cd,short k, short i1, short i2, short k2);

    void shiftingForKey(vector<bool>&ck, vector<bool>&dk, short round);

    void finalSwapForKey(vector<bool> &cd, vector<bool> ck, vector<bool>dk);

    void createKey();

    void readFile();

    void IP();

    void encodingFunction();

    vector<bool> Expansion_R(vector<bool> right);

    void K_xor_E(vector<bool> key, vector<bool> &exp);

    void trasformToDecimal(int &k, int &q, int i, bool b[8][6]);

    void trasformToBinary(int v, vector<bool>& F);

    vector<bool> substitution(vector<bool> exp);

    void PermF(vector<bool> &F);

    vector<bool> L_xor_F(vector<bool>left, vector<bool>F);

    void inverse_IP();

    void writeToFile(int toDelete);

public:

    void encoding(string fName,string newKey);
    void decoding(string fName,string newKey);
};
