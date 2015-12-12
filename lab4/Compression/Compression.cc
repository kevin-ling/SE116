#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <map>
#include "huffman.h"
using namespace std;
 

void naiveCopy(string inputFilename, string outputFilename) 
{
    ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
    ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
    char c;
    while (ifs.get(c)) ofs.put(c);
    ofs.close();
    ifs.close();
}

void usage(string prog) 
{
    cerr << "usage: " << endl
        << "    " << prog << "[-d] input_file output_file" << endl;
    exit(2);
}

int main(int argc, char* argv[])
{
    int i;
    string inputFilename, outputFilename;
    Huffman app;
    bool isDecompress = false;
    for (i = 1; i < argc; i++) 
    {
        if (argv[i] == string("-d")) isDecompress = true;
        else if (inputFilename == "") inputFilename = argv[i];
        else if (outputFilename == "") outputFilename = argv[i];
        else usage(argv[0]);
    }
    if (outputFilename == "") usage(argv[0]);
    
    app.setInput(inputFilename);
    app.setOutput(outputFilename);
    if (isDecompress) app.decompress();
    else app.compress();
    return 0;
}
