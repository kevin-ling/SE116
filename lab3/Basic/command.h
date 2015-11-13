/*
 * File: command.h
 * -----------------
 * This file defines the Command abstract type and 
 * the commands subclasses for Interpreter commands
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "evalstate.h"
#include "program.h"
class Command
{
public:

    /*
     * Constructor: Command
     * ----------------------
     * The base class constructor is empty.  Each subclass must provide
     * its own constructor.
     */
    
    Command();

    /*
     * Method: onCommand
     * Usage: cmd->onCommand(state, program);
     * ----------------------------
     * execute the command
     */
    
    virtual void onCommand(EvalState & state, Program & program) = 0;
    
};

class RUNcmd : public Command
{
public:
    /*
     * Method: onCommand
     * Usage: cmd->onCommand(state, program);
     * ----------------------------
     * execute the command
     */
    
    virtual void onCommand(EvalState & state, Program & program);
    
};

class LISTcmd : public Command
{
public:
    /*
     * Method: onCommand
     * Usage: cmd->onCommand(state, program);
     * ----------------------------
     * execute the command
     */
    
    virtual void onCommand(EvalState & state, Program & program);
    
};

class CLEARcmd : public Command
{
public:

    /*
     * Method: execute
     * Usage: cmd->onCommand(state, program);
     * ----------------------------
     * execute the command
     */
    
    virtual void onCommand(EvalState & state, Program & program);
    
};
class QUITcmd : public Command
{
public:
    /*
     * Method: execute
     * Usage: cmd->onCommand(state, program);
     * ----------------------------
     * execute the command
     */
    
    virtual void onCommand(EvalState & state, Program & program);
    
};
class HELPcmd : public Command
{
public:

    /*
     * Method: execute
     * Usage: cmd->onCommand(state, program);
     * ----------------------------
     * execute the command
     */
    
    virtual void onCommand(EvalState & state, Program & program);
    
};


 #endif