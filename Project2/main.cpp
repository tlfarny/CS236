#include <iostream>
#include <set>
#include <vector>
#include <string>
#include "Token.h"
#include "Tokenizer.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Rule.h"
#include "Predicate.h"
#include "Parameter.h"

using namespace std;

int main(int argc, const char * argv[]) {
    vector<Token> Tokens;
    Tokenizer tokenizer;
    DatalogProgram datalog;
    Parser pparser;
    set<Parameter> domain;
    bool flagged = false;
    unsigned int position = 0;
    tokenizer.tokenMaker(argv[1], Tokens);
    try {
        pparser.parser(Tokens, position, datalog);
    } catch (int e) {
        cout<<"Failure!"<<endl<<"  ";
        Tokens[position].toString();
        flagged = true;
    }
    if (flagged==false) {
        cout<<"Success!"<<endl;
        datalog.toString();
    }
    return 0;
}
