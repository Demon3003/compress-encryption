#pragma once
#include <vector>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <fstream>
using namespace std;

#define VER_PTR shared_ptr<vertex>

struct vertex
{
    int number;
    char symbol;
    shared_ptr<vertex> right, left;
};



class Huffman
{
    ifstream input;
    ofstream output;
    vector<short> code;
    map<char, vector<short>> symbolCode;
    list<VER_PTR> vertexs;
    map <char, int> element;
    list<char> symbols;

    void createFirstVertexs();

    void getCode(VER_PTR topVertex);

    void createTree();

    void writeDictionary();

    void writeToFile();

    void checkForSpace(int &,char&);

    void readBits(vector<short>&,int &,char &,int);

    void readAllSymbols(int &,int &j,int&);

    void raedTabel(int &);

    void addVertexToTree(VER_PTR,list<char>::iterator it);

    void deCode(VER_PTR, int &);

    public:
        void huffman_ar(string name);
        void huffman_unarchiver(string fName);

};
