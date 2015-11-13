/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"
/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

enum StatementType{REM, LET, INPUT, PRINT, END, GOTO, IF, EMPTY};
class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual void execute(EvalState & state) = 0;

/*
 * Method: type
 * Usage: StatementType type = stmt->getType();
 * --------------------------------------------
 * Returns the type of the expression, which must be one of the constants
 * CONSTANT, IDENTIFIER, or COMPOUND.
 */

   virtual StatementType getType() = 0;

};

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

class REMStatement : public Statement
{
public:

/*
 * Constructor: REMStatement
 * Usage: REMStatement* stmt = new REMStatement(string)
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   REMStatement(std::string rem);


/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual void execute(EvalState & state);

   virtual StatementType getType();

private:
	std::string remark;

 };

class LETStatement : public Statement
{
public:
    
    /*
     * Constructor: LETStatement
     * Usage: LETStatement* stmt = new LETStatement(exp)
     * ----------------------
     * The base class constructor is empty.  Each subclass must provide
     * its own constructor.
     */
    
    LETStatement(Expression* exp);
    
    /*
     * Destructor: ~Statement
     * Usage: delete stmt;
     * -------------------
     * The destructor deallocates the storage for this expression.
     * It must be declared virtual to ensure that the correct subclass
     * destructor is called when deleting a statement.
     */
    
    virtual ~LETStatement();
    
    /*
     * Method: execute
     * Usage: stmt->execute(state);
     * ----------------------------
     * Execute a LET statement
     */
    
    virtual void execute(EvalState & state);

    virtual StatementType getType();
    
private:
    Expression* expr;
    
};

class PRINTStatement : public Statement
{
public:
    
    /*
     * Constructor: PRINTStatement
     * Usage: PRINTStatement* stmt = new PRINTStatement(exp)
     * ----------------------
     * The base class constructor is empty.  Each subclass must provide
     * its own constructor.
     */
    
    PRINTStatement(Expression* exp);
    
    /*
     * Destructor: ~Statement
     * Usage: delete stmt;
     * -------------------
     * The destructor deallocates the storage for this expression.
     * It must be declared virtual to ensure that the correct subclass
     * destructor is called when deleting a statement.
     */
    
    virtual ~PRINTStatement();
    
    /*
     * Method: execute
     * Usage: stmt->execute(state);
     * ----------------------------
     * Execute a LET statement
     */
    
    virtual void execute(EvalState & state);

    virtual StatementType getType();
    
private:
    Expression* expr;
    
};

class INPUTStatement : public Statement
{
public:
    
    /*
     * Constructor: INPUTStatement
     * Usage: INPUTStatement* stmt = new INPUTStatement(exp)
     * ----------------------
     * The base class constructor is empty.  Each subclass must provide
     * its own constructor.
     */
    
    INPUTStatement(std::string var);
    
    
    /*
     * Method: execute
     * Usage: stmt->execute(state);
     * ----------------------------
     * Execute an INPUT statement
     */
    
    virtual void execute(EvalState & state);

    virtual StatementType getType();
    
private:
    std::string name;
    
};

class ENDStatement : public Statement
{
public:
    
    /*
     * Method: execute
     * Usage: stmt->execute(state);
     * ----------------------------
     * Execute an INPUT statement
     */
    
    virtual void execute(EvalState & state);

    virtual StatementType getType();
    
};

class GOTOStatement : public Statement
{
public:
    
    /*
     * Constructor: GOTOStatement
     * Usage: GOTOStatement* stmt = new GOTOStatement(exp)
     * ----------------------
     */
    
    GOTOStatement(int num);
    
    
    /*
     * Method: execute
     * Usage: stmt->execute(state);
     * ----------------------------
     * Execute an GOTO statement
     */
    
    virtual void execute(EvalState & state);

    virtual StatementType getType();

    int getLineNumber();
    
private:
    int lineNumber;
    
};

class IFStatement : public Statement
{
public:
    
    /*
     * Constructor: IFStatement
     * Usage: IFStatement* stmt = new IFStatement(exp)
     * ----------------------
     */
    
    IFStatement(Expression* left, Expression* right,
                std::string compare, int num);
    
    
    /*
     * Method: execute
     * Usage: stmt->execute(state);
     * ----------------------------
     * Execute an IF statement
     */
    
    virtual void execute(EvalState & state);

    virtual StatementType getType();

    bool result();
    int getLineNumber();
    
private:
    int lineNumber;
    Expression* lhs;
    Expression* rhs;
    std::string comp;
    bool jump;
    
};

/*  Handle Empty Statement
 *
 */

class EmptyStatement : public Statement
{
public:

    virtual void execute(EvalState & state);

    virtual StatementType getType();
};

#endif
