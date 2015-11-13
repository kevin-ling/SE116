/*
 * File: parser.cpp
 * ----------------
 * Implements the parser.h interface.
 */

#include <iostream>
#include <string>

#include "exp.h"
#include "parser.h"

#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/strlib.h"
#include "../StanfordCPPLib/tokenscanner.h"
using namespace std;

/*
 * Implementation notes: parseExp
 * ------------------------------
 * This code just reads an expression and then checks for extra tokens.
 */

Expression *parseExp(TokenScanner & scanner) {
   Expression *exp = readE(scanner);
   if (scanner.hasMoreTokens()) {
      error("parseExp: Found extra token: " + scanner.nextToken());
   }
   return exp;
}

/*
 * Implementation notes: readE
 * Usage: exp = readE(scanner, prec);
 * ----------------------------------
 * This version of readE uses precedence to resolve the ambiguity in
 * the grammar.  At each recursive level, the parser reads operators and
 * subexpressions until it finds an operator whose precedence is greater
 * than the prevailing one.  When a higher-precedence operator is found,
 * readE calls itself recursively to read in that subexpression as a unit.
 */

Expression *readE(TokenScanner & scanner, int prec) {
   Expression *exp = readT(scanner);
   string token;
   while (true) {
      token = scanner.nextToken();
      int newPrec = precedence(token);
      if (newPrec <= prec) break;
      Expression *rhs = readE(scanner, newPrec);
      exp = new CompoundExp(token, exp, rhs);
   }
   scanner.saveToken(token);
   return exp;
}

/*
 * Implementation notes: readT
 * ---------------------------
 * This function scans a term, which is either an integer, an identifier,
 * or a parenthesized subexpression.
 */

Expression *readT(TokenScanner & scanner) {
   string token = scanner.nextToken();
   TokenType type = scanner.getTokenType(token);
   if (type == WORD) return new IdentifierExp(token);
   if (type == NUMBER) return new ConstantExp(stringToInteger(token));
   if (token != "(") error("Illegal term in expression");
   Expression *exp = readE(scanner);
   if (scanner.nextToken() != ")") {
      error("Unbalanced parentheses in expression");
   }
   return exp;
}

/*
 * Implementation notes: precedence
 * --------------------------------
 * This function checks the token against each of the defined operators
 * and returns the appropriate precedence value.
 */

int precedence(string token) {
   if (token == "=") return 1;
   if (token == "+" || token == "-") return 2;
   if (token == "*" || token == "/") return 3;
   return 0;
}

/*
 * Implementation notes: parseStmt
 * --------------------------------
 * This function checks the first token from the scanner to determine
 * the type of the statement and then call correspoding parse Fuction.
 */
Statement* parseStmt(TokenScanner & scanner)
{
   if (!scanner.hasMoreTokens())
      return new EmptyStatement();
   string token = scanner.nextToken();
   if (token == "REM") return parseREM(scanner);
   if (token == "LET") return parseLET(scanner);
   if (token == "PRINT") return parsePRINT(scanner);
   if (token == "INPUT") return parseINPUT(scanner);
   if (token == "END")   return parseEND(scanner);
   if (token == "GOTO") return parseGOTO(scanner);
   if (token == "IF") return parseIF(scanner);
   error("SYNTAX ERROR");
   // more ... TODO
}

/*
 * Implementation notes: parseREM
 * --------------------------------
 * This function constructs a REM statement
 */
Statement* parseREM(TokenScanner & scanner)
{
   string comment;
   while (scanner.hasMoreTokens())
      comment += scanner.nextToken();
   return new REMStatement(comment);
}

 /*
 * Fuction: parseLET
 * Usage: Statement* stmt = parseLET(scanner);
 * --------------------------------------------
 * Returns a pointer to a parsed LET Statement
 */

Statement* parseLET(TokenScanner & scanner)
{
   std::string name = scanner.nextToken();
   scanner.saveToken(name);
   if (!validNAME(name))
      error("SYNTAX ERROR");
   Expression* exp = parseExp(scanner);
   return new LETStatement(exp);
}
 /*
 * Fuction: parsePRINT
 * Usage: Statement* stmt = parsePRINT(scanner);
 * --------------------------------------------
 * Returns a pointer to a parsed PRINT Statement
 */

 Statement* parsePRINT(TokenScanner & scanner)
 {
   Expression* exp = parseExp(scanner);
   return new PRINTStatement(exp);
 }
 /*
 * Fuction: parseINPUT
 * Usage: Statement* stmt = parsePRINT(scanner);
 * --------------------------------------------
 * Returns a pointer to a parsed PRINT Statement
 */

 Statement* parseINPUT(TokenScanner & scanner)
 {
   if (!scanner.hasMoreTokens())
      error("SYNTAX ERROR");
   string name = scanner.nextToken();
   if (!validNAME(name))
      error("SYNTAX ERROR");
   return new INPUTStatement(name);
 }

 Statement* parseEND(TokenScanner & scanner)
 {
   return new ENDStatement();
 }

 Statement* parseGOTO(TokenScanner & scanner)
 {
   if (!scanner.hasMoreTokens())
      error("SYNTAX ERROR");
   std::string token = scanner.nextToken();
   TokenType type = scanner.getTokenType(token);
   if (type != NUMBER)
      error("SYNTAX ERROR");
   return new GOTOStatement(stringToInteger(token));
 }
 Statement* parseIF(TokenScanner & scanner)
 {
   if (!scanner.hasMoreTokens())
      error("SYNTAX ERROR");
   string token = scanner.nextToken();
   string left,right,comp;
   while (token != ">" && token != "<" && token != "=")  // left expr
   {
      left += token;
      if (!scanner.hasMoreTokens())
         error("SYNTAX ERROR");
      token = scanner.nextToken();
   }
   comp = token;                       // compare operator
   if (!scanner.hasMoreTokens())
      error("SYNTAX ERROR");
   token = scanner.nextToken();
   while (token != "THEN")             // right expr
   {
      right += token;      
      if (!scanner.hasMoreTokens())
         error("SYNTAX ERROR");
      token = scanner.nextToken();
   }
   if (!scanner.hasMoreTokens())
      error("SYNTAX ERROR");
   string lineNum = scanner.nextToken();
   if (scanner.getTokenType(lineNum) != NUMBER)
      error("SYNTAX ERROR");
   TokenScanner newScanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(left);
   Expression* lhs = parseExp(scanner);
   scanner.setInput(right);
   Expression* rhs = parseExp(scanner);
   return new IFStatement(lhs, rhs, comp, stringToInteger(lineNum));
 }


Command* parseCmd(std::string token)
{
   if (token == "RUN") return new RUNcmd();
   if (token == "LIST") return new LISTcmd();
   if (token == "CLEAR") return new CLEARcmd();
   if (token == "QUIT")  return new QUITcmd();
   if (token == "HELP")  return new HELPcmd();
   error("Command undefined!");
}


bool validNAME(std::string token)
{
   return !(token == "LET" || token == "REM" || token == "INPUT"
            || token == "PRINT" || token == "END" || token =="GOTO"
            || token == "IF" || token == "THEN" || token == "RUN"
            || token == "LIST" || token == "CLEAR" || token == "QUIT"
            || token == "HELP");
}
