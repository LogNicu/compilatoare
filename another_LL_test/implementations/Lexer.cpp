//
// Created by nicu on 11/18/23.
//


#include "../flex/common_flex.h"
#include "../classes/Lexer.h"
#include "../classes/Token.h"
#include <regex>


//#######################################################################################################

Lexer::Lexer(std::istringstream stream) : l(&stream, &std::cout)
{
    pos = this->text.begin();
    //while (l.yylex());
}

Token Lexer::next() {
//    yyFlexLexer();
    l.yylex();
    return getToken();
    //while(l.yylex()) {
        //std::cout << std::string(l.YYText(), l.YYLeng()) << "\n";
        std::cout<<getToken()<<" secs\n";
    //}
    std::string::const_iterator end = text.end();
    if (pos == text.end()) {
        return {Token::M_EOF};
    }
    std::regex rex("([0-9]+(?:\\.[0-9]+)?)|(>=)|(<=)|(==)|(!=)|([*+-/()!><])");
    std::smatch match;
    if (std::regex_search(pos, end, match, rex, std::regex_constants::match_continuous)) {
        pos = match[0].second;
        if (match[1].matched) {
            return {Token::NUMBER, std::stod(match[0].str())};
        }
        if (match[2].matched) {
            return {Token::GT_EQ, 0, 0};
        }
        if (match[3].matched) {
            return  {Token::LT_EQ, 0, 0};
        }
        if (match[4].matched) {
            return  {Token::EQ_EQ, 0, 0};
        }
        if (match[5].matched) {
            return  {Token::BANG_EQ, 0, 0};
        }
        if (match[6].matched) {
            char symbol =  match[6].str().at(0);
            return {(Token::Type) symbol, 0, symbol};
        }

    }
    throw std::runtime_error("Error: Unknown token: ");
}

#undef stringify

