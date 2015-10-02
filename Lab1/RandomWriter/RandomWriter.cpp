/*
 * File: RandomWriter.cpp
 * ----------------------
 *
 * Name: 凌康伟
 * Student ID: 5140219295
 * This file is the starter project for the random writer problem.
 *
 */

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>


using namespace std;
using Container = map<string, vector<char>>;
int selectSource();
int selectOrder();
string buildMap(const string& filename, Container& container, const int order);
void randomWriter(const string& filename, const int order);
string maxValue(const map<string, int> &wordMap);
int rnd(int max);
int main()
{
    srand(time(NULL));
    vector<string> book = {"Hamlet.txt", "Middlemarch.txt", "TomSawyer.txt"};
    string source = book[selectSource()];
    int order = selectOrder();
    randomWriter(source, order);
    return 0;
}
int rnd(int max)
{
    return rand()%max;
}
int selectSource()
{
    int choice = 1;
    do
    {
        cout << "Please select a source text to build the RandomWritter:\n"
        << "1. Hamlet\n"
        << "2. Middlemarch\n"
        << "3. TomSawyer\n";
        cin >> choice;
    } while (choice > 3 || choice < 1);
    return choice - 1;
}
int selectOrder()
{
    int order = 0;
    do
    {
        cout << "Please enter the Markov Order (1-10) : ";
        cin >> order;
    } while (order > 10 || order < 1);
    return order;
}
void randomWriter(const string& filename, const int order)
{
    Container container;
    string initialSeed;
    initialSeed = buildMap(filename, container, order);        // build the model
    string randomText = initialSeed,current = initialSeed;
    while (randomText.length() <= 2000)
    {
        vector<char>& ref = container[current];
        char ch = ref[rnd(ref.size())];          // randomly select one character that follows it
        current = current.substr(1, order -1) + ch;   //update current
        randomText += ch;                     //update text
    }
    cout << randomText << endl;
    
}
string buildMap(const string& filename, Container& container, const int order)
{
    char ch;
    map<string, int> frequency;
    ifstream source("../../../../"+filename);
    if (source.fail()) cout << "fail" << endl;
    string currentWord, previousWord;
    while (source.get(ch))
    {
        if (currentWord.length() == order)       // a new word show up
        {
            ++frequency[currentWord];            // update it's frequency
            previousWord = currentWord;
            container[previousWord].push_back(ch);      // record the character that follows it
            currentWord = currentWord.substr(1, order - 1);   //update the current word
        }
        currentWord += ch;
    }
    return maxValue(frequency);
}

string maxValue(const map<string, int> &wordMap)     //find the most frequent word
{
    string retVal;
    auto iter = wordMap.cbegin();
    int freq = 0;
    for (; iter != wordMap.cend(); ++iter)
    {
        if (iter->second > freq)
        {
            freq = iter->second;
            retVal = iter->first;
        }
    }
    return retVal;
}

