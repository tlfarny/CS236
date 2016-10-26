#pragma once
#include <fstream>
#include <vector>
#include "Predicate.h"

using namespace std;

//Rules are a predicate with a list of predicates.

class Rule{
public:
    Rule(Predicate predicateIn): frontPredicate(predicateIn){}
    ~Rule(){}
    void toString(){
        frontPredicate.toString();
        cout<<" :- ";
        for (unsigned int i=0; i<backPredicates.size(); i++) {
            backPredicates[i].toString();
            if (i<backPredicates.size()-1) {
                cout<<",";
            }
        }
    }
    
    int getRuleListSize(){
        return backPredicates.size();
    }
    
    vector<Predicate> getBackPredicates(){
        return backPredicates;
    }
    
    Predicate getFrontPredicate(){
        return frontPredicate;
    }
    
    void ppushback(Predicate predicateIn){
        backPredicates.push_back(predicateIn);
    }
    
private:
    Predicate frontPredicate;
    vector<Predicate> backPredicates;
    
};