#pragma once
#include <set>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Predicate.h"
#include "Rule.h"

using namespace std;

class DatalogProgram{
public:
    DatalogProgram(){}
    ~DatalogProgram(void){}
    
    void toString(){
        cout<<"Schemes("<<Scheme.size()<<"):"<<endl;
        for (unsigned int i=0; i<Scheme.size(); i++) {
            cout<<"  ";
            Scheme[i].toString();
            cout<<endl;
        }
        cout<<"Facts("<<Facts.size()<<"):"<<endl;
        for (unsigned int i = 0; i<Facts.size(); i++) {
            cout<<"  ";
            Facts[i].toString();
            cout<<"."<<endl;
        }
        cout<<"Rules("<<Rules.size()<<"):"<<endl;
        for (unsigned int i=0; i<Rules.size(); i++) {
            cout<<"  ";
            Rules[i].toString();
            cout<<"."<<endl;
        }
        cout<<"Queries("<<PQueries.size()<<"):"<<endl;
        for (unsigned int i = 0; i<PQueries.size(); i++) {
            cout<<"  ";
            PQueries[i].toString();
            cout<<"?"<<endl;
        }
        cout<<"Domain("<<Domain.size()<<"):"<<endl;
        std::set<string>::iterator it;
        for (it = Domain.begin(); it!=Domain.end(); it++) {
            cout<<"  "<<*it<<endl;
        }
    }  //5
    
    void ppushbackScheme(Predicate predicateIn){
        Scheme.push_back(predicateIn);
    }  //1
    
    void ppushbackFacts(Predicate predicateIn){
        Facts.push_back(predicateIn);
    }  //1
    
    void ppushbackPQueries(Predicate predicateIn){
        PQueries.push_back(predicateIn);
    }  //1
    
    void ppushbackRules(Rule ruleIn){
        Rules.push_back(ruleIn);
    }  //1
    
    void iinsert(string stringIn){
        Domain.insert(stringIn);
    }  //1
    
private:
    vector<Predicate> Scheme;
    vector<Predicate> Facts;
    vector<Predicate> PQueries;
    vector<Rule> Rules;
    set<string> Domain;
};
