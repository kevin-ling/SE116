/*
 * This file contains definitions for Huffman class.
 *
 */
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <map>
#include <bitset>
#include "pqueue.h"
using namespace std;
typedef int ext_char;
const int PSEUDO_EOF = 256;
const int NOT_A_CHAR = 257;

class Huffman
{
    public:
        Huffman();
        Huffman(const string & in, const string & out);
        ~Huffman();
        
        void setInput(const string & input);
        void setOutput(const string & output);
        void initIO();
        void closeIO();

        void compress();
        void decompress();

        void clear();
        void freeTree();

    private:
        struct HuffmanNode
        {
            ext_char        value;
            int             freq;
            HuffmanNode*    zero;
            HuffmanNode*    one;

            HuffmanNode();
            HuffmanNode(ext_char val, int f);
        };

        string                          input;
        string                          output;
        PriorityQueue<HuffmanNode*>     pqueue;
        HuffmanNode*                    huff_root;
        map<ext_char, int>              frequencyMap;
        map<ext_char, string>           huffmanMap;
        map<string, ext_char>           decodeMap;

        /*
         *  Handles I/O part
         */
        ifstream                        fin;
        ofstream                        fout;
        bitset<8>                       curByte;
        int                             pos;

        void writeBit(int bit);
        void write(const string & code);
        bool readBit();

        void buildFrequencyMap();
        void buildHuffmanTree();
        void recEncMap(HuffmanNode* t, string prefix);
        void buildEncodingMap();
        
        void encode();
        void writeHeader();

        void decode();
        void readHeader();
        void recDecMap(HuffmanNode* t, string prefix);
        void buildDecodingMap();

        void freeTree(HuffmanNode* t);
    

        //test functions
        void printFrequencyMap();
        void printEncodeMap();
        void printDecodeMap();


};




#endif
