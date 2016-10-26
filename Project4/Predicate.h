#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "Scheme.h"
#include "Parameter.h"
#include "Tuple.h"

using namespace std;

class Predicate {
public:
    Predicate(string nameIn): name(nameIn) {}
    ~Predicate(){}
    
    Tuple tuples;
    
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
    
    string getName(){
        return name;
    }
    
    vector<string> getStrings(){
        vector<string> parametersToReturn;
        for (unsigned int i = 0; i < parameters.size(); i++) {
            parametersToReturn.push_back(parameters[i].getName());
        }
        return parametersToReturn;
    }
    
    vector<Parameter> getParameters(){
        return parameters;
    }
    
    Scheme getScheme(){
        Scheme names;
        for (unsigned int i = 0; i < parameters.size(); i++) {
            names.push_back(parameters[i].getName());
        }
        return names;
    }
    
    void getTuples(){
        for (unsigned int i = 0; i < parameters.size(); i++) {
            tuples.push_back(parameters[i].getName());
        }
    }
    
    int getParameterSize(){
        return parameters.size();
    }
    
    string checkParameter(int& position){
        return parameters[position].getName();
    }
    
    bool isValue(int& position){
        bool val = parameters[position].getValue();
        return val;
    }
    
    bool isVariable(int& position){
        bool var = parameters[position].getVariable();
        return var;
    }
    
private:
    string name;
    vector<Parameter> parameters;
};