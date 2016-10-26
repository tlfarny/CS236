#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Token.h"
#include "DatalogProgram.h"
#include "Rule.h"
#include "Predicate.h"
#include "Parameter.h"

using namespace std;

class Parser{
    
public:
    Parser(): tempPredicate("none"), tempParameter("none", false, false), tempRule(tempPredicate){}
    ~Parser(){}
     
    void match(TokenType_t tokenIn, unsigned int& position, vector<Token>& Tokens){
        if (Tokens[position].getToken()==tokenIn) {
            position++;
        }
        else{
            throw 1;
        }
        
    }  //3
    
    void expressionParse(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog, string& expression){
        if (Tokens[position].getToken()==ID) {
            expression.append(Tokens[position].getInfo());
            position++;
        }
        else if (Tokens[position].getToken()==STRING){
            expression.append(Tokens[position].getInfo());
            position++;
        }
        else if (Tokens[position].getToken()==LEFT_PAREN){
            expression.append(Tokens[position].getInfo());
            match(LEFT_PAREN, position, Tokens);
            expressionParse(Tokens, position, datalog, expression);
            expression.append(Tokens[position].getInfo());
            if (Tokens[position].getToken()==ADD) {
                match(ADD, position, Tokens);
            }
            else{
                match(MULTIPLY, position, Tokens);
            }
            expressionParse(Tokens, position, datalog, expression);
            expression.append(Tokens[position].getInfo());
            match(RIGHT_PAREN, position, Tokens);
        }
        else{
            throw 1;
        }
    }
    
    /*void parameter(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        if (Tokens[position].getToken()==ID) {
            //assign as a variable
            tempParameter = Parameter(Tokens[position].getInfo(), false, true);
            tempPredicate.ppushback(tempParameter);
            position++;
        }
        else if (Tokens[position].getToken()==STRING){
            //assign as a value
            tempParameter = Parameter(Tokens[position].getInfo(), true, false);
            datalog.iinsert(Tokens[position].getInfo());
            tempPredicate.ppushback(tempParameter);
            position++;
        }
        else if (Tokens[position].getToken()==LEFT_PAREN){
            //create an expression
            string expression;
            expression.append(Tokens[position].getInfo());
            match(LEFT_PAREN, position, Tokens);
            expressionParse(Tokens, position, datalog, expression);
            expression.append(Tokens[position].getInfo());
            if (Tokens[position].getToken()==ADD) {
                match(ADD, position, Tokens);
            }
            else{
                match(MULTIPLY, position, Tokens);
            }
            expressionParse(Tokens, position, datalog, expression);
            expression.append(Tokens[position].getInfo());
            match(RIGHT_PAREN, position, Tokens);
            tempParameter = Parameter(expression, true, false);
            tempPredicate.ppushback(tempParameter);
        }
        else{
            throw 1;
        }
    }  //4
    
    void parameterList(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        parameter(Tokens, position, datalog);
        if (Tokens[position].getToken()==COMMA) {
            match(COMMA, position, Tokens);
            parameterList(Tokens, position, datalog);
        }
    }  //2
    
    void predicate(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        if (Tokens[position].getToken()!=ID) {
            throw 1;
        }
        tempPredicate = Predicate(Tokens[position].getInfo());
        position++;
        match(LEFT_PAREN, position, Tokens);
        parameterList(Tokens, position, datalog);
        match(RIGHT_PAREN, position, Tokens);
    }  //2
    
    void predicateList(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
     predicate(Tokens, position, datalog);
     if (Tokens[position].getToken()==COMMA) {
     match(COMMA, position, Tokens);
     predicateList(Tokens, position, datalog);
     }
     }  //2*/
    
    void parameterScheme(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        if (Tokens[position].getToken()==ID) {
            //assign as a variable
            tempParameter = Parameter(Tokens[position].getInfo(), false, true);
            tempPredicate.ppushback(tempParameter);
            position++;
        }
        else{
            throw 1;
        }
    }  //4
    
