#include <iostream>
#include <vector>
#include <string>
#include "Token.h"
#include "Tokenizer.h"

using namespace std;

int main(int argc, const char * argv[]) {
    vector<Token> Tokens;
    Tokenizer tokenizer;
    tokenizer.tokenMaker(argv[1], Tokens);
    return 0;
}
