/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <cstring>
#include "statement.h"
#include "../StanfordCPPLib/simpio.h"
#include "parser.h"

using namespace std;

/* Implementation of the Statement class */

Statement::Statement(int l,string v):line_number(l),line(v) {
   /* Empty */
}
void Statement::print() {
    cout<<line_number<<" "<<line<<endl;
}
void let::execute(EvalState &state) {
    TokenScanner *scanner=new TokenScanner;
    scanner->scanStrings();
    scanner->ignoreWhitespace();
    scanner->scanNumbers();
    scanner->setInput(line);
    string tmp=scanner->nextToken();
    string record;
    while(tmp!="="){
        record=tmp;
        tmp=scanner->nextToken();
    }
    if(record=="LET") cout<<"SYNTAX ERROR"<<endl;
    Expression *exp=parseExp(*scanner);
    int value=exp->eval(state);
    if(value==-99999){
       cout<<"VARIABLE NOT DEFINED"<<endl;
    }
    else state.setValue(record,value);
    delete scanner;
}
void Print::execute(EvalState &state) {
    TokenScanner *scanner=new TokenScanner;
    scanner->scanStrings();
    scanner->scanNumbers();
    scanner->ignoreWhitespace();
    scanner->setInput(line);
    scanner->nextToken();
    Expression *exp=parseExp(*scanner);
    int value=exp->eval(state);
    if(value==-99999){
       cout<<"VARIABLE NOT DEFINED"<<endl;
    }
    else cout<<exp->eval(state)<<endl;
    delete scanner;
}
void input::execute(EvalState &state) {
    TokenScanner *scanner=new TokenScanner;
    scanner->scanStrings();
    scanner->ignoreWhitespace();
    scanner->scanNumbers();
    scanner->setInput(line);
    scanner->nextToken();
    string var=scanner->nextToken();
    bool flag=true;
   while(flag){
      flag=false;
      cout<<" ? ";
      string smp=getLine();
      if(!isnum(smp)) {
         cout<<"INVALID NUMBER"<<endl;
         flag=true;}
      else{
         int tmp=atoi(smp.c_str());
         state.setValue(var,tmp);
      }
   }
    delete scanner;
}
bool input::isnum(string n){
   if((n[0]>='0'&&n[0]<='9')||n[0]=='-'){
      for(int i=1;i<n.length();++i){
          if(n[i]<'0'||n[i]>'9') return false;
      }
      return true;
   }
   else return false;
}
void End::execute(EvalState &state) {
    state.current_line=0;
}
void Goto::execute(EvalState &state) {
    TokenScanner *scanner=new TokenScanner;
    scanner->scanStrings();
    scanner->ignoreWhitespace();
    scanner->scanNumbers();
    scanner->setInput(line);
    scanner->nextToken();
    state.current_line=-atoi(scanner->nextToken().c_str());
    delete scanner;
}
void rem::execute(EvalState &state) {return;}
void if_then_::execute(EvalState &state) {
    int left,right;
    TokenScanner *scanner=new TokenScanner;
    scanner->scanStrings();
    scanner->scanNumbers();
    scanner->ignoreWhitespace();
    scanner->setInput(line);
    scanner->nextToken();
    string tmp="";
    string code=scanner->nextToken();
    while(code!="<" &&code!="="&&code!=">")
    {
        tmp+=code;
        tmp+=" ";
        code=scanner->nextToken();
    }
    string op=code;
    TokenScanner tmp_scanner1;
    tmp_scanner1.ignoreWhitespace();
    tmp_scanner1.scanNumbers();
    tmp_scanner1.scanStrings();
    tmp_scanner1.setInput(tmp);
    left=parseExp(tmp_scanner1)->eval(state);
    tmp.clear();
    code=scanner->nextToken();
    while(code!="THEN")
    {
        tmp+=code;
        tmp+=" ";
        code=scanner->nextToken();
    }
    TokenScanner tmp_scanner2;
    tmp_scanner2.ignoreWhitespace();
    tmp_scanner2.scanNumbers();
    tmp_scanner2.scanStrings();
    tmp_scanner2.setInput(tmp);
    right=parseExp(tmp_scanner2)->eval(state);
    bool flag;
    if(op=="<") flag=(left<right);
    if(op=="=") flag=(left==right);
    if(op==">") flag=(left>right);
    if(flag)  state.current_line=-atoi(scanner->nextToken().c_str());
   delete scanner;
}