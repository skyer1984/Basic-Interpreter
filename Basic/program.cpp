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
Program::Program()=default;
Program::~Program() {
        for(auto i:p){
            delete i.second.states;
        }
        p.clear();
   // Replace this stub with your own code
}

void Program::clear() {
    for(auto i:p){
        delete i.second.states;
    }
    p.clear();
   // Replace this stub with your own code
}

void Program::addSourceLine(int lineNumber, string line) {
        if(p[lineNumber].states!= nullptr) {
           delete p[lineNumber].states;
           p[lineNumber].states=nullptr;
        }
        p[lineNumber].source_line=line;
   // Replace this stub with your own code
}

void Program::removeSourceLine(int lineNumber) {
    delete p[lineNumber].states;
    p.erase(lineNumber);
   // Replace this stub with your own code
}

string Program::getSourceLine(int lineNumber) {
    if(p.count(lineNumber))
        return p[lineNumber].source_line;
   return "";    // Replace this stub with your own code
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
     if(!p.count(lineNumber))
         error("SYNTAX ERROR");
     else
     {
         if(p[lineNumber].states!= nullptr) {
             delete p[lineNumber].states;
             p[lineNumber].states= nullptr;
         }
         p[lineNumber].states=stmt;
     }
   // Replace this stub with your own code
}

Statement *Program::getParsedStatement(int lineNumber) {
    if(p[lineNumber].states!= nullptr) return p[lineNumber].states;
   return NULL;  // Replace this stub with your own code
}

int Program::getFirstLineNumber() {
    if(!p.empty())
        return p.begin()->first;
    return -1;     // Replace this stub with your own code
}

int Program::getNextLineNumber(int lineNumber) {
  if(lineNumber==-1) return getFirstLineNumber();
  else{
      auto i = p.find(lineNumber);
      if(++i!=p.end()) return i->first;
  }
   return -1;     // Replace this stub with your own code
}
void Program::run(EvalState &state){
   state.current_line=getFirstLineNumber();
   for(int &i=state.current_line;i!=-1;i=getNextLineNumber(i))
   {
      bool flag=false;
       p[i].states->execute(state);
       if(i==0) break;
       while(i<0){
          i=-i;
          if(!p.count(i)) {
             cout<<"LINE NUMBER ERROR"<<endl;
             flag=true;
             break;}
          else p[i].states->execute(state);
       }
       if(flag) break; 
   }
}
void Program::list(EvalState &state) {
    for(auto i:p)
        i.second.states->print();
}