#pragma once
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <fstream>
#include "Scheme.h"
#include "Tuple.h"

using namespace std;

class Relation{
    
private:
    string Name;
    Scheme scheme;
    set<Tuple> tuples;
    
public:
    Relation(){}
    Relation(string nameIn, Scheme schemeIn): Name(nameIn), scheme(schemeIn){}
    ~Relation(){}
    
    void IInsert(Tuple& tupleIn){
        tuples.insert(tupleIn);
    }  //1
    
    string getName(){
        return Name;
    }
    
    string getScheme(unsigned int& position){
        return scheme[position];
    }
    
    Scheme getSchemes(){
        return scheme;
    }
    
    void setSchemes(set<Tuple>& newTuplesIn){
        tuples = newTuplesIn;
    }
    
    void addScheme(string& stringIn){
        scheme.push_back(stringIn);
    }
    
    int getTuplesSize(){
        return tuples.size();
    }  //1
    
    set<Tuple> getTuples(){
        return tuples;
    }
    
    int getSchemeSize(){
        return scheme.size();
    }
    
    void setTuples(set<Tuple>& tempTuples){
        tuples = tempTuples;
    }  //1
    
    void toString() const{
        std::set<Tuple>::const_iterator it;
        for (it = tuples.begin(); it!=tuples.end(); it++) {
            Tuple tempTuple = *it;
            cout<<" ";
            for (unsigned int i=0; i<scheme.size(); i++) {
                cout<<" "<<scheme[i]<<"="<<tempTuple[i];
            }
            cout<<endl;
        }
    }  //3
    
    void selectValue(int& position, string& content, set<Tuple>& tempTuplesIn){
        std::set<Tuple>::const_iterator it;
        for (it = tuples.begin(); it != tuples.end(); it++) {
            //iterate through the set and check every tuple for the string at the position and add it to the tempTuples
            Tuple tempTuple = *it;
            if (tempTuple[position]==content) {
                tempTuplesIn.insert(tempTuple);
            }
        }
        tuples = tempTuplesIn;
    }  //3
    
    void selectVariable(int& position, int& mappedInt, set<Tuple>& tempTuplesIn){
        std::set<Tuple>::const_iterator it;
        for (it = tuples.begin(); it != tuples.end(); it++) {
            //iterate through the set and check every tuple for the string at the position and add it to the tempTuples
            Tuple tempTuple = *it;
            if (tempTuple[position]==tempTuple[mappedInt]) {
                tempTuplesIn.insert(tempTuple);
            }
        }
        tuples = tempTuplesIn;
    }  //3
    
    void selectDisplay(){
        cout<<"select"<<endl;
        std::set<Tuple>::const_iterator it;
        for (it = tuples.begin(); it!=tuples.end(); it++) {
            Tuple tempTuple = *it;
            cout<<" ";
            for (unsigned int i=0; i<scheme.size(); i++) {
                cout<<" "<<scheme[i]<<"="<<tempTuple[i];
            }
            cout<<endl;
        }
    }  //3
    
    void selectNoDisplay(){
        std::set<Tuple>::const_iterator it;
        for (it = tuples.begin(); it!=tuples.end(); it++) {
            Tuple tempTuple = *it;
            //cout<<" ";
            for (unsigned int i=0; i<scheme.size(); i++) {
                //cout<<" "<<scheme[i]<<"='"<<tempTuple[i]<<"'";
            }
            //cout<<endl;
        }
    }
    
    void project(vector<int>& positions){
        cout<<"project"<<endl;
        if (positions.size()==0) {
            
        }
        else{
            std::set<Tuple>::const_iterator it;
            for (it = tuples.begin(); it!=tuples.end(); it++) {
                Tuple tempTuple = *it;
                cout<<" ";
                for (unsigned int i = 0; i < positions.size(); i++) {
                    cout<<" "<<scheme[positions[i]]<<"="<<tempTuple[positions[i]];
                }
                cout<<endl;
            }
        }
    }  //4
    
    void projectNoDisplay(vector<int>& positions){
        if (positions.size()==0) {
            
        }
        else{
            std::set<Tuple>::const_iterator it;
            for (it = tuples.begin(); it!=tuples.end(); it++) {
                Tuple tempTuple = *it;
                cout<<" ";
                for (unsigned int i = 0; i < positions.size(); i++) {
                    cout<<" "<<scheme[positions[i]]<<"="<<tempTuple[positions[i]]<<"";
                }
                cout<<endl;
            }
        }
        
    }
    
    void projectRules(vector<int>& positions){
        set<Tuple> newTuples;
        if (positions.size()==0) {
            
        }
        else{
            Scheme newScheme;
            std::set<Tuple>::const_iterator it;
            for (it = tuples.begin(); it!=tuples.end(); it++) {
                Tuple tempTuple = *it;
                Tuple newTuple;
                newScheme.clear();
                newTuple.clear();
                for (unsigned int i = 0; i < positions.size(); i++) {
                    newScheme.push_back(scheme[positions[i]]);
                    newTuple.push_back(tempTuple[positions[i]]);
                }
                newTuples.insert(newTuple);
            }
            tuples = newTuples;
            scheme = newScheme;
        }
    }  //4
    
