#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;
using rule = pair<string, string>;
vector<pair<string,string>> rules;
int minStep = 11;
vector<string> used;

void convert(string start, string dest, int step, int begin, int maxStep)
{
	if (step > maxStep)
	{
		return;
	}
    else if (start == dest)
    {
    	if (step < minStep)
    		minStep = step;
		return;
    }
	else
	{
		used[step] = start;   // record the word in current process to prevent duplicates
		
		// iterate every rules
		for (auto iter = rules.begin(); iter != rules.end(); ++iter)
		{

			// cut duplicates
			size_t pos = max(begin - int(iter->first.size()) + 1,0);
			
			int size = iter->first.size();	

			// try every possible transform
			while ((pos = start.find(iter->first, pos)) != string::npos)
			{
				string thisStr = start;			
				thisStr.replace(pos, size, iter->second);
				
				// if the word hasn't been used in an ealier step
				if (find(used.begin(), used.begin() + step + 1, thisStr) == (used.begin() + step+1))
				{		
					convert(thisStr, dest, step + 1, pos, maxStep);
				}

				++pos;				
			}
		}
	}
	return;
}
int main() 
{
	ifstream fin("convert.in");
	ofstream fout("convert.out");
	string start, dest;
	fin >> start >> dest;
	string A, B;
	while (fin >> A >> B)
	{
		rules.push_back(rule(A,B));
	}
	
	used.resize(12);

	// try at a certain number of steps, reduce recursive cost 
	for (int i = 0 ; i <= 10; ++i)
	{
		convert(start, dest, 0, 0, i);
		if (minStep < 11)
		{
			break;
		}
	}

	if (minStep < 11)
		fout << minStep << endl;
	else
		fout << "NO ANSWER" << endl;
	fin.close();
	fout.close();
}