#pragma once
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
    
    int getTuplesSize(){
        return tuples.size();
    }  //1
    
    set<Tuple> getTuples(){
        return tuples;
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
                cout<<" "<<scheme[i]<<"='"<<tempTuple[i]<<"'";
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
    
    void rename(vector<int>& positions, vector<string>& variableOrder){
        //cout<<"rename"<<endl;
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
    
    
};