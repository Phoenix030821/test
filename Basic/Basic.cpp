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

/* Main program */

int main() {
   EvalState state;
   Program program;
  // cout << "Stub implementation of BASIC" << endl;
   while (true) {
      try {
         processLine(getLine(), program, state);
      } catch (ErrorException & ex) {
         cout  << ex.getMessage() << endl;
      }
   }
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

void processLine(string line,Program &program,EvalState &state){
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    string s=scanner.nextToken();
    if(s[0]>='0'&&s[0]<='9'){
        int th=0,len=s.length();
        for(int x=0;x<len;x++)th*=10,th+=s[x]-'0';
        program.addSourceLine(th,line);
        string t=scanner.nextToken();
        if(t=="LET"){
            Expression *exp=parseExp(scanner);
            if(exp->getType()!=COMPOUND)error("SYNTAX ERROR");
            Statement *l=new letit(exp);
            program.setParsedStatement(th,l);
        }
        else if(t=="IF"){
            int now=line.find("THEN");
            string fir=line.substr(0,now-1);
            TokenScanner sca;
            sca.ignoreWhitespace();
            sca.scanNumbers();
            sca.setInput(fir);
            while(sca.nextToken()!="IF");
            Expression *exp=parseExp(sca);exp->jud();
            if(exp->getType()!=COMPOUND)error("SYNTAX ERROR");
            while(scanner.nextToken()!="THEN");
            Expression *q=parseExp(scanner);
            if(q->getType()!=CONSTANT)error("SYNTAX ERROR");
            int r=q->eval(state);
            Statement *l=new ifit(exp,r);
            program.setParsedStatement(th,l);
        }
        else if(t=="GOTO"){
            Expression *exp=parseExp(scanner);
            if(exp->getType()!=CONSTANT)error("SYNTAX ERROR");
            Statement *l=new gotoit(exp->eval(state));
            program.setParsedStatement(th,l);
        }
        else if(t=="INPUT"){
            Expression *exp=parseExp(scanner);
            Statement *l=new inputit(exp);
            program.setParsedStatement(th,l);
        }
        else if(t=="PRINT"){
            Expression *exp=parseExp(scanner);
            Statement *l=new printit(exp);
            program.setParsedStatement(th,l);
        }
        else if(t=="END"){
            Statement *l=new endit;
            program.setParsedStatement(th,l);
        }
        else if(t=="REM"){
            Statement *l=new remit;
            program.setParsedStatement(th,l);
        }
        else if(t==""){
            program.removeSourceLine(th);
        }
        else{
            error("SYNTAX ERROR");
        }
        return;
    }
    if(s=="LET"){
        Expression *exp=parseExp(scanner);
        exp->eval(state);
    }
    else if(s=="INPUT"){
        Expression *exp=parseExp(scanner);
        if(exp->getType()!=IDENTIFIER)error("SYNTAX ERROR");
        cout<<" ? ";
        string a;
        while(1){
            getline(cin,a);int len=a.length();bool fl=0;
            if(len==1&&(a[0]<'0'||a[0]>'9'))fl=1;
            for(int x=0;x<len;x++){
                if(x==0&&a[x]=='-')continue;
                if(a[x]<'0'||a[x]>'9'){
                    fl=1;break;
                }
            }
            if(!fl){
                int p=0;
                if(a[0]!='-')for(int x=0;x<len;x++)p*=10,p+=a[x]-'0';
                else {
                    for(int x=1;x<len;x++)p*=10,p+=a[x]-'0';p*=-1;
                }
                state.setValue(exp->toString(),p);break;
            }
            cout<<"INVALID NUMBER"<<endl;
            cout<<" ? ";
        }
    }
    else if(s=="PRINT"){
        Expression *exp=parseExp(scanner);
        cout<<exp->eval(state)<<endl;
    }
    else if(s=="RUN"){
        int i=program.getFirstLineNumber();
        while(i){
            program.getParsedStatement(i)->execute(state);
           if(program.getParsedStatement(i)->fl==0x3f3f3f3f){
                program.clear();break;
            }
            if(program.getParsedStatement(i)->fl)i=program.getParsedStatement(i)->fl;
            else i=program.getNextLineNumber(i);
        }

    }
    else if(s=="LIST"){
        int i=program.getFirstLineNumber();
        while(i){
            cout<<program.getSourceLine(i)<<endl;
            i=program.getNextLineNumber(i);
        }
    }
    else if(s=="QUIT"){
        exit(0);
    }
    else if(s=="CLEAR"){
        state.clea();
        program.clear();
    }
    else if(s=="HELP"){
        cout<<"Yet another basic interpreter"<<endl;
    }
    else{
        error("SYNTAX ERROR");
    }
}
/*void processLine(string line, Program & program, EvalState & state) {
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);
   Expression *exp = parseExp(scanner);
   int value = exp->eval(state);
   cout << value << endl;
   delete exp;
}*/
