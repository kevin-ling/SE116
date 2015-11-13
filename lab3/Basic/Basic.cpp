/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include <cctype>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);
bool isCommand(std::string word);
bool isNumericStricted(std::string word);

/* Main program */

int main() {
   EvalState state;
   Program program;
   //cout << "The World's Best Basic Interpreter by kevin5396" << endl;
   while (true) {
      try {
         processLine(getLine(), program, state);
      } catch (ErrorException & ex) {
         cout << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & state) {
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);
   std::string token = scanner.nextToken();
   TokenType type = scanner.getTokenType(token);
   if (type == WORD)
   {
      scanner.saveToken(token);
      if (isCommand(token))
      {
         Command* cmd = parseCmd(token);
         cmd->onCommand(state, program);
         delete cmd;
      } 
      else if (!isNumericStricted(token))
      {
         Statement* stmt = parseStmt(scanner);
         stmt->execute(state);
         delete stmt;
      }
      else
         error("SYNTAX ERROR");
   }
   else if (type == NUMBER)
   {
      std::string next = scanner.nextToken();
      scanner.saveToken(next);
      if (isCommand(token))
         error("SYNTAX ERROR");
      int lineNumber = stringToInteger(token);
      Statement* stmt = parseStmt(scanner);
      program.addSourceLine(lineNumber, line.substr(token.length(),
                            line.length()-token.length()));
      program.setParsedStatement(lineNumber, stmt);
   }
}

bool isCommand(std::string word)
{
   return word == "RUN" || word == "LIST" || word == "CLEAR" 
         || word == "QUIT" || word == "HELP";
}
bool isNumericStricted(std::string word)
{
   return word == "IF" || word == "GOTO" || word == "END" || word == "REM";
}
