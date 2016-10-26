#pragma once
#include <string>
#include <iostream>

using namespace std;

enum TokenType_t {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, ENDOFFILE};

class Token{
public:
    Token(TokenType_t tokenin, string Contentin, int LineNumberin) : type(tokenin), info(Contentin), lineNumber(LineNumberin){};
    ~Token(void){};
    void stringFirst(string& output){
        if (type==COMMA) {
            output = "COMMA";
        }
        else if (type==PERIOD){
            output = "PERIOD";
        }
        else if (type==Q_MARK){
            output = "Q_MARK";
        }
        else if (type==LEFT_PAREN){
            output = "LEFT_PAREN";
        }
        else if (type==RIGHT_PAREN){
            output = "RIGHT_PAREN";
        }
        else if (type ==COLON){
            output = "COLON";
        }
        else if (type==COLON_DASH){
            output = "COLON_DASH";
        }
    }  //8
    void stringSecond(string& output){
        if (type==SCHEMES) {
            output = "SCHEMES";
        }
        else if (type==FACTS){
            output = "FACTS";
        }
        else if (type==QUERIES){
            output = "QUERIES";
        }
        else if (type==RULES){
            output = "RULES";
        }
        else if (type==ID){
            output= "ID";
        }
        else if (type ==STRING){
            output = "STRING";
        }
    }  //7
    
    void stringThird(string& output){
        if (type==MULTIPLY) {
            output = "MULTIPLY";
        }
        else if (type==ADD){
            output = "ADD";
        }
        else if (type==UNDEFINED){
            output = "UNDEFINED";
        }
        else if (type==COMMENT){
            output = "COMMENT";
        }
        else if (type ==ENDOFFILE){
            output = "EOF";
        }
    }
    
    void toString(){
        string output;
        stringFirst(output);
        stringSecond(output);
        stringThird(output);
        cout<<"("<<output<<",\""<<info<<"\","<<lineNumber<<")"<<endl;
    }  //1
    
    TokenType_t getToken(){
        return type;
    }
    
    string getInfo(){
        return info;
    }
    
private:
    TokenType_t type;
    string info;
    int lineNumber;
};

