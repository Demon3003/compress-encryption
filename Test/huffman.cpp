#include "huffman.h"
#include <QApplication>
#include <vector>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <fstream>
using namespace std;

const int space=2;

#define VER_PTR shared_ptr<vertex>

void Huffman::huffman_ar(string name)
{
    input.open(name, ios::binary);
    while (!input.eof())
    {
        char a ;
        a = input.get();
        element[a]++;
    }

    createFirstVertexs();

    createTree();

    VER_PTR topVertex = vertexs.front(); // корінь дерева

    getCode(topVertex);

    input.clear(); input.seekg(0); // зміщуємо вказівник на початок файлу

    output.open(name+".arc", ios::binary);

    writeToFile();
    input.close();
    output.close();

}

void Huffman::createFirstVertexs()
{
    for ( map<char, int>::iterator it=element.begin();  it != element.end(); it++ )   // Створюємо початкові вершини
    {
        VER_PTR p(new vertex);
        p->symbol = it->first;
        p->number = it->second;
        p->right = nullptr;
        p->left = nullptr;
        vertexs.push_back(p);
    }
}

void Huffman::getCode(VER_PTR topVertex)
{
    if (topVertex->left != NULL)        //   для проходу по лівій гілці від кореня дерева
    {
        code.push_back(0);
        getCode(topVertex->left);
    }

    if (topVertex->right != NULL)       //  для проходу по правій гілці від кореня дерева
    {
        code.push_back(1);
        getCode(topVertex->right);
    }

    if ((topVertex->right == NULL) && (topVertex->right == NULL))
    {

        symbolCode[topVertex->symbol] = code;
    }

    if(!code.empty())
    code.pop_back();

}

void Huffman::createTree()
{
    struct compare
    {
        bool operator()(const VER_PTR l, const VER_PTR r)
            const {
            return l->number < r->number;
        }
    };

    list<VER_PTR> reserve;
    reserve = vertexs;
    while (vertexs.size() != 1)        //Створення дерева             // забераємо 2 вершини додаємо 1 поки не залишиться 1 вершина
    {
        vertexs.sort(compare());
        VER_PTR leftVertex = vertexs.front();
        vertexs.pop_front();
        VER_PTR rightVertex = vertexs.front();
        vertexs.pop_front();
        VER_PTR newVertex(new vertex);
        newVertex->left = leftVertex;
        newVertex->right = rightVertex;
        newVertex->number = leftVertex->number + rightVertex->number;
        reserve.push_back(newVertex);
        vertexs.push_back(newVertex);
    }
    reserve.push_front(vertexs.front());
    vertexs = reserve;
}


void Huffman::writeDictionary()
{
    int j=7,k = 0;
    char bin = 0;
    for (map<char, int>::iterator it = element.begin(); it != element.end(); it++)
    {
        output << it->first;
        code = symbolCode[it->first];

        for (int i = 0; i < code.size(); i++)
        {
            bin = bin | code[i] << (j);
            j--;
            if (j == -1)
            {
                j = 7;
                output << bin;
                bin = 0;
            }
        }
        j = 7;
        if (code.size() % 8 != 0)
        {
            output << bin;
            bin = 0;
        }
        output << " ";
        output << code.size() << " ";
        k++;
    }

    output << " " << k;
}

void Huffman::writeToFile()
{
    int k = 0;
    char bin = 0;
    while (!input.eof())
    {
        char a;
        a = input.get();
        code = symbolCode[a];
        for (int i = 0; i<code.size(); i++)
        {
            bin = bin | code[i] << (7 - k);
            k++;
            if (k == 8)
            {
                k = 0;
                output << bin;
                bin = 0;
            }
        }

    }

    writeDictionary();
}

void Huffman::huffman_unarchiver(string fName)
{
    input.open(fName, ios::binary);
    fName.erase(fName.size()-4,4);
    output.open(fName, ios::binary);
    int p;

    raedTabel(p);

    VER_PTR top(new vertex);
    for (list<char>::iterator it = symbols.begin(); it != symbols.end(); it++)
    {
        code = symbolCode[*it];
        addVertexToTree(top,it);
    }

    input.clear();
    input.seekg(0, input.end);
    p = p + input.tellg()+space+1;

    deCode(top, p);
    input.close();
    output.close();

}

void Huffman::checkForSpace(int &i,char&c)
{
    while (c != ' ')
    {
        i--;
        input.seekg(i, input.end);
        c = input.get();
    }

};

void Huffman::raedTabel(int & position)
{
    char c;
    int i = -space, j;
    input.seekg(i, input.end);
    c = input.get();
    checkForSpace(i, c);
    position = i - space;
    input >> i;
    input.seekg(position, input.end);       //  пропуск пробіла

    c = input.get();
    checkForSpace(position, c);
    position++;
    input.seekg(position, input.end);
    input >> j;

    readAllSymbols(position,j,i);

}

void Huffman::addVertexToTree(VER_PTR top,list<char>::iterator it)
{
        int i=space;

        if (!code.empty())
        {
            i = code.front();
            code.erase(code.begin());
        }
        else
        {
            top->symbol = *it;
        }

        if ( i == 0)
        {
            if (top->left == nullptr)
            {
                VER_PTR p(new vertex);
                top->left = p;
            }

            addVertexToTree(top->left,it);
        }
        if (i == 1)
        {
            if (top->right == nullptr)
            {
                VER_PTR p(new vertex);
                top->right = p;
            }

            addVertexToTree(top->right,it);
        }
}

void Huffman::deCode(VER_PTR top, int & p)
{
    char c; int i;
    VER_PTR exp = top;
    c = 0;
    i = 7;
    input.seekg(0);
    c = input.get();

    while (p != 0)
    {

        if ((c & (1 << i)) != 0)
        {
            exp = exp->right;
        }
        else
        {
            exp = exp->left;
        }

        if ((exp->left == NULL) && (exp->right == NULL))
        {
            output << exp->symbol;
            exp = top;
        }

        i--;

        if (i < 0)
        {
            i = 7;
            c = input.get();
            p--;

        }
    }

}

void Huffman::readBits(vector<short>&cod,int &position,char &c,int j)
{
    position--;
    input.seekg(position, input.end);
    int count = j / 8;
    if (j % 8 != 0)
        count++;
    while (count > 0)
    {
        for (int k = 0; k < 8; k++)
        {
            if ((c & (1 << k)) == 0)
            {
                cod.emplace(cod.begin(), 0);
            }

            if ((c & (1 << k)) != 0)
            {
                cod.emplace(cod.begin(), 1);
            }
        }
        c = input.get();
        position--;
        input.seekg(position, input.end);
        count--;
    }
}

void Huffman::readAllSymbols(int &position,int &j,int&i)
{
    position = position - space;
    input.seekg(position, input.end);
    char c = input.get();
    vector<short> cod;
    while (i > 0)
    {
        readBits(cod,position,c,j);
        i--;
        symbols.push_front(c);
        cod.resize(j);
        symbolCode[c] = cod;
        cod.clear();
        position--;                                          // пропуск пробіла
        input.seekg(position, input.end);
        c = input.get();

        if (i != 0)
            checkForSpace(position, c);

        position++;
        input.seekg(position, input.end);
        input >> j;
        position = position - space;
        input.seekg(position, input.end);
        c = input.get();
    }
}
