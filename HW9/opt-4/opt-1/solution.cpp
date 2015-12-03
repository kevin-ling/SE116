/*
 *  OPT-1
 *
 *	Isomorphism on trees
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

using adj = vector<int>;
using Tree = unordered_map<int, adj>;  		// adjacent list
int k,n,a,b;
Tree trees[100];
int root[100];
vector<set<int>> answer(100, set<int>{});
unordered_map<string, int> found;

int h = 0;		 // the index for a kind of tree in answer

int myhash(string & s)
{
	if (found.count(s) == 0)
		found[s] = h++;
	return found[s];
}

string encode(Tree & tree, int v)    // encode the tree by 0 and 1s.
{
	if (tree.count(v) == 0)
		return "";
	vector<string> codes;
	string code;
	for (auto & w : tree[v])
	{
		codes.push_back(encode(tree, w));
	}
	sort(codes.begin(), codes.end());
	for (auto & s : codes)
	{
		code += '0' + s + '1';
	}
	return code;
}

int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	fin >> k >> n;
	for (int i = 0 ; i < k ; ++i)
	{
		for (int j = 0 ; j < n - 1; ++j)
		{
			fin >> a >> b;
			if (j == 0)
				root[i] = a;
			trees[i][a].push_back(b);
		}
	}

	for (int i = 0; i < k ; ++i)
	{
		string code = encode(trees[i], root[i]);
		answer[myhash(code)].insert(i+1);
	}

	for (int i = 0; i < h; ++i)
	{
		for (auto it = answer[i].begin(); it != answer[i].end(); ++it)
		{
			if (it != answer[i].begin())
				fout << "=";
			fout << *it;
		}
		fout << endl;
	}

	fin.close();
	fout.close();
}
