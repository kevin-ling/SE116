/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
using namespace std;

Program::Program() {

}

Program::~Program() {
   clear();
}

void Program::clear() {
   sourceCode.clear();
   parsedStatement.clear();
}

void Program::addSourceLine(int lineNumber, string line) {
   sourceCode[lineNumber] = line;
}

void Program::removeSourceLine(int lineNumber) {
   sourceCode.erase(lineNumber);
}

string Program::getSourceLine(int lineNumber) {
	if (sourceCode.count(lineNumber) == 0)
		error("LINE NUMBER ERROR");
   return sourceCode.at(lineNumber);
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
	if (parsedStatement.count(lineNumber) != 0)
	{
		delete parsedStatement[lineNumber];
		parsedStatement.erase(lineNumber);
	}
	parsedStatement.insert(std::pair<int, Statement*>(lineNumber, stmt));
}

Statement* Program::getParsedStatement(int lineNumber) {
	if (parsedStatement.count(lineNumber) == 0)
		error("LINE NUMBER ERROR");
   return parsedStatement.at(lineNumber);
}
int Program::getFirstLineNumber() {
	if (!sourceCode.empty())
    	return sourceCode.begin()->first;
    return -1;
}

int Program::getNextLineNumber(int lineNumber) {
	map<int, std::string>::iterator next = sourceCode.upper_bound(lineNumber);
	if (next != sourceCode.end())
		return next->first;
	return -1;
    
}
