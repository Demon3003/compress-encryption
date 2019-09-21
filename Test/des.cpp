#include "des.h"
#include <fstream>
#include<string>
#include <vector>
using namespace std;

void DES::encoding(string fName,string newKey)
{
    input.open(fName, ios::binary);
    output.open(fName+".enc", ios::binary);
    buffer=newKey;
    wideKey();
    createKey();
    buffer.clear();
    input.seekg(0, input.end);
    length = input.tellg();
    input.seekg(0, input.beg);
    int numberOfBlocks = length / 8 ;
    if (length % 8 != 0)
    {
        numberOfBlocks++;
        output << 8 - length % 8 << " ";
    }
    else {
        output << 0 << " ";
    }


    for (int i = 0; i < numberOfBlocks; i++)
    {
        readFile();
        fillOutBlock(block);
        IP();
        encodingFunction();
        inverse_IP();
        writeToFile(0);

        buffer.clear();
        block.clear();
    }

    input.close();
    output.close();
}

void DES::decoding(string fName,string newKey)
{
    input.open(fName, ios::binary);
    fName.erase(fName.size() - 4, 4); output.open(fName, ios::binary);
    short helpSymbols;
    input >> helpSymbols; input.get();
    input.seekg(0, input.end);
    length = input.tellg();
    length = length - 2;
    input.seekg(2, input.beg);
    buffer=newKey;
    wideKey();
    createKey();
    buffer.clear();
    int numberOfBlocks = length / 8;
    int i = 0;
    vector<vector<bool> >res(keys.size());
    for (int j = keys.size() - 1; j >= 0; j--)
    {
        res[i] = keys[j];
        i++;
    }
    keys = res;

    for (int i = 0; i < numberOfBlocks; i++)
    {
        readFile();
        fillOutBlock(block);
        IP();
        encodingFunction();
        inverse_IP();
        if (i == numberOfBlocks - 1)
            writeToFile(helpSymbols);
        else
            writeToFile(0);

        buffer.clear();
        block.clear();
    }

    input.close();
    output.close();
}

void DES::encodingFunction()
{
    vector<bool> left, right;
    left = block; left.resize(32);
    right = block; right.erase(right.begin(), right.begin() + 32);

    for (int round = 1; round <= 16; round++)
    {
        vector<bool> F, exp;
        exp = Expansion_R(right);
        K_xor_E(keys[round - 1], exp);
        F = substitution(exp);
        PermF(F);
        exp = right;
        right = L_xor_F(left, F);
        left = exp;
    }
    block = right;
    for (int k = 0; k < left.size(); k++)  block.push_back(left[k]);

}

void DES::fillOutBlock(vector<bool>& myBlock)
{
    for (int j = 0; j< 8; j++)
    {
        for (int a = 7; a >= 0; a--)
        {
            if ((buffer[j] & (1 << a)) == 0)
            {
                myBlock.push_back(0);
            }
            else
            {
                myBlock.push_back(1);
            }
        }

    }

}

void DES::wideKey()
{
    short n=0,k=0,t=0;
    buffer.push_back('0');
    fillOutBlock(key);
    vector<bool> reserve;
    for (int i = 0; i < key.size(); i++)
    {
        reserve.push_back(key[i]);
        if (key[i] == 1)
            n++;
        if (t==6)
        {
            if (n % 2 == 0)
                reserve.push_back(1);
            else
                reserve.push_back(0);

            n = 0;
            t = 0;
            k++;
        }
        else
            t++;
    }
    key = reserve;
}

