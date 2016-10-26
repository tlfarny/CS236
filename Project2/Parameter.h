#pragma once
#include <fstream>

using namespace std;

class Parameter{
    
public:
    Parameter(string nameIn, bool isValueIn, bool isVariableIn): Name(nameIn), isValue(isValueIn), isVariable(isVariableIn){}
    ~Parameter(){}
    
    void toString(){
        if (isValue==true) {
            cout<<Name;
        }
        else if (isVariable==true){
            cout<<Name;
        }
    }
private:
    string Name;
    bool isValue;
    bool isVariable;
    
    
};