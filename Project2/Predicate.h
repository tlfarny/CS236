#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "Parameter.h"

using namespace std;

class Predicate {
public:
    Predicate(string nameIn): name(nameIn) {}
    ~Predicate(){}
    
    
    void ppushback(Parameter parameterIn){
        parameters.push_back(parameterIn);
    }  //1
    
    void toString(){
        cout<<name<<"(";
        for (unsigned int i=0; i<parameters.size(); i++) {
            parameters[i].toString();
            if (i < parameters.size()-1) {
                cout<<",";
            }
        }
        cout<<")";
    }  //3
    
private:
    string name;
    vector<Parameter> parameters;
};