void DES::swapForKey(vector<bool> & cd,short k,short i1, short i2,short k2)
{
    int  i;
    for (i = i1; i < i2; i++)
    {
        cd[i] = key[k - 1];
        if (k - 8 > 0)
            k = k - 8;
        else
            k = k + k2;
    }
}
void DES::shiftingForKey(vector<bool>&ck, vector<bool>&dk,short round )
{
    const short sz1 = 16,sz3 = 28;
    short shift;
    if (round == 1 || round == 2 || round == 9 || round == sz1)
        shift = 1;
    else
        shift = 2;
    while (shift > 0)
    {
        int t,i;
        t = ck[0];
        for (i = 0; i < sz3 - 1; i++)
            ck[i] = ck[i + 1];
        ck[sz3 - 1] = t;
        t = dk[0];
        for (i = 0; i < sz3 - 1; i++)
            dk[i] = dk[i + 1];
        dk[sz3 - 1] = t;
        shift--;
    }
}
void DES::finalSwapForKey(vector<bool> &cd,vector<bool> ck, vector<bool>dk)
{
    const short sz1 = 28, sz2 = 56;
    vector<bool> per(sz2);
    int i, k;
    for (i = 0; i < sz1; i++) per[i] = ck[i];
    for (k = 0, i = sz1; i < sz2; i++) per[i] = dk[k++];

    cd[0] = per[13]; cd[1] = per[16]; cd[2] = per[10]; cd[3] = per[23]; cd[4] = per[0]; cd[5] = per[4]; cd[6] = per[2]; cd[7] = per[27];
    cd[8] = per[14]; cd[9] = per[5]; cd[10] = per[20]; cd[11] = per[9]; cd[12] = per[22]; cd[13] = per[18]; cd[14] = per[11]; cd[15] = per[3];
    cd[16] = per[25]; cd[17] = per[7]; cd[18] = per[15]; cd[19] = per[6]; cd[20] = per[26]; cd[21] = per[19]; cd[22] = per[12]; cd[23] = per[1];
    cd[24] = per[40]; cd[25] = per[51]; cd[26] = per[30]; cd[27] = per[36]; cd[28] = per[46]; cd[29] = per[54]; cd[30] = per[29]; cd[31] = per[39];
    cd[32] = per[50]; cd[33] = per[46]; cd[34] = per[32]; cd[35] = per[47]; cd[36] = per[43]; cd[37] = per[48]; cd[38] = per[38]; cd[39] = per[55];
    cd[40] = per[33]; cd[41] = per[52]; cd[42] = per[45]; cd[43] = per[41]; cd[44] = per[49]; cd[45] = per[35]; cd[46] = per[28]; cd[47] = per[31];
}
void DES::createKey()
{
    const short sz1 = 16, sz2 = 56, sz3 = 28, sz4 = 48;
    keys.resize(sz1);
    vector<bool> cd(sz2), ck(sz3), dk(sz3);
    short i, round;
    swapForKey(cd, 57, 0, 28, 57);
    swapForKey(cd,63, 28, 52, 55);
    swapForKey(cd,28, 52, 56, 0);
    ck = cd; ck.resize(sz3);
    dk = cd; dk.erase(dk.begin(), dk.begin() + sz3);

    for (round = 1; round <= sz1; round++)
    {
        shiftingForKey(ck, dk, round);
        cd.resize(sz4);
        finalSwapForKey(cd,ck,dk);
        for (i = 0; i < sz4; i++)
            keys[round - 1].push_back(cd[i]);
    }

}

void DES::readFile()
{
    if (length > 0)
    {
        if (length - 8 > 0)
        {
            for (int i = 0; i < 8; i++)
                buffer.push_back(input.get());
            length = length - 8;
        }
        else
        {
            for (int i = 0; i < length; i++)
                buffer.push_back(input.get());
            for (int i = 0; i < 8 - length; i++)
                buffer.push_back(' ');
            length = 0;
        }
    }
}


void DES::IP()
{
    const short sz1 = 58,sz2=32;
    int k = sz1, i;
    vector<bool> ip;
    ip.resize(block.size());
    for (i = 0; i < sz2; i++)
    {
        ip[i] = block[k - 1];
        if (k - 8>0)  k = k - 8;
        else       k = k + sz1;
    }
    k = sz1-1;
    for (i = sz2; i < sz2*2; i++)
    {
        ip[i] = block[k - 1];
        if (k - 8 > 0)   k = k - 8;
        else	    k = k + sz1;
    }
    block = ip;
}

vector<bool> DES::Expansion_R(vector<bool> right)
{
    vector<bool>  exp;
    int k;
    exp.push_back(right[31]);
    for (int i = 0  ; i < 8; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (((i | j) != 0) && (i!=7 || j!=5))
            {

                if ((j != 0) && (j != 5))
                {
                    k = 4 * i + j;
                    exp.push_back(right[k - 1]);
                }
                if (j == 0)
                {
                    k = 4 * i;
                    exp.push_back(right[k - 1]);
                }
                if (j == 5)
                {
                    k = 4 * i + j;
                    exp.push_back(right[k - 1]);
                }
            }
        }
    }
    exp.push_back(right[0]);
    return exp;
}

