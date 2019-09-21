#include "rc4.h"
#include <fstream>
#include <string>
using namespace std;

const short blockSize = 256;


void RC4::rc4_encoding(string fName,string newKey)
{

  RC4_main(fName,fName+".enc", newKey);

}

void RC4::rc4_decoding(string fName,string newKey)
{
    string s=fName;
    s.erase(s.size()-4,4);
    RC4_main(fName,s, newKey) ;

}
void RC4::init_block(unsigned char  S[],string key)
{
   int keyLength = key.size();

   for (int i = 0; i < blockSize; i++)
   {
       S[i]=i;
   }

   int j = 0;
   for (int i = 0; i < blockSize; i++)
   {
       j = (j + S[i] + key[i % keyLength]) % blockSize;
       char c = S[i];
       S[i] = S[j]; S[j] = c;
   }
}

char RC4::keyStream(int&x,int &y, unsigned char S[])
{
    x = (x + 1) % blockSize;
    y = (y + S[x]) % blockSize;

    char c = S[x];
    S[x] = S[y]; S[y] = c;

    return S[(S[x] + S[y]) % blockSize];
}

void RC4::Encode(int&x, int &y, unsigned char S[])
{
    char symbol;

    while(input.peek()!=EOF)
    {
        symbol = input.get();
        symbol = symbol^ keyStream(x,y,S);
        output << symbol;
    }
}

void RC4::RC4_main(string fName,string fNameOutput,string newKey)
{
        unsigned char block_s[blockSize];
        input.open(fName,ios::binary);
        output.open(fNameOutput,ios::binary);
        int x=0, y = 0;
        init_block( block_s,newKey);
        Encode(x, y,block_s);
        input.close();
        output.close();

};
