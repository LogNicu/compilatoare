/*
    Calculator:
    12.22 + (23.2 - 6) -> output the result

    TOKENS" '+' '-' '*' '/' '(' ')' NUMBER
    NUMBER [0-9]+("."[0-9]+)?
    EOF

*/
#include <string>
#include <regex>
#include <iostream>
class CToken {

public:
    enum {tkSymbol, tkNumber, tkEof} type;
    double value;
    char symbol;

    bool isEof() {return type == tkEof;}
    bool isSymbol(char aSymbol) {return type == tkSymbol && symbol == aSymbol;}
    bool isNumber(){return type == tkNumber;}
};



class CLexer {
    std::string text;
    std::string::const_iterator pos;
public:
    CLexer(std::string &atext) {
        text = atext; pos = text.begin();
    }

    CToken next() {
        CToken tok;
        std::string::const_iterator end = text.end();
        if(pos == text.end()) {
            tok.type = CToken::tkEof;
        }else{
            std::regex rex("([0-9]+(?:\\.[0-9]+)?)|([*+-/()])");
            // ?: something about group match ?
            std::smatch match;
            if(std::regex_search(pos, end, match, rex, std::regex_constants::match_continuous)) {
                pos = match[0].second;
                if(match[1].matched) {
                    tok.type = CToken::tkNumber;
                    tok.value = std::stod(match[0].str());
                }
                if(match[2].matched) {
                    tok.type = CToken::tkSymbol;
                    tok.symbol = match[2].str().at(0);
                }
                
            }else {
                //throw error here
            }
        }
        return tok;
    }

};


class CParser {
public:
    void parseExpr
}

int main(int argc, char **argv) {
    std::string line;

    while(std::getline(std::cin,line)) {
        try {
            CLexer l(line);
            CToken tok;
            do {
                tok = l.next();
                if(tok.isNumber()) {
                    std::cout<<tok.symbol<<std::endl;
                }else if (tok.type == CToken::tkSymbol){
                    std::cout<<tok.symbol<<std::endl;
                }
            }while(!tok.isEof());

            //std::cout<< p.parse() <<std::endl;
        }catch(std::exception &e) {

        }
    }
}