void DES::K_xor_E(vector<bool> myKey, vector<bool> &exp)
{
    vector<bool> reserve(exp.size());

    for (int i = 0; i < exp.size(); i++)
        reserve[i] = exp[i] ^ myKey[i];

    exp = reserve;
}

vector<bool> DES::substitution(vector<bool> exp)
{
    int s1[4][16] = {
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
    };

    int s2[4][16] = {
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
    };

    int s3[4][16] = {
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
    };

    int s4[4][16] = {
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
    };

    int s5[4][16] = {
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
    };

    int s6[4][16] = {
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
    };

    int s7[4][16] = {
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
    };

    int s8[4][16] = {
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
    };

    bool b[8][6]; int k = 0, i, j, q, v;
    vector<bool> F;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j<6; j++)
        {
            b[i][j] = exp[k++];
        }
    }

    for (i = 0; i < 8; i++)
    {
        trasformToDecimal(k,q, i, b);
        switch (i + 1)
        {
            case 1:	v = s1[k][q];	break;
            case 2:	v = s2[k][q];	break;
            case 3:	v = s3[k][q];	break;
            case 4:	v = s4[k][q];	break;
            case 5:	v = s5[k][q];	break;
            case 6:	v = s6[k][q];	break;
            case 7:	v = s7[k][q];	break;
            case 8:	v = s8[k][q];	break;
        }

        trasformToBinary(v, F);
    }
    return F;
}

void DES::trasformToDecimal(int &k, int &q,int i,bool b [8][6])
{
    int p = 1, j = 4; q = 0;
    k = (b[i][0] * 2) + (b[i][5]);      // переводимо до десяткової системи

    while (j > 0)
    {
        q = q + (b[i][j] * p);
        p = p * 2;
        j--;
    }

}

void DES::trasformToBinary(int v,vector<bool>& F)
{
    int d, i = 3; bool b[4];
    while (v > 0)
    {
        d = v % 2;
        b[i--] = d;
        v = v / 2;
    }
    while (i >= 0)
    {
        b[i--] = 0;
    }

    for (i = 0; i < 4; i++)
        F.push_back(b[i]);
}

void DES::PermF(vector<bool> &F)
{
    vector<bool> p(F.size());
    p[0] = F[15]; p[1] = F[6]; p[2] = F[19]; p[3] = F[20]; p[4] = F[28]; p[5] = F[11]; p[6] = F[27]; p[7] = F[16];
    p[8] = F[0]; p[9] = F[14]; p[10] = F[22]; p[11] = F[25]; p[12] = F[4]; p[13] = F[17]; p[14] = F[30]; p[15] = F[9];
    p[16] = F[1]; p[17] = F[7]; p[18] = F[23]; p[19] = F[13]; p[20] = F[31]; p[21] = F[26]; p[22] = F[2]; p[23] = F[8];
    p[24] = F[18]; p[25] = F[12]; p[26] = F[29]; p[27] = F[5]; p[28] = F[21]; p[29] = F[10]; p[30] = F[3]; p[31] = F[24];
    F = p;
}

vector<bool >DES::L_xor_F(vector<bool>left,vector<bool>F)
{
    vector<bool> reserve(left.size());
    for (int i = 0; i < left.size(); i++)
    {
        reserve[i] = left[i] ^ F[i];
    }
    return reserve;
}

void DES::inverse_IP()
{
    vector<bool> inv;
    int p = 40, q = 8, k1, k2;
    for (int i = 0; i < 8; i++)
    {
        k1 = p; k2 = q;
        for (int j = 0; j < 8; j++)
        {
            if (j % 2 == 0)
            {
                inv.push_back(block[k1 - 1]);
                k1 = k1 + 8;
            }
            else if (j % 2 != 0)
            {
                inv.push_back(block[k2 - 1]);
                k2 = k2 + 8;
            }
        }
        p = p - 1; q = q - 1;
    }
    block = inv;
}

void DES::writeToFile(int toDelete)
{
    char symbol=0;
    int count=7;
    for (int i = 0; i < block.size()- toDelete*8; i++)
    {
        symbol = symbol | block[i] << (count);
        count--;
        if (count == -1)
        {
            count = 7;
            output << symbol;
            symbol = 0;
        }

    }

}
