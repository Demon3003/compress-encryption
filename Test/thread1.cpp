#include "thread1.h"
#include "huffman.h"
#include "des.h"
#include "rle.h"
#include "rc4.h"
#include <fstream>
#include <windows.h>
using namespace std;

MyThread::MyThread(char t,QString s,QString e) :algorithm(t), name(s),key(e)
{
}

void MyThread::run()
{
    switch (algorithm)
    {
        case 'H': {Huffman huf; huf.huffman_ar(name.toStdString()); break;}

        case 'h': {Huffman huf; huf.huffman_unarchiver(name.toStdString()); break;}

        case 'R': {RLE rl; rl.rle(name.toStdString()); break;}

        case 'r': {RLE rl; rl.rleUnarchiver(name.toStdString()); break;}

        case 'D': {DES des; des.encoding(name.toStdString(),key.toStdString()); break;}

        case 'd': {DES des; des.decoding(name.toStdString(),key.toStdString()); break;}

        case 'C': {RC4 rc;	rc.rc4_encoding(name.toStdString(),key.toStdString()); break;}

        case 'c': {RC4 rc; rc.rc4_decoding(name.toStdString(),key.toStdString());break;}
    }

    emit send(1);

}
