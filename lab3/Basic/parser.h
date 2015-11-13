/*
 * File: parser.h
 * --------------
 * This file acts as the interface to the parser module.
 */

#ifndef _parser_h
#define _parser_h

#include <string>
#include "exp.h"
#include "statement.h"
#include "command.h"

#include "../StanfordCPPLib/tokenscanner.h"

/*
 * Function: parseExp
 * Usage: Expression *exp = parseExp(scanner);
 * -------------------------------------------
 * Parses an expression by reading tokens from the scanner, which must
 * be provided by the client.  The scanner should be set to ignore
 * whitespace and to scan numbers.
 */

Expression *parseExp(TokenScanner & scanner);

/*
 * Function: readE
 * Usage: Expression *exp = readE(scanner, prec);
 * ----------------------------------------------
 * Returns the next expression from the scanner involving only operators
 * whose precedence is at least prec.  The prec argument is optional and
 * defaults to 0, which means that the function reads the entire expression.
 */

Expression *readE(TokenScanner & scanner, int prec = 0);

/*
 * Function: readT
 * Usage: Expression *exp = readT(scanner);
 * ----------------------------------------
 * Returns the next individual term, which is either a constant, an
 * identifier, or a parenthesized subexpression.
 */

Expression *readT(TokenScanner & scanner);

/*
 * Function: precedence
 * Usage: int prec = precedence(token);
 * ------------------------------------
 * Returns the precedence of the specified operator token.  If the token
 * is not an operator, precedence returns 0.
 */

int precedence(std::string token);

/*
* Fuction: validNAME
* Usage: bool valid = validNAME(token);
* --------------------------------------------
* Returns a pointer to a parsed Command
*/
bool validNAME(std::string token);
/*
 * Fuction: parseStmt
 * Usage: Statement* stmt = parseStmt(scanner);
 * --------------------------------------------
 * Returns a pointer to a parsed Statement
 */

Statement* parseStmt(TokenScanner & scanner);

/*
* Fuction: parseREM
* Usage: Statement* stmt = parseREM(scanner);
* --------------------------------------------
* Returns a pointer to a parsed REM Statement
*/

Statement* parseREM(TokenScanner & scanner);
/*
* Fuction: parseLET
* Usage: Statement* stmt = parseLET(scanner);
* --------------------------------------------
* Returns a pointer to a parsed LET Statement
*/

Statement* parseLET(TokenScanner & scanner);
/*
* Fuction: parsePRINT
* Usage: Statement* stmt = parsePRINT(scanner);
* --------------------------------------------
* Returns a pointer to a parsed PRINT Statement
*/

Statement* parsePRINT(TokenScanner & scanner);
/*
* Fuction: parseINPUT
* Usage: Statement* stmt = parsePRINT(scanner);
* --------------------------------------------
* Returns a pointer to a parsed PRINT Statement
*/

Statement* parseINPUT(TokenScanner & scanner);

Statement* parseEND(TokenScanner & scanner);

Statement* parseGOTO(TokenScanner & scanner);

Statement* parseIF(TokenScanner & scanner);

/*
* Fuction: parseCmd
* Usage: Command* cmd = parseCmd(token);
* --------------------------------------------
* Returns a pointer to a parsed Command
*/

Command* parseCmd(std::string token);




#endif
