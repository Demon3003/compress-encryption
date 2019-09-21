#include "rle.h"
#include <string>
#include <fstream>
using namespace std;

const int maxNum = 127;


void RLE::rle(string fName)
{
    input.open(fName, ios::binary);
    output.open(fName+".arc", ios::binary);
    string notSame;
    char symbol1, symbol2;
    symbol1 = input.get();
    symbol2 = input.get();
    while (input.peek() != EOF)
    {
        unsigned int symbolCount = 0;

        if (symbol1 == symbol2)
        {    
            readTheSame(symbol1,symbol2, symbolCount);
            printTheSame(symbol1,symbolCount);
        }
        else
        {
            readNotTheSame(symbol1,symbol2,notSame);
            printNotTheSame(notSame);
            notSame.clear();
        }
        symbol1 = input.get();
        symbol2 = input.get();
    }
    input.close();
    output.close();
}


void RLE::readTheSame(char &symbol1,char &symbol2, unsigned int &symbolCount)
{
    symbolCount++;
    do
    {
        symbol1 = symbol2;
        symbol2 = input.get();
        symbolCount++;
    } while ((symbol1 == symbol2) && !input.eof());
    input.seekg(-1, input.cur);
}

void RLE::readNotTheSame(char &symbol1,char &symbol2, string &notSame)
{
    notSame.push_back(symbol1);
    do
    {
        symbol1 = symbol2;
        symbol2 = input.get();
        notSame.push_back(symbol1);
    } while ((symbol1 != symbol2) && !input.eof());

    int i = notSame.size();

    if (notSame[i - 1] == symbol2)
    {
        notSame.pop_back();
        input.seekg(-1, input.cur);

    }
    input.seekg(-1, input.cur);
}

void RLE::printTheSame(char symbol1, unsigned int symbolCount)
{
    char symbol2;
    if (symbolCount <= maxNum)
    {
        symbol2 = symbolCount;
        output << symbol2;
        output << symbol1;
    }
    else
    {
        int i;
        i = symbolCount / maxNum;
        while (i != 0)
        {
            symbol2 = maxNum;
            output << symbol2;
            output << symbol1;
            i--;
        }
        if (symbolCount % maxNum != 0)
        {
            symbol2 = symbolCount % maxNum;
            output << symbol2;
            output << symbol1;
        }
    }
};
void RLE::printNotTheSame( string &notSame)
{
    int i; char symbol2;
    if (notSame.size() <= maxNum)
    {
        symbol2 = notSame.size();
        symbol2 = -symbol2;
        output << symbol2;

        for (i = 0; i < notSame.size(); i++)
            output << notSame[i];

    }
    else
    {
        i = 0;
        while (i < notSame.size() / maxNum)
        {
            symbol2 = maxNum;
            symbol2 = -symbol2;
            output << symbol2;
            for (int j = i* maxNum; j <i*maxNum+maxNum; j++)
            {
                output << notSame[j];
            }

            i++;
        }
        if (notSame.size() % maxNum != 0)
        {
            symbol2 = notSame.size() % maxNum;
            symbol2 = -symbol2;
            output << symbol2;
            for (i = notSame.size() + symbol2; i < notSame.size(); i++)
                output << notSame[i];
        }
    }
};

void RLE::rleUnarchiver(string fName)
{
    input.open(fName, ios::binary);
    fName.erase(fName.size()-4,4);
    output.open(fName, ios::binary);
    char symbol,count;
    while (input.peek() != EOF)
    {
       count = input.get();
       if (count >= 0)
       {
         symbol = input.get();
         while (count > 0)
         {
            output << symbol;
            count= count-1;
         }
       }
       else
       {
         while (count < 0)
         {
            symbol = input.get();
            output << symbol;
            count= count+1;
         }
        }
      }

    input.close();
    output.close();
}
