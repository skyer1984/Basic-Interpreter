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
#include "../StanfordCPPLib/tokenscanner.h"
#include <string>

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {
public:
    int line_number;
    std::string line;
/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   Statement(int l,string v);

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */


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
   void print();

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
/*
 * 赋值语句
 */
class let:public Statement{
public:
    let(int l,string v):Statement(l,v){}
    void execute(EvalState &state) override;
};
/*
 * 注释
 */
class rem: public Statement{
public:
    rem(int l,string v):Statement(l,v){}
    void execute(EvalState &state) override;
};
/*
 *输出
 */
class Print: public Statement{
public:
    Print(int l,string v):Statement(l,v){}
    void execute(EvalState &state) override;
};
/*
 * 输入
 */
class input:public Statement{
    public:
     input(int v,string l):Statement(v,l){}
     void execute(EvalState &state) override;
     bool isnum(string n);
};
/*
 * 结束
 */
class End:public Statement{
public:
    End(int v,string l):Statement(v,l){}
    void execute(EvalState &state) override;
};
class Goto:public Statement{
public:
    Goto(int v,string l):Statement(v,l){}
    void execute(EvalState &state);
};
class if_then_:public Statement{
public:
    if_then_(int v,string l):Statement(v,l){}
    void execute(EvalState &state);
};

#endif
