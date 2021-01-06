/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}
void letit::execute(EvalState &state) {
    from->eval(state);
}
void ifit::execute(EvalState &state) {
    if(jud->eval(state))fl=li;
    else fl=0;
}
void inputit::execute(EvalState &state) {
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
            state.setValue(from->toString(),p);break;
        }
        cout<<"INPUT ERROR"<<endl;
        cout<<" ? ";
    }
}
void printit::execute(EvalState &state) {
    cout<<state.getValue(from->toString());
}
void gotoit::execute(EvalState &state) {
    fl=li;
    return;
}
void remit::execute(EvalState &state) {
    return;
}
void endit::execute(EvalState &state) {
    return;
}
