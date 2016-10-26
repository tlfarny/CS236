#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
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
    
    void factMaker(DatalogProgram& datalogIn, vector<Predicate>& tempPred){
        tempPred = datalogIn.getFacts();
        for (unsigned int i = 0; i < tempPred.size(); i++) {
            tempPred[i].getTuples();
            database[tempPred[i].getName()].IInsert(tempPred[i].tuples);
        }
    }           //2
    
    void iterateParameters(unsigned int& i, vector<Predicate>& tempPred, set<Tuple>& tempTuples, Relation& tempRelation, map<string, int>& variables, string& tempString, vector<string>& variableOrder, vector<int>& positions){
        tempTuples.clear();
        for (int g = 0; g < tempPred[i].getParameterSize(); g++) {                          //Cycling through parameters
            if (tempPred[i].isValue(g)==true) {
                string tempString = tempPred[i].checkParameter(g);
                tempRelation.selectValue(g, tempString, tempTuples);
            }
            else{
                if (variables.count(tempPred[i].checkParameter(g))) {                       //variable  is present in map
                    int mappedInt = variables[tempPred[i].checkParameter(g)];               //map position
                    tempRelation.selectVariable(g, mappedInt, tempTuples);                  //select variable
                }
                else{                                                                       //variable not present in map
                    //tempString = tempPred[i].checkParameter(g);
                    variables[tempPred[i].checkParameter(g)] = g;                           //add variable to map
                    variableOrder.push_back(tempPred[i].checkParameter(g));                 //add variable to order list of variables.
                    positions.push_back(g);                                                 //push position into positions vector
                }
            }
        }
    }
    
    
    void iterateParametersFront(Predicate& frontPred, vector<string>& fvariableOrder, vector<int>& fpositions, Relation& firstRelation){
        for (int i = 0; i < frontPred.getParameterSize(); i++) {
            for (unsigned int g = 0; g < firstRelation.getSchemeSize(); g++) {
                if (firstRelation.getScheme(g)==frontPred.checkParameter(i)) {
                    fvariableOrder.push_back(frontPred.checkParameter(i));
                    fpositions.push_back(g);
                }
            }
        }
    }
    
    bool canJoin(Scheme& scheme1, Tuple& tuple1, Scheme& scheme2, Tuple& tuple2, vector<int>& left, vector<int>& right){
        for (int i = 0; i < scheme1.size(); i++) {                                          //for each Scheme A
            for (int g = 0; g < scheme2.size(); g++) {                                      //check against Scheme B
                if (scheme1[i]==scheme2[g]) {                                               //if A matches B
                    if (tuple1[i]!=tuple2[g]) {                                             //if the tuple in A's spot doesn't match the tuple in B's spot
                        //cout<<"broken"<<endl;
                        return false;
                    }
                    else{                                                                   //otherwise
                        //cout<<"match"<<endl;
                        left.push_back(i);                                                  //mark A's Spot
                        right.push_back(g);                                                 //mark B's spot
                    }
                }
                else{
                    //cout<<"doesn't match "<<scheme1[i]<<" "<<scheme2[g]<<endl;
                }
            }
        }
        return true;
    }
    
    void join(Scheme& schemeRight, Scheme& schemeLeft, Tuple& tempTuple1, Tuple& tempTuple2, vector<int>& right){
        for (int i = 0; i < schemeRight.size(); i++) {                                      //for each scheme in the new group
            if (right.size()==0) {                                                          //if none matches, cartesian product
                tempTuple1.push_back(tempTuple2[i]);                                        //just slam everything together
            }
            else if (std::find(right.begin(), right.end(), i) != right.end()) {             //don't add if it is the spot that matches the joined tuple.
            }
            else{                                                                           //if it isn't a matching spot
                tempTuple1.push_back(tempTuple2[i]);                                        //push the tuple parameter onto the old Tuple (makes it longer)
            }
        }                                                                                   //should be the correct tuple
    }
    
    void ruleMaker(DatalogProgram& datalogIn, vector<Predicate>& tempPred){
        vector<Rule> tempRules = datalogIn.getRules();
        int passesThroughRules = 0;
        Relation tempRelation;
        int databaseSizeBefore = 0, databaseSizeAfter = 0;
        while (1) {                                                                         //while loop through rules
            databaseSizeBefore = 0;                                                         //reset fact counts.
            databaseSizeAfter = 0;
            typedef map<string, Relation>::const_iterator mapIterator;
            for (mapIterator iter = database.begin(); iter !=database.end(); iter++) {      //check how many facts there are before
                databaseSizeBefore +=database[iter->first].getTuplesSize();
            }
            for (unsigned int j = 0; j < tempRules.size(); j++) {                           //iterating through rules
                Predicate frontPred = tempRules[j].getFrontPredicate();                     //get front part of rule
                tempPred = tempRules[j].getBackPredicates();                                //get back rules list
                Relation firstRelation, nextRelation;
                map<string, int> variables;
                vector<int> positions;
                set<Tuple> tempTuples, newTuples, firstTuples, nextTuples;
                vector<string> variableOrder;
                vector<int> left, right;
                Scheme schemeLeft, schemeRight;
                bool joining = true, joined =false;
                string tempString;
                Tuple newTuple;
                for (unsigned int i = 0; i<tempPred.size(); i++) {                          //for each one of the listed rules
                    variableOrder.clear();
                    positions.clear();
                    variables.clear();
                    tempTuples.clear();
                    left.clear();
                    right.clear();
                    if (i==0) {                                                             //on the First Predicate of the back
                        firstRelation = database[tempPred[i].getName()];                    //copy first relation
                        iterateParameters(i, tempPred, tempTuples, tempRelation, variables, tempString, variableOrder, positions);//select
                        firstRelation.projectRules(positions);                              //project
                        firstRelation.renameRules(positions, variableOrder);                //rename
                    }
                    else{                                                                   //On the next of the back predicate
                        nextRelation = database[tempPred[i].getName()];                     //copy relation
                        iterateParameters(i, tempPred, tempTuples, nextRelation, variables, tempString, variableOrder, positions);//select
                        nextRelation.projectRules(positions);                               //project
                        nextRelation.renameRules(positions, variableOrder);                 //rename
                        schemeLeft = firstRelation.getSchemes();                            //copy schemes from joined relations
                        firstTuples = firstRelation.getTuples();                            //copy Tuples set from joined relations.
                        schemeRight = nextRelation.getSchemes();                            //copy schemes from new relation
                        nextTuples = nextRelation.getTuples();                              //copy tuples from new relation
                        newTuples.clear();
                        std::set<Tuple>::const_iterator it;
                        for (it = firstTuples.begin(); it!=firstTuples.end(); it++) {       //for each tuple in the joined
                            std::set<Tuple>::const_iterator it2;
                            for (it2 = nextTuples.begin(); it2!=nextTuples.end(); it2++) {  //check against the tuple in the new group
                                Tuple tempTuple1 = *it;
                                Tuple tempTuple2 = *it2;
                                joining = canJoin(schemeLeft, tempTuple1, schemeRight, tempTuple2, left, right);//checks old vs. new tuple
                                if (joining==true) {                                        //if they properly match
                                    joined = true;
                                    join(schemeRight, schemeLeft, tempTuple1, tempTuple2, right);
                                    newTuple = tempTuple1;
                                    newTuples.insert(newTuple);
                                }
                            }
                        }
                        if (joined ==true) {
                            for (int i = 0; i < schemeRight.size(); i++) {
                                if (right.size()==0) {
                                    firstRelation.addScheme(schemeRight[i]);
                                }
                                else if (std::find(right.begin(), right.end(), i) != right.end()) { //if i is the same spot as the matching variable
                                                                                            //do nothing
                                }
                                else{                                                       //otherwise
                                    firstRelation.addScheme(schemeRight[i]);                //add the schemes to the list.
                                }
                            }
                        }
                        /*                        nextRelation = database[tempPred[i].getName()];        //Copy Relation
                        //                        iterateParameters(i, tempPred, tempTuples, nextRelation, variables, tempString, variableOrder, positions);//select
                        //                        nextRelation.projectRules(positions);                            //project
                        //                        nextRelation.renameRules(positions, variableOrder);              //rename
                        //                        Scheme schemes1 = firstRelation.getSchemes(), schemes2 = nextRelation.getSchemes();
                        //                        vector<int> left, right;
                        
                        //                                                for (int i = 0; i < firstRelation.getTuplesSize(); i++) {
                        //                            for (int j = 0; j < nextRelation.getTuplesSize(); j++) {
                        //                                bool Joins = canJoin(firstRelation.getSchemes(), firstRelation., nextRelation.getSchemes(), , );
                        //                            }
                        //                        }
                        //firstRelation.join(nextRelation);*/
                        firstRelation.setTuples(newTuples);                                 //make the matching tuples the new tuples.
                        /*for (unsigned int i = 0; i < firstRelation.getSchemeSize(); i++) {
                            cout<<firstRelation.getScheme(i)<<" ";
                        }
                        cout<<endl;*/
                    }
                    
                }
                vector<int> fpositions;
                vector<string> fvariableOrder;
                iterateParametersFront(frontPred, fvariableOrder, fpositions, firstRelation);
                database[frontPred.getName()].projectFront(fpositions, fvariableOrder, firstRelation);
            }
            typedef map<string, Relation>::const_iterator mapIterator;
            for (mapIterator iter = database.begin(); iter !=database.end(); iter++) {
                databaseSizeAfter +=database[iter->first].getTuplesSize();
            }
            passesThroughRules++;
            if (databaseSizeBefore==databaseSizeAfter) {
                break;
            }
        }
        /*typedef map<string, Relation>::const_iterator mapIter;
        for (mapIter iter = database.begin(); iter!=database.end(); iter++) {
            tempRelation = iter->second;
            cout<<tempRelation.getName()<<endl;
            tempRelation.toString();
        }*/
        cout<<"Schemes populated after "<<passesThroughRules<<" passes through the Rules."<<endl;
    }
    
    void queryMaker(DatalogProgram& datalogIn, vector<Predicate>& tempPred){
        tempPred = datalogIn.getPQueries();
        //cout<<"Query Evaluation"<<endl<<endl;
        for (unsigned int i = 0; i<tempPred.size(); i++) {                  //Cycling through Queries
            map<string, int> variables;
            vector<int> positions;
            set<Tuple> tempTuples;
            vector<string> variableOrder;
            string tempString = "";
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
        factMaker(datalogIn, tempPred);
        ruleMaker(datalogIn, tempPred);
        queryMaker(datalogIn, tempPred);
    }
};