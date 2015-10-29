#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	vector<int> ve = {1,2,3,4,5};
	vector<int> ves;
	
	auto iter = ve.begin();
	++iter;
	ves.insert(ves.end(),ve.begin(), iter);
	ves.insert(ves.end(),iter + 1, ve.end());
	for (auto c : ves)
		cout << c << endl;
}

				exp1.insert(exp1.end(),expression.begin(), i);
				exp1.insert(exp1.end(),i+1, j);
				exp1.insert(exp1.end(),j+1,expression.end());




				string calculate(Num_Expr & numExpr)
{
	if (numExpr.size() == 1)     // full expression acquired
	{
		if (numExpr[0].first == 24)     // found 24
			return num_expr[0].second;
		else
			return "";
	}


}