    void projectFront(vector<int> fpositions, vector<string> fvariables, Relation& firstRelation){
        //cout<<"projectfront "<<fpositions.size()<<" "<<fvariables.size()<<" "<<firstRelation.getTuplesSize()<<" "<<tuples.size()<< endl;
        if (fpositions.size()<=0) {
        }
        else{
            std::set<Tuple>::const_iterator iter;
            for (iter = firstRelation.tuples.begin(); iter!= firstRelation.tuples.end (); iter++) {
                Tuple tempTuple = *iter;
                Tuple newTuple;
                for (int i = 0; i < fpositions.size(); i++) {
                    if (firstRelation.scheme[fpositions[i]]==fvariables[i]) {
                        newTuple.push_back(tempTuple[fpositions[i]]);
                        //cout<<tempTuple[fpositions[i]]<<" ";
                    }
                }
                //cout<<endl;
                tuples.insert(newTuple);
            }
        }
        //cout<<"projectfront "<<fpositions.size()<<" "<<fvariables.size()<<" "<<firstRelation.getTuplesSize()<<" "<<tuples.size()<< endl;
    }
    
    void rename(vector<int>& positions, vector<string>& variableOrder){
        if (variableOrder.size()==0) {
            
        }
        else{
            std::set<Tuple>::const_iterator it;
            for (it = tuples.begin(); it!=tuples.end(); it++) {
                Tuple tempTuple = *it;
                cout<<" ";
                for (unsigned int i = 0; i < variableOrder.size(); i++) {
                    cout<<" "<<variableOrder[i]<<"="<<tempTuple[positions[i]];
                    if (i+1<variableOrder.size()) {
                        cout<<",";
                    }
                }
                cout<<endl;
            }
        }
    }  //4
    
    void renameNoDisplay(vector<int>& positions, vector<string>& variableOrder){
        if (variableOrder.size()==0) {
            
        }
        else{
            std::set<Tuple>::const_iterator it;
            for (it = tuples.begin(); it!=tuples.end(); it++) {
                Tuple tempTuple = *it;
                cout<<" ";
                for (unsigned int i = 0; i < variableOrder.size(); i++) {
                    cout<<" "<<variableOrder[i]<<"="<<tempTuple[positions[i]]<<"";
                }
                cout<<endl;
            }
        }
        cout<<endl;
    }
    
    void renameRules(vector<int>& positions, vector<string>& variableOrder){
        if (variableOrder.size()==0) {
            
        }
        else if (positions.size()==0){
            
        }
        else{
            Scheme newScheme;
            for (int i = 0; i < variableOrder.size(); i++) {
                scheme[positions[i]] = variableOrder[positions[i]];
            }
        }
    }  //4
    
    void renameRulesFront(vector<int>& positions, vector<string>& variableOrder){
        if (variableOrder.size()==0) {
            
        }
        else{
            Scheme newScheme;
            for (int i = 0; i < variableOrder.size(); i++) {
                scheme[positions[i]] = variableOrder[positions[i]];
            }
        }
    }  //4
    
    void checkInsideSet(int& firstPosition, int& secondPosition, Relation& relationToAdd, set<Tuple>& combinedTuples, Tuple& tempTuple1, set<Tuple>& tuplesToCheck){
        std::set<Tuple>::const_iterator iter;
        for (iter=tuplesToCheck.begin(); iter!=tuplesToCheck.end(); iter++) {
            Tuple tempTuple2 = *iter;
            cout<<"1 "<<tempTuple1[firstPosition]<<endl;
            cout<<"2 "<<tempTuple2[secondPosition]<<endl;
            if (tempTuple1[firstPosition]==tempTuple2[secondPosition]) {
                for (unsigned int i = 0; i < tempTuple2.size(); i++) {
                    tempTuple1.push_back(tempTuple2[i]);
                    cout<<"match"<<endl;
                }
                cout<<"combinedTuples.insert(tempTuple1);"<<endl;
                combinedTuples.insert(tempTuple1);
            }
        }
    }
    
    void checkForMatchingTuples(int& firstPosition, int& secondPosition, Relation& relationToAdd, set<Tuple>& combinedTuples){
        std::set<Tuple>::const_iterator it;
        set<Tuple> tuplesToCheck = relationToAdd.getTuples();
        for (it = tuples.begin(); it!=tuples.end(); it++) {
            Tuple tempTuple1 = *it;
            checkInsideSet(firstPosition, secondPosition, relationToAdd, combinedTuples, tempTuple1, tuplesToCheck);
        }
    }  //5
    
