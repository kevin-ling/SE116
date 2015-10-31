#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <ctime>
using namespace std;
using Num_Expr = vector<pair<double, string>>;
using ITER = vector<pair<double, string>>::iterator;
// store 4 numbers
vector<double> nums;

// store expression string
vector<string> expr;

// 4 operators
char op[4] = {'+','-','*','/'};
// correspond function
auto add = [](double a, double b)->double{return a+b;};
auto sub = [](double a, double b)->double{return a-b;};
auto x = [](double a, double b)->double{return a*b;};
auto x_ = [](double a, double b)->double{return a/b;};
std::function<double(double, double)> func[4] = {add, sub, x, x_};

double getNum(string & str)
{
	switch (str[0])
	{
		case 'J' : return 11; break;
		case 'Q' : return 12; break;
		case 'K' : return 13; break;
		default  : if (str == "10") return 10;
				   return double(str[0]-'0'); break;
	}
}
void fill_with_no_ij(Num_Expr& istr, Num_Expr& in,ITER &i,ITER &j)
{
	istr.insert(istr.end(),in.begin(), i);
	istr.insert(istr.end(),i+1, j);
	istr.insert(istr.end(),j+1, in.end());
}
void construct(Num_Expr& istr, ITER &i, ITER &j, int k)
{
	double res = func[k](i->first, j->first);
	string s = i->second +" "+ op[k] +" "+j->second;
	if (!istr.empty())		// we don't need parenthesis at border
		s = "( " + s +" )";     
	istr.push_back(make_pair(res, s));
}
string calculate(Num_Expr & numExpr)
{
	if (numExpr.size() == 1)     // full expression acquired
	{
		if (numExpr[0].first == 24)     // found 24
		{
			return numExpr[0].second;
		}
		else
			return "";
	}

	// iterate through every possible combination until find a 24 combination.
	for (auto i = numExpr.begin(); i != numExpr.end(); ++i)
		for (auto j = i + 1; j != numExpr.end(); ++j)
			for (int k = 0 ; k < 4; ++k)
			{
				Num_Expr num_expr1;

				// copy elements to new Num_Expr that currently not dealing with
				fill_with_no_ij(num_expr1, numExpr, i, j);		
				
				Num_Expr num_expr2(num_expr1);
				string res;
				// process with i,j and j,i 
				// in case of 0-divider
				if (j->first != 0)	
				{
					//if(!(k == 3 && (i->first % j->first != 0)))
					
						// construct new value and new expression with i and j
					construct(num_expr1,i,j,k);
					res = calculate(num_expr1);
					if (!res.empty())
						return res;
					
				}
				if (i->first != 0)
				{
					//if(!(k == 3 && (j->first % i->first != 0)))
					
					construct(num_expr2,j,i,k);					
					res = calculate(num_expr2);
					if (!res.empty())
						return res;
					
				}
			}
	return "";
}

int main()
{
	ifstream fin("calculator.in");
	ofstream fout("calculator.out");
	string str;
	Num_Expr num_expr;
	while (fin >> str)
	{
		num_expr.push_back(make_pair(getNum(str), str));
	}
	string res = calculate(num_expr);
	if (!res.empty())
		fout << res << endl;
	else
		fout << "NO ANSWER" << endl;
}
