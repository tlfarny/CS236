#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Token.h"

using namespace std;

class Tokenizer{
private:
    string input;
    vector<Token> Tokens;
public:
    Tokenizer(){}
    ~Tokenizer(){}
    
    void tokenMaker(string in1, vector<Token>& Tokens){
        ifstream in;
        char c;
        int lineNumber = 1;
        in.open(in1);
        while(in.get(c)){
            string content;
            bool create = true;
            int toAdd = 0;
            TokenType_t tokenKind = UNDEFINED;
            charChecker(c, tokenKind, content, lineNumber, Tokens, in, create, toAdd);
            if (create == true) {
                Tokens.push_back(Token(tokenKind, content, lineNumber));
                //Tokens[Tokens.size()-1].toString();                         //Should I put this in its own loop?
            }
            lineNumber+=toAdd;
        }
        Tokens.push_back(Token(ENDOFFILE, "", lineNumber));
        for (int i = 0; i < Tokens.size(); i++) {
            Tokens[i].toString();
        }
        cout<<"Total Tokens = "<<Tokens.size()<<endl;
        in.close();
    }
    
    void charChecker(char& c, TokenType_t& tokenKind, string& content, int& lineNumber, vector<Token>& Tokens, ifstream& in, bool& create, int& toAdd){
        content+=c;
        if (c == ':'){                                                      //Correct
            colonChecker(c, tokenKind, content, lineNumber, in);
        }
        else if (isalpha(c) || c=='\''){                                    //Correct
            stringChecker(c, tokenKind, content, lineNumber, in, toAdd);
        }
        else if (ispunct(c)){                                               //Correct
            punctuationChecker(c, tokenKind, content, lineNumber, create, in, toAdd);
        }
        else{                                                               //Checking
            processOthers(c, lineNumber, in, create, content, tokenKind);
        }
    }  //7
    
    void colonChecker(char& c, TokenType_t& tokenKind, string& content, int& lineNumber, ifstream& in){
        if (in.peek()=='-') {
            in.get(c);
            content += c;
            tokenKind = COLON_DASH;
        }
        else{
            tokenKind = COLON;
        }
    }  //3
    
    void stringChecker(char& c, TokenType_t& tokenKind, string& content, int& lineNumber, ifstream& in, int& toAdd){
        if (c=='\'') {                          //start string
            tokenKind = UNDEFINED;
            while (in.peek()!=EOF) {
                in.get(c);
                content+=c;
                if (c=='\n') {
                    toAdd++;
                }
                if (c=='\'') {
                    if (in.peek()=='\'') {
                        in.get(c);
                        content+=c;//continue repeating loop
                    }
                    else{                       //whole string ready
                        tokenKind = STRING;     //declared string
                        break;
                    }
                }
            }
        }                                       //should be done
        else{
            while (isalpha(in.peek()) || isdigit(in.peek())) {
                in.get(c);
                content+=c;
            }
            stringAssigner(tokenKind, content, lineNumber);
        }                                                //should be done
    }  //7
    
    void stringAssigner(TokenType_t& tokenKind, string& content, int& lineNumber){
        if (content=="Schemes") {  //this looks correct
            tokenKind = SCHEMES;
        }
        else if (content=="Facts"){
            tokenKind = FACTS;
        }
        else if (content=="Rules"){
            tokenKind = RULES;
        }
        else if (content=="Queries"){
            tokenKind = QUERIES;
        }
        else{
            tokenKind = ID;
        }
    }  //6
    
    void punctuationChecker(char& c, TokenType_t& tokenKind, string& content, int& lineNumber, bool& create, ifstream& in, int& toAdd){
        if (c == ',' || c == '.' || c == '?' || c == '(' || c == ')' || c=='#' || c=='+' || c=='*') {
            punctuationTokenMaker(c, tokenKind, content, lineNumber, create, in, toAdd);
        }
        else{
            tokenKind = UNDEFINED;                                          //needs fixing
        }
    }
    
    void punctuationTokenMaker(char& c, TokenType_t& tokenKind, string& content, int& lineNumber, bool& create, ifstream& in, int& toAdd){
        if (c==',') {
            tokenKind = COMMA;
        }
        else if (c=='.'){
            tokenKind = PERIOD;
        }
        else if (c=='?'){
            tokenKind = Q_MARK;
        }
        else if (c=='('){
            tokenKind = LEFT_PAREN;
        }
        else if (c==')'){
            tokenKind = RIGHT_PAREN;
        }
        else if (c=='#'){
            hashChecker(c, lineNumber, in, create, content, tokenKind, toAdd);
        }
        else if (c=='+'){
            tokenKind = ADD;
        }
        else if (c=='*'){
            tokenKind = MULTIPLY;
        }
    }  //6

    void hashChecker(char &c, int& lineNumber, ifstream& in, bool& create, string& content, TokenType_t& tokenKind, int& toAdd){
        tokenKind = UNDEFINED;
        if (in.peek()=='|') {  // block comment —————Not ending right.
            in.get(c);
            content+=c;
            while (in.peek()!=EOF) {
                in.get(c);
                content += c;
                if (c=='\n') {
                    toAdd++;
                }
                if (c=='|') {
                    if (in.peek()=='#') {
                        in.get(c);
                        content+=c;  //Block comment fully formed. tempWord ready to be tonkenized
                        tokenKind = COMMENT;
                        break;
                    }
                }
            }
        }
        else{
            while (in.peek()!='\n') {                               // single line comment
                in.get(c);                                  //figure out new line situation
                content += c;
            }
            tokenKind = COMMENT;
        }
    }
    
    void processOthers(char& c, int& lineNumber, ifstream& in, bool& create, string& content, TokenType_t& tokenKind){
        if (c=='\n') {
            lineNumber++;
            create = false;
        }
        else if (isspace(c)){
            create = false;
        }
    }  //6

};