    Scheme schemeMaker(vector<string>& vectorToScheme){
        Scheme schemeToReturn;
        for (unsigned int i = 0; i < vectorToScheme.size(); i++) {
            schemeToReturn.push_back(vectorToScheme[i]);
        }
        return schemeToReturn;
    }
    
    void join(Relation& relationToAdd){
        vector<string> lettersToScheme = scheme;
        set<Tuple> combinedTuples;
        map<int, int> matchingVariables;
        string nameToMake = Name;
        for (int i = 0; i < relationToAdd.getSchemeSize(); i++) {
            lettersToScheme.push_back(relationToAdd.scheme[i]);
            nameToMake.append(relationToAdd.scheme[i]);
        }  //schemes built
        //combine relations or make a new relation
        for (unsigned int i = 0; i < scheme.size(); i++) {
            for (unsigned int g = 0; g < relationToAdd.getSchemeSize(); g++) {
                if (scheme[i] == relationToAdd.scheme[g]) {
                    matchingVariables[i] = g;//track locations where numbers match
                }
            }
        }  //All matching variable locations are known
        //iterate through the map checking for matching locations, adding them to a new set.
        
        typedef map<int, int>::const_iterator mapIterator;
        for (mapIterator iter = matchingVariables.begin(); iter !=matchingVariables.end(); iter++) {
            int firstPosition, secondPosition;
            firstPosition = iter->first;
            secondPosition = iter->second;
            checkForMatchingTuples(firstPosition, secondPosition, relationToAdd, combinedTuples);
        }
        Name = nameToMake;
        Scheme schemeToReplace = schemeMaker(lettersToScheme);
        scheme = schemeToReplace;
        tuples = combinedTuples;
    }  //6
    
    void uunion(Relation& firstRelationFinished, vector<string>& variableOrder, vector<int>& positions, Relation& tempRelation, Predicate& frontPred){
        vector<int> foundVariables;
        for (int j = 0; j < scheme.size(); j++) {
            for (int i = 0; i < firstRelationFinished.getSchemeSize(); i++) {
                if (scheme[j]==firstRelationFinished.scheme[i]) {
                    foundVariables.push_back(i);
                }
            }
        }  //spots and order of variables decided
        //start going through the tuples of the set to be combined.
        Tuple tuplesToAdd;
        std::set<Tuple>::const_iterator iter;
        for (iter = firstRelationFinished.tuples.begin(); iter!=firstRelationFinished.tuples.end(); iter++) {
            Tuple tempTuple = *iter;
            for (int i = 0; i < foundVariables.size(); i++) {
                tuplesToAdd.push_back(tempTuple[foundVariables[i]]);
            }
            tuples.insert(tuplesToAdd);
        }
    }
    
    /*void uunion(Relation& firstRelationFinished, vector<string>& variableOrder, vector<int>& positions, Relation& tempRelation, Predicate& frontPred){
        cout<<"vector<int> foundVariables;"<<endl;
        vector<int> foundVariables;
        cout<<"for (unsigned int i = 0; i < scheme.size(); i++) {"<<endl;
        for (unsigned int i = 0; i < scheme.size(); i++) {                              //for each item in the scheme
            cout<<"for (unsigned int g = 0; g < firstRelationFinished.getSchemeSize(); g++) {"<<endl;
            for (unsigned int g = 0; g < firstRelationFinished.getSchemeSize(); g++) {      //check it against each item in Relation
                cout<<"if (scheme[i]==firstRelationFinished.scheme[g]) {"<<endl;
                if (scheme[i]==firstRelationFinished.scheme[g]) {                               //matching
                    cout<<"foundVariables.push_back(g);"<<endl;
                    foundVariables.push_back(g);                                                //add spot int to vector
                }
            }
        }                                                                               //done
        cout<<"for (unsigned int g= 0; g< scheme.size(); g++) {//iter through the set"<<endl;
        for (unsigned int g= 0; g< scheme.size(); g++) {//iter through the set
            cout<<"std::set<Tuple>::const_iterator it;"<<endl;
            std::set<Tuple>::const_iterator it;
            cout<<"if (!tuples.count(*it)) {"<<endl;
            if (!tuples.count(*it)) {
                cout<<"Tuple tempTuple = *it;"<<endl;
                Tuple tempTuple = *it;
                cout<<"for (it=firstRelationFinished.tuples.begin(); it!=firstRelationFinished.tuples.end(); it++) {"<<endl;
                for (it=firstRelationFinished.tuples.begin(); it!=firstRelationFinished.tuples.end(); it++) {
                    cout<<" "<<scheme[g]<<"="<<tempTuple[foundVariables[g]]<<endl;
                }
                
            }
            else{
                cout<<"else{"<<endl;
                cout<<"tuples.insert(*it);"<<endl;
                tuples.insert(*it);
            }
        }
    }  //7*/
};