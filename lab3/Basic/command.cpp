/*
 * File: command.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Command class itself and its subclasses  
 */

#include "command.h"
#include "evalstate.h"
#include "program.h"

/* Implementation of the Command class */
Command::Command()
{}
/* Implementation of the RUNcmd class */

void RUNcmd::onCommand(EvalState &state, Program & program)
{
	int lineNumber = program.getFirstLineNumber();
	while (lineNumber != -1)
	{
		Statement* stmt = program.getParsedStatement(lineNumber);
		int next = program.getNextLineNumber(lineNumber);
		if (stmt->getType() == END)
			break;
		stmt->execute(state);
		switch(stmt->getType())
		{
			case GOTO : 
				lineNumber = ((GOTOStatement*)stmt)->getLineNumber();
				break;
			case IF : 
				lineNumber = (((IFStatement*)stmt)->result())? 
							((IFStatement*)stmt)->getLineNumber():next;
				break;
			default:
				lineNumber = next;	    
		}
	}
}
/* Implementation of the LISTcmd class */

void LISTcmd::onCommand(EvalState &state, Program & program)
{
	int lineNumber = program.getFirstLineNumber();
	while (lineNumber != -1)
	{
		std::string code = program.getSourceLine(lineNumber);
		if (code.size() > 0)
			cout << lineNumber << code << endl;
		lineNumber = program.getNextLineNumber(lineNumber);
	}	
}
/* Implementation of the CLEARcmd class */
void CLEARcmd::onCommand(EvalState &state, Program & program)
{
	state.clear();
	program.clear();
}
/* Implementation of the QUITcmd class */
void QUITcmd::onCommand(EvalState &state, Program & program)
{
	exit(0);
}
/* Implementation of the HELPcmd class */
void HELPcmd::onCommand(EvalState &state, Program & program)
{
	cout << "!DNAMMOC PLEH EHT DERETNE EV'UOY" << endl;
}