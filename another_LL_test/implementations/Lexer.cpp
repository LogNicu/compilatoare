//
// Created by nicu on 11/18/23.
//

#include "../classes/Lexer.h"
#include <regex>
#define stringify(x) #x
const std::unordered_map<Token::Type,std::string> Token::toStr = {
        {Token::PLUS,     stringify(PLUS)},
        {Token::MINUS ,   stringify(MINUS)},
        {Token::SLASH ,   stringify(SLASH)},
        {Token::STAR ,    stringify(STAR)},
        {Token::O_PAREN , stringify(O_PAREN)},
        {Token::C_PAREN , stringify(C_PAREN)},
        {Token::BANG,     stringify(BANG)},
        {Token::GT,       stringify(GT)},
        {Token::LT,       stringify(LT)},
        {Token::GT_EQ,       stringify(GT_EQ)},
        {Token::LT_EQ,       stringify(LT_EQ)},
        {Token::EQ_EQ,       stringify(EQ_EQ)},
        {Token::BANG_EQ,       stringify(BANG_EQ)},
        {Token::NUMBER,   stringify(NUMBER)},
        {Token::M_EOF,    stringify(M_EOF)}
};

[[nodiscard]] std::string Token::toString() const {
    const Token &t = *this;
    return  std::string("{")+"\033[91m"+toStr.at(t.type)+"\033[0m, "+
    std::to_string(t.value)+(t.type != NUMBER && t.type != M_EOF ? std::string(", '")+t.symbol+"'}": "}");
}
[[nodiscard]] std::string Token::typeToStr() const {
    return  toStr.at(this->type);
}
[[nodiscard]] std::string Token::typeToStr(Token::Type aType) {
    return  toStr.at(aType);
}

std::ostream& operator<<(std::ostream& os, const Token& obj) {
    os << obj.toString();
    return os;
}

Token::Token(Type type, double  value = 0, char symbol = 0) : type(type), value(value), symbol(symbol) {}


//#######################################################################################################

Lexer::Lexer(std::string &text) : text(std::move(text)){
    pos = this->text.begin();
}

Token Lexer::next() {

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

