/*
 * Implementation for Huffman class
 *
 *
 */

#include "huffman.h"

Huffman::Huffman(){}
Huffman::Huffman(const string & in, const string & out)
    : input(in), output(out)
{}

Huffman::~Huffman()
{   
    clear();
}

void Huffman::setInput(const string & input)
{
    this->input = input;
}

void Huffman::setOutput(const string & output)
{
    this->output = output;
}

void Huffman::initIO()
{
    // this two cause error on Ubuntu, don't know why :(
    //fin.exceptions(ifstream::failbit);
    //fout.exceptions(ofstream::failbit);

    // need open in binary mode
    fin.open(input, ios::binary);
    fout.open(output, ios::binary);

    curByte.reset();
    pos = 0;
}

void Huffman::closeIO()
{
    fin.close();
    fout.close();
}

void Huffman::compress()
{
    initIO();
    buildFrequencyMap();
    buildHuffmanTree();
    buildEncodingMap();
    pos = 0;

    writeHeader();
    encode();

    freeTree();
    closeIO();
}

void Huffman::decompress()
{
    initIO();
    readHeader();

    buildHuffmanTree();
    buildDecodingMap();
    pos = 8;

    decode();
    freeTree();
    closeIO();
}

void Huffman::clear()
{
    pqueue.clear();
    frequencyMap.clear();
    huffmanMap.clear();
}

void Huffman::freeTree()
{
    freeTree(huff_root);
}

Huffman::HuffmanNode::HuffmanNode()
    : zero(nullptr), one(nullptr)
{}


Huffman::HuffmanNode::HuffmanNode(ext_char val, int f)
    : value(val), freq(f), zero(nullptr), one(nullptr)
{}

void Huffman::writeBit(int bit)
{
    if (bit == 1)   
        curByte.set(pos);
    ++pos;
    if (pos == 8)
    {
        char ch = curByte.to_ulong();
        fout.put(ch);
        pos = 0;
        curByte.reset();
    }
}

void Huffman::write(const string & code)
{
    for (char c : code)
    { 
        if (c == '1')
            writeBit(1);
        else
            writeBit(0);
    }
}

bool Huffman::readBit()
{
    if (pos == 8)
    {
        curByte.reset();
        ext_char ch = fin.get();
        curByte = bitset<8>(ch);
        pos = 0;
    }
    return curByte[pos++];

}

void Huffman::buildFrequencyMap()
{
    frequencyMap[PSEUDO_EOF] = 1;
    ext_char ch;
    while ((ch = fin.get()) != -1)
    {
        if (frequencyMap.count(ch) == 0)
            frequencyMap[ch] = 1;
        else
            ++frequencyMap[ch];
    }
    fin.clear();
    fin.seekg(0, ios_base::beg);

    //test
    //printFrequencyMap();
}

void Huffman::buildHuffmanTree()
{
    int count = frequencyMap.size();
    for (auto & ch : frequencyMap)
    {
        HuffmanNode* node = new HuffmanNode(ch.first, ch.second);
        pqueue.push(node, node->freq);

    }
    
    while (--count)
    {
        HuffmanNode* a = pqueue.pop();
        HuffmanNode* b = pqueue.pop();
        HuffmanNode* z = new HuffmanNode(NOT_A_CHAR, a->freq + b->freq);
        z->zero = a;
        z->one = b;
        pqueue.push(z, z->freq);
    }
    huff_root = pqueue.pop();
}

void Huffman::recEncMap(HuffmanNode* t, string prefix)
{
    if (t->zero != nullptr)
        recEncMap(t->zero, prefix+'0');
    if (t->one != nullptr)
        recEncMap(t->one, prefix+'1');
    if (t->value != NOT_A_CHAR)
        huffmanMap[t->value] = prefix;
}

void Huffman::buildEncodingMap()
{
    string prefix = "";
    recEncMap(huff_root, prefix);

    //test
    //printEncodeMap();
}

void Huffman::encode()
{
    ext_char ch;
    while (!fin.eof())
    {
        ch = fin.get();
        write(huffmanMap[ch]);
    }
    write(huffmanMap[PSEUDO_EOF]);

    //test

    write("00000000");  // make sure all bits have been written.
    fin.seekg(0, ios_base::beg);
}

void Huffman::writeHeader()
{
    fout.put('{');
    map<ext_char, int>::iterator begin = frequencyMap.begin();
    map<ext_char, int>::iterator end = frequencyMap.end();
    map<ext_char, int>::iterator cur = begin;
    
    while (cur != end)
    {
        cout << cur->first << '\t' << cur->second << endl;
        if (cur->first != PSEUDO_EOF)
        {
            if (cur != begin)
                fout.put(',');
            fout << cur->first;
            fout.put(' ');
            fout << cur->second;
        }
        ++cur;
    }
    fout.put('}');
}

void Huffman::decode()
{
    int bit;
    string code = "";
    while (!(fin.eof() && pos == 8))
    {
        //if (decodeMap[code] == PSEUDO_EOF)
        //    break;
        bit = readBit();
        code += to_string(bit);
        if (decodeMap.count(code) == 0)
            continue;
        else
        {
            if (decodeMap[code] == PSEUDO_EOF)
                break;
            fout.put(decodeMap[code]);
            code = "";
        }
    }
}

void Huffman::readHeader()
{
    frequencyMap.clear();
    ext_char ch;
    char p;
    int freq;
    p = fin.get();
    if (p != '{')
        throw invalid_argument("Header not found");
    while(p != '}')
    {
        fin >> ch;
        fin.get(p);
        if (p != ' ')
            throw invalid_argument("invalid Header");
        fin >> freq;
        frequencyMap[ch] = freq;

        fin.get(p);
        if (p == '}')
            break;
    }
    frequencyMap[PSEUDO_EOF] = 1;

    //test
}

void Huffman::recDecMap(HuffmanNode* t, string prefix)
{
    if (t->zero != nullptr)
        recDecMap(t->zero, prefix+'0');
    if (t->one != nullptr)
        recDecMap(t->one, prefix+'1');
    if (t->value != NOT_A_CHAR)
        decodeMap[prefix] = t->value; 
}

void Huffman::buildDecodingMap()
{
    string prefix = "";
    recDecMap(huff_root, prefix);
    
    //test
    //printDecodeMap();
}

void Huffman::freeTree(HuffmanNode* t)
{
    if (t == nullptr)
        return;
    freeTree(t->zero);
    freeTree(t->one);
    delete t;
}

void Huffman::printFrequencyMap()
{
    cout << "int\t" << "char\t" << "freq" << endl; 
    for (auto & c : frequencyMap)
        cout << c.first << '\t' << (char)c.first << '\t' << c.second << endl;
}

void Huffman::printEncodeMap()
{
    for (auto & c : huffmanMap)
        cout << c.first << '\t' << (char)c.first << '\t' << c.second << endl;
}

void Huffman::printDecodeMap()
{
    for (auto & c : decodeMap)
        cout << c.first << '\t' << (char)c.second << '\t' << c.second << endl;
}

