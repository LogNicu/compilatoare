//
// Created by nicu on 12/2/23.
//

#include <utility>

#include "../classes/Token.h"
#define stringify(x) #x
const std::unordered_map<Token::Type,std::string> Token::toStr = {
        {PLUS,     stringify(PLUS)},
        {MINUS ,   stringify(MINUS)},
        {SLASH ,   stringify(SLASH)},
        {STAR ,    stringify(STAR)},
        {O_PAREN , stringify(O_PAREN)},
        {C_PAREN , stringify(C_PAREN)},
        {BANG,     stringify(BANG)},
        {GT,       stringify(GT)},
        {LT,       stringify(LT)},
        {AND, stringify(AND)},
        {OR, stringify(OR)},
        {XOR, stringify(XOR)},
        {COLON, stringify(COLON)},
        {SEMICOL, stringify(SEMICOL)},
        {EQUAL, stringify(EQUAL)},
        {COMMA, stringify(COMMA)},
        {O_ACCOL, stringify(O_ACCOL)},
        {C_ACCOL, stringify(C_ACCOL)},
        {UNARY_NEG, stringify(UNARY_NEG)},
        {GT_EQ,       stringify(GT_EQ)},
        {LT_EQ,       stringify(LT_EQ)},
        {EQ_EQ,       stringify(EQ_EQ)},
        {BANG_EQ,       stringify(BANG_EQ)},
        {LOGIC_AND, stringify(LOGIC_AND)},
        {LOGIC_OR, stringify(LOGIC_OR)},
        {L_SHIFT, stringify(L_SHIFT)},
        {R_SHIFT, stringify(R_SHIFT)},
        {ARROW, stringify(ARROW)},
        {FN, stringify(FN)},
        {DATA_TYPE, stringify(DATA_TYPE)},
        {NUMBER,   stringify(NUMBER)},
        {IDENTIFIER, stringify(IDENTIFIER)},
        {RETURN, stringify(RETURN)},
        {LET, stringify(LET)},
        {ERROR_TOK, stringify(ERROR_TOK)},
        {M_EOF,    stringify(M_EOF)}
};

[[nodiscard]] std::string Token::toString() const {
    const Token &t = *this;
    return  std::string("{")+"\033[91m"+toStr.at(t.type)+"\033[0m, "+
            std::to_string(t.value)+(t.type != NUMBER && t.type != M_EOF ? std::string(", '")+t.lexemme+"'}": "}");
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

Token::Token(Type type, double  value, std::string alexemme,unsigned long long lineNumber) : type(type), value(value), lexemme(alexemme), lineNumber(lineNumber) {}

