#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "Predicate.h"
#include "Relation.h"
#include "DatalogProgram.h"

using namespace std;

class Database{
    
private:
    map<string,Relation> database;
    
public:
    Database(){}
    ~Database(){}
    
    void schemeMaker(DatalogProgram& datalogIn, vector<Predicate>& tempPred){
        tempPred = datalogIn.getScheme();
        for (unsigned int i = 0; i < tempPred.size(); i++) {
            string name = tempPred[i].getName();
            Scheme scheme = tempPred[i].getScheme();
            Relation tempRelation = Relation(name, scheme);
            database[name]= tempRelation;
        }
    }         //2
    
    /*void schemeEval(){
        cout<<"Scheme Evaluation"<<endl<<endl;
    } */                                                  //1
    
    void factMaker(DatalogProgram& datalogIn, vector<Predicate>& tempPred){
        tempPred = datalogIn.getFacts();
        for (unsigned int i = 0; i < tempPred.size(); i++) {
            tempPred[i].getTuples();
            database[tempPred[i].getName()].IInsert(tempPred[i].tuples);
        }
    }           //2
    
    /*void factEval(){
        cout<<"Fact Evaluation"<<endl<<endl;
        typedef map<string, Relation>::const_iterator mapIterator;
        for (mapIterator iter = database.begin(); iter !=database.end(); iter++) {
            cout<<iter->first<<endl;
            iter->second.toString();
            cout<<endl;
        }
    }  */                                                   //2
    
    void ruleMaker(){
        
    }
    
    void ruleEval(){
        
    }
    
    void queryMaker(DatalogProgram& datalogIn, vector<Predicate>& tempPred){
        tempPred = datalogIn.getPQueries();
        //cout<<"Query Evaluation"<<endl<<endl;
        for (unsigned int i = 0; i<tempPred.size(); i++) {                  //Cycling through Queries
            map<string, int> variables;
            vector<int> positions;
            set<Tuple> tempTuples;
            vector<string> variableOrder;
            string tempString;
            Relation tempRelation = database[tempPred[i].getName()];        //Copy Relation
            for (int g = 0; g < tempPred[i].getParameterSize(); g++) {      //Cycling through parameters of query
                tempTuples.clear();
                if (tempPred[i].isValue(g)==true) { 
                    string tempString = tempPred[i].checkParameter(g);
                    tempRelation.selectValue(g, tempString, tempTuples);
                }
                else{
                    if (variables.count(tempPred[i].checkParameter(g))) {   //variable  is present in map
                        int mappedInt = variables[tempPred[i].checkParameter(g)]; //map position
                        tempRelation.selectVariable(g, mappedInt, tempTuples);  //select variable
                    }
                    else{                                                  //variable not present in map
                        tempString = tempPred[i].checkParameter(g);
                        variables[tempPred[i].checkParameter(g)] = g;
                        variableOrder.push_back(tempPred[i].checkParameter(g));
                        positions.push_back(g);
                    }
                }
            }
            queryEval(datalogIn, tempPred, positions, variableOrder, tempRelation, i);
        }
    }  //7
    
    void queryDisplay(vector<Predicate>& tempPred, unsigned int& position){
        vector<Parameter> tempParameters;
        cout<<tempPred[position].getName()<<"(";
        tempParameters = tempPred[position].getParameters();
        for (unsigned int g = 0; g < tempPred[position].getParameterSize(); g++) {
            if (tempParameters[g].getValue()==true) {
                cout<<tempParameters[g].getName();
            }
            else if (tempParameters[g].getVariable()==true){
                cout<<tempParameters[g].getName();
            }
            if (g<tempParameters.size()-1) {
                cout<<",";
            }
        }
        cout<<")? ";
    }  //5
    
    void queryEval(DatalogProgram& datalogIn, vector<Predicate>& tempPred, vector<int>& positions, vector<string>& variableOrder,  Relation& tempRelation,unsigned int& position){
        vector<Parameter> tempParameters;
        queryDisplay(tempPred, position);           //Good to this point
        if (tempRelation.getTuplesSize()<=0) {
            cout<<"No"<<endl;
        }
        else{
            cout<<"Yes("<<tempRelation.getTuplesSize()<<")"<<endl;
            //tempRelation.selectDisplay();
            //tempRelation.project(positions);
            tempRelation.rename(positions, variableOrder);              //I Think that I just need to display rename, but add commas
        }
        
    }  //3
    
    void DDatabase(DatalogProgram& datalogIn){
        vector<Predicate> tempPred;
        schemeMaker(datalogIn, tempPred);
        //schemeEval();
        factMaker(datalogIn, tempPred);
        //factEval();
        queryMaker(datalogIn, tempPred);
    }
    
};