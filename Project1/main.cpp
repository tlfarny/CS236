#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Token.h"

using namespace std;

void punctuationTokenMaker(char& c, TokenType_t& tokenKind, string& content, int& lineNumber, ofstream& out, bool& broken, bool& create){
    content+=c;
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
}  //6

void colonChecker(char& c, TokenType_t& tokenKind, string& content, int& lineNumber, ifstream& in){
    content+=c;
    if (in.peek()=='-') {
        in.get(c);
        content += c;
        tokenKind = COLON_DASH;
    }
    else{
        tokenKind = COLON;
    }
}  //3

void stringAssigner(char& c, TokenType_t& tokenKind, string& content, int& lineNumber){
    if (content=="Schemes") {
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

void stringChecker(char& c, TokenType_t& tokenKind, string& content, int& lineNumber, ifstream& in, ofstream& out, bool& broken){
    if (c=='\'') {
        in.get(c);
        while (c!='\'') {
            content+=c;
            in.get(c);
            if (c=='\n') {
                
                out<<"Input Error on line "<<lineNumber<<endl;
                broken = true;
                break;
            }
        }
        tokenKind = STRING;
    }
    else{
        content+=c;
        while (isalpha(in.peek()) || isdigit(in.peek())) {
            in.get(c);
            content+=c;
        }
        stringAssigner(c, tokenKind, content, lineNumber);
    }
}  //7

void hashChecker(char &c, int& lineNumber, ifstream& in, ofstream& out, bool& broken, bool& create){
    string tempWord;
    tempWord += c;
    if (in.peek()=='|') {  // block comment
        in.get(c);
        while (c) {
            if (c=='|') {
                if (in.peek()=='#') {
                    tempWord+=c;
                    in.get(c);
                    tempWord+=c;  //Block comment fully formed. tempWord ready to be tonkenized
                    break;
                }
            }
        }
    }
    else{
        while (c!='\n') {  // single line comment
            in.get(c);
            tempWord += c;
        }
    }
    lineNumber++;
    create = false;
}

void processOthers(char& c, int& lineNumber, ifstream& in, ofstream& out, bool& broken, bool& create){
    if (c=='\n') {
        lineNumber++;
        create = false;
    }
    else if (c=='#') {
        hashChecker(c, lineNumber, in, out, broken, create);
    }
    else if (isspace(c)){
        create = false;
    }
    else{
        out<<"Input Error on line "<<lineNumber<<endl;
        broken = true;
    }
}  //6

void punctuationChecker(char& c, TokenType_t& tokenKind, string& content, int& lineNumber, ofstream& out, bool& broken, bool& create){
    if (c == ',' || c == '.' || c == '?' || c == '(' || c == ')') {
        punctuationTokenMaker(c, tokenKind, content, lineNumber, out, broken, create);
    }
    else{
        out<<"Input Error on line "<<lineNumber<<endl;
        broken = true;
        create = false;
    }
} //7

void charChecker(char& c, TokenType_t& tokenKind, string& content, int& lineNumber, vector<Token>& Tokens, ifstream& in, ofstream& out, bool& broken, bool& create){
    if (c == ':'){
        colonChecker(c, tokenKind, content, lineNumber, in);
    }
    else if (isalpha(c) || c=='\''){
        stringChecker(c, tokenKind, content, lineNumber, in, out, broken);
    }
    else if (ispunct(c) && c!='#'){
        punctuationChecker(c, tokenKind, content, lineNumber, out, broken, create);
    }
    else{
        processOthers(c, lineNumber, in, out, broken, create);
    }
}  //7

void tokenMaker(string in1, string in2){
    ifstream in;
    ofstream out;
    char c;
    bool broken = false;
    vector<Token> Tokens;
    TokenType_t tokenKind = STRING;
    int lineNumber = 1;
    in.open(in1);
    out.open(in2);
    while(in.get(c) && broken==false){
        string content;
        bool create = true;
        charChecker(c, tokenKind, content, lineNumber, Tokens, in, out, broken, create);
        if (broken==false && create==true) {
            Tokens.push_back(Token(tokenKind, content, lineNumber));
            Tokens[Tokens.size()-1].toString(out);
        }
    }
    if (broken==false) {
        out<<"Total Tokens = "<<Tokens.size()<<endl;
    }
    in.close();
    out.close();
}  //6

int main(int argc, const char * argv[]){
    tokenMaker(argv[1], argv[2]);
    return 0;
}  //1

