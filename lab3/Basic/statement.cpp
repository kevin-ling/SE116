/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/simpio.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}

/* Implementation of the REMStatement class */

REMStatement::REMStatement(std::string comt)
{
	this->remark = comt;
}

void REMStatement::execute(EvalState &state)
{
    return;
}

StatementType REMStatement::getType()
{
  return REM;
}

/* Implementation of the LETStatement class */

LETStatement::LETStatement(Expression* exp)
: expr(exp)
{}

LETStatement::~LETStatement()
{
    delete expr;
}
void LETStatement::execute(EvalState &state)
{
    expr->eval(state);
}
StatementType LETStatement::getType()
{
  return LET;
}

/* Implementation of the PRINTStatement class */

PRINTStatement::PRINTStatement(Expression* exp)
: expr(exp)
{}

PRINTStatement::~PRINTStatement()
{
    delete expr;
}
void PRINTStatement::execute(EvalState &state)
{
    int value = expr->eval(state);
    cout << value << endl;
}
StatementType PRINTStatement::getType()
{
  return PRINT;
}

/* Implementation of the INPUTStatement class */

INPUTStatement::INPUTStatement(std::string var)
: name(var)
{}

void INPUTStatement::execute(EvalState &state)
{
	std::string prompt = " ? ";
	std::string str;
  int value;
  while (true)
  {
    cout << prompt;
    getline(cin,str);
    istringstream stream(str);
    stream >> value >> ws;
    if (stream.fail() || !stream.eof()) {
       cout << "INVALID NUMBER" << endl;
    }
    else
      break;
  }
  state.setValue(name, value);
}
StatementType INPUTStatement::getType()
{
  return INPUT;
}

/* Implementation of the ENDStatement class */
void ENDStatement::execute(EvalState &state)
{

}

StatementType ENDStatement::getType()
{
  return END;
}
/* Implementation of the GOTOStatement class */
GOTOStatement::GOTOStatement(int num)
: lineNumber(num)
{}

void GOTOStatement::execute(EvalState & state)
{
   //empty
}
StatementType GOTOStatement::getType()
{
  return GOTO;
}
int GOTOStatement::getLineNumber()
{
  return lineNumber;
}
/* Implementation of the IFStatement class */
IFStatement::IFStatement(Expression* left, Expression* right,
                           std::string compare, int num)
: lhs(left), rhs(right), lineNumber(num), comp(compare), jump(false)
{}

void IFStatement::execute(EvalState & state)
{
  int left = lhs->eval(state);
  int right = rhs->eval(state);
  if (comp == ">") jump = left > right;
  if (comp == "<") jump = left < right;
  if (comp == "=") jump = left == right;
}

StatementType IFStatement::getType()
{
  return IF;
}

bool IFStatement::result()
{
  return jump;
}
int IFStatement::getLineNumber()
{
  return lineNumber;
}

void EmptyStatement::execute(EvalState &state)
{
  //empty
}
StatementType EmptyStatement::getType()
{
  return EMPTY;
}