    void parameterListScheme(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        parameterScheme(Tokens, position, datalog);
        if (Tokens[position].getToken()==COMMA) {
            match(COMMA, position, Tokens);
            parameterListScheme(Tokens, position, datalog);
        }
    }  //2
    
    void predicateScheme(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        if (Tokens[position].getToken()!=ID) {
            throw 1;
        }
        tempPredicate = Predicate(Tokens[position].getInfo());
        position++;
        match(LEFT_PAREN, position, Tokens);
        parameterListScheme(Tokens, position, datalog);
        match(RIGHT_PAREN, position, Tokens);
    }  //2
    
    void parameterFact(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        if (Tokens[position].getToken()==STRING){
            //assign as a value
            tempParameter = Parameter(Tokens[position].getInfo(), true, false);
            datalog.iinsert(Tokens[position].getInfo());
            tempPredicate.ppushback(tempParameter);
            position++;
        }
        else{
            throw 1;
        }
    }  //4
    
    void parameterListFact(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        parameterFact(Tokens, position, datalog);
        if (Tokens[position].getToken()==COMMA) {
            match(COMMA, position, Tokens);
            parameterListFact(Tokens, position, datalog);
        }
    }  //2
    
    void predicateFact(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        if (Tokens[position].getToken()!=ID) {
            throw 1;
        }
        tempPredicate = Predicate(Tokens[position].getInfo());
        position++;
        match(LEFT_PAREN, position, Tokens);
        parameterListFact(Tokens, position, datalog);
        match(RIGHT_PAREN, position, Tokens);
    }  //2
    
    void parameterRule(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        if (Tokens[position].getToken()==ID) {
            //assign as a variable
            tempParameter = Parameter(Tokens[position].getInfo(), false, true);
            tempPredicate.ppushback(tempParameter);
            position++;
        }
        else if (Tokens[position].getToken()==STRING){
            //assign as a value
            tempParameter = Parameter(Tokens[position].getInfo(), true, false);
            tempPredicate.ppushback(tempParameter);
            position++;
        }
        else if (Tokens[position].getToken()==LEFT_PAREN){
            //create an expression
            string expression;
            expression.append(Tokens[position].getInfo());
            match(LEFT_PAREN, position, Tokens);
            expressionParse(Tokens, position, datalog, expression);
            expression.append(Tokens[position].getInfo());
            if (Tokens[position].getToken()==ADD) {
                match(ADD, position, Tokens);
            }
            else{
                match(MULTIPLY, position, Tokens);
            }
            expressionParse(Tokens, position, datalog, expression);
            expression.append(Tokens[position].getInfo());
            match(RIGHT_PAREN, position, Tokens);
            tempParameter = Parameter(expression, true, false);
            tempPredicate.ppushback(tempParameter);
        }
        else{
            throw 1;
        }
    }  //4
    
    void parameterListRule(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        parameterRule(Tokens, position, datalog);
        if (Tokens[position].getToken()==COMMA) {
            match(COMMA, position, Tokens);
            parameterListRule(Tokens, position, datalog);
        }
    }  //2
    
    void predicateRule(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        if (Tokens[position].getToken()!=ID) {
            throw 1;
        }
        tempPredicate = Predicate(Tokens[position].getInfo());
        position++;
        match(LEFT_PAREN, position, Tokens);
        parameterListRule(Tokens, position, datalog);
        match(RIGHT_PAREN, position, Tokens);
    }  //2
    
    void parameterQuery(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        if (Tokens[position].getToken()==ID) {
            //assign as a variable
            tempParameter = Parameter(Tokens[position].getInfo(), false, true);
            tempPredicate.ppushback(tempParameter);
            position++;
        }
        else if (Tokens[position].getToken()==STRING){
            //assign as a value
            tempParameter = Parameter(Tokens[position].getInfo(), true, false);
            tempPredicate.ppushback(tempParameter);
            position++;
        }
        else if (Tokens[position].getToken()==LEFT_PAREN){
            //create an expression
            string expression;
            expression.append(Tokens[position].getInfo());
            match(LEFT_PAREN, position, Tokens);
            expressionParse(Tokens, position, datalog, expression);
            expression.append(Tokens[position].getInfo());
            if (Tokens[position].getToken()==ADD) {
                match(ADD, position, Tokens);
            }
            else{
                match(MULTIPLY, position, Tokens);
            }
            expressionParse(Tokens, position, datalog, expression);
            expression.append(Tokens[position].getInfo());
            match(RIGHT_PAREN, position, Tokens);
            tempParameter = Parameter(expression, true, false);
            tempPredicate.ppushback(tempParameter);
        }
        else{
            throw 1;
        }
    }  //4
    
