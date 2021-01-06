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
    head.nxt= nullptr;
}

Program::~Program() {
   lines *a=head.nxt,*b= nullptr;
   while(a!= nullptr){
       b=a->nxt;delete a;a=b;
   }
}

void Program::clear() {
    lines *a=head.nxt,*b= nullptr;
    head.nxt= nullptr;
    while(a!= nullptr){
        b=a->nxt;delete a;a=b;
    }
}

void Program::addSourceLine(int lineNumber, string line) {
    lines *a=&head;
    while(a->nxt!= nullptr&&a->nxt->num<lineNumber)a=a->nxt;
    if(a->nxt== nullptr||a->nxt->num!=lineNumber){
        lines *p=new lines;p->num=lineNumber;p->lin=line;
        p->nxt=a->nxt;a->nxt=p;
    }
    else{
        a->nxt->lin=line;
    }
}

void Program::removeSourceLine(int lineNumber) {
   lines *a=&head;
   while(a->nxt== nullptr||a->nxt->num<lineNumber)a=a->nxt;
   if(a->nxt== nullptr||a->nxt->num>lineNumber)error("LINE NUMBER ERROR");
   else{
       lines *p=a->nxt;
       a->nxt=a->nxt->nxt;delete p;
   }
}

string Program::getSourceLine(int lineNumber) {
   lines *a=&head;
   while(a->nxt!= nullptr&&a->nxt->num<lineNumber)a=a->nxt;
   if(a->nxt== nullptr||a->nxt->num>lineNumber)error("LINE NUMBER ERROR");
   else{
      return a->nxt->lin;
   }
   return 0;
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    lines *a=&head;
    while(a->nxt->num<lineNumber)a=a->nxt;
    a->nxt->s=stmt;
}

Statement *Program::getParsedStatement(int lineNumber) {
   lines *a=&head;
   while(a->nxt->num<lineNumber)a=a->nxt;
   return a->nxt->s;
}

int Program::getFirstLineNumber() {
    if(head.nxt== nullptr)return 0;
   return head.nxt->num;
}

int Program::getNextLineNumber(int lineNumber) {
   lines *a=&head;
   while(a->nxt!= nullptr&&a->nxt->num<=lineNumber)a=a->nxt;
   if(a->nxt== nullptr)return 0;
   return a->nxt->num;
}
