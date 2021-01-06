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
void ScannerToStatement(string Type,Program &program,int num,string line);
string ScannerToString(TokenScanner &scanner,string Type);

/* Main program */

int main() {
   EvalState state;
   Program program;
   while (true) {
      try {
         processLine(getLine(), program, state);
      } catch (ErrorException & ex) {
         cerr << "Error: " << ex.getMessage() << endl;
      }
   }
   program.clear();
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
    scanner.scanStrings();
    scanner.scanNumbers();
    scanner.setInput(line);
    if (line == "QUIT") {
        exit(0);
    }
    if (line == "RUN") {
        program.run(state);
    }
    if (line == "LIST") {
        program.list(state);
    }
    if (line == "CLEAR") {
        program.clear();
        state.clear();
    }
    else {
       if(line[0]>='0'&&line[0]<='9')
       {
              int line_num = atoi(scanner.nextToken().c_str());
        if(!scanner.hasMoreTokens()) program.removeSourceLine(line_num);
        else{
            string Type =scanner.nextToken();
            string smp = ScannerToString(scanner,Type);
            program.addSourceLine(line_num,smp);
            ScannerToStatement(Type,program,line_num,smp);
        }
       }
       else{
          string scp=scanner.nextToken();
          if(scp=="LET") {
             let tmp(0,ScannerToString(scanner,"LET"));
             tmp.execute(state);
          }
          else if(scp=="PRINT"){
             Print tmp(0,ScannerToString(scanner,"PRINT"));
             tmp.execute(state);
          }
          else if(scp=="INPUT"){
             input tmp(0,ScannerToString(scanner,"INPUT"));
             tmp.execute(state);
          }
       }
    }
}
string ScannerToString(TokenScanner &scanner,string Type)
{
    string tmp=Type+" ";
    while(scanner.hasMoreTokens()){
        tmp+=scanner.nextToken();
        if(scanner.hasMoreTokens())
        tmp+=" "; 
}
  return tmp;
}
void ScannerToStatement(string Type,Program &program,int num,string tmp){
    Statement *exp;
    if(Type=="LET"){exp=new let(num,tmp);program.setParsedStatement(num,exp);}
    if(Type=="PRINT"){exp=new Print(num,tmp);program.setParsedStatement(num,exp);}
    if(Type=="INPUT"){exp=new input(num,tmp);program.setParsedStatement(num,exp);}
    if(Type=="GOTO"){exp=new Goto(num,tmp);program.setParsedStatement(num,exp);}
    if(Type=="IF"){exp=new if_then_(num,tmp);program.setParsedStatement(num,exp);}
    if(Type=="END"){exp=new End(num,tmp);program.setParsedStatement(num,exp);}
    if(Type=="REM"){exp=new rem(num,tmp);program.setParsedStatement(num,exp);}
}