    void parameterListQuery(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        parameterQuery(Tokens, position, datalog);
        if (Tokens[position].getToken()==COMMA) {
            match(COMMA, position, Tokens);
            parameterListQuery(Tokens, position, datalog);
        }
    }  //2
    
    void predicateQuery(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        if (Tokens[position].getToken()!=ID) {
            throw 1;
        }
        tempPredicate = Predicate(Tokens[position].getInfo());
        position++;
        match(LEFT_PAREN, position, Tokens);
        parameterListQuery(Tokens, position, datalog);
        match(RIGHT_PAREN, position, Tokens);
    }  //2
    
    void query(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        predicateQuery(Tokens, position, datalog);
        match(Q_MARK, position, Tokens);
        datalog.ppushbackPQueries(tempPredicate);
    }  //1
    
    void queryList(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        if (Tokens[position].getToken()!=ENDOFFILE) {
            query(Tokens, position, datalog);
            queryList(Tokens, position, datalog);
        }
    }  //2
    
    void predicateListRules(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        predicateRule(Tokens, position, datalog);
        tempRule.ppushback(tempPredicate);
        if (Tokens[position].getToken()==COMMA) {
            match(COMMA, position, Tokens);
            predicateListRules(Tokens, position, datalog);
        }
    }  //2
    
    void rule(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        predicateScheme(Tokens, position, datalog);
        tempRule = Rule(tempPredicate);
        match(COLON_DASH, position, Tokens);
        predicateListRules(Tokens, position, datalog);
        match(PERIOD, position, Tokens);
        datalog.ppushbackRules(tempRule);
        
    }  //1
    
    void ruleList(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        if (Tokens[position].getToken()!=QUERIES) {
            rule(Tokens, position, datalog);
            ruleList(Tokens, position, datalog);
        }
    }  //2
    
    void fact(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        predicateFact(Tokens, position, datalog);
        match(PERIOD, position, Tokens);
        datalog.ppushbackFacts(tempPredicate);
    }  //1
    
    void factList(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        if (Tokens[position].getToken()==ID) {
            fact(Tokens, position, datalog);
            factList(Tokens, position, datalog);
        }
    }  //2
    
    void scheme(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        predicateScheme(Tokens, position, datalog);
        datalog.ppushbackScheme(tempPredicate);
    }  //1
    
    void schemeList(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        if (Tokens[position].getToken()!=FACTS) {
            scheme(Tokens, position, datalog);
            if (Tokens[position].getToken()!=FACTS) {
                schemeList(Tokens, position, datalog);
            }
        }
    }  //2
    
    void schemeListStart(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        if (Tokens[position].getToken()==FACTS) {
            throw 1;
        }
        else{
            schemeList(Tokens, position, datalog);
        }
    }
    
    void parser(vector<Token>& Tokens, unsigned int& position, DatalogProgram& datalog){
        match(SCHEMES, position, Tokens);
        match(COLON, position, Tokens);
        schemeListStart(Tokens, position, datalog);
        match(FACTS, position, Tokens);
        match(COLON, position, Tokens);
        factList(Tokens, position, datalog);
        match(RULES, position, Tokens);
        match(COLON, position, Tokens);
        ruleList(Tokens, position, datalog);
        match(QUERIES, position, Tokens);
        match(COLON, position, Tokens);
        queryList(Tokens, position, datalog);
        if (Tokens[position].getToken()!=ENDOFFILE) {
            throw 1;
        }
    }  //1
    
private:
    Predicate tempPredicate;
    Parameter tempParameter;
    Rule tempRule;
};