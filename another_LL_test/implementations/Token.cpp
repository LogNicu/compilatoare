//
// Created by nicu on 12/2/23.
//

#include "../classes/Token.h"
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

Token::Token(Type type, double  value, char symbol) : type(type), value(value), symbol(symbol) {}

