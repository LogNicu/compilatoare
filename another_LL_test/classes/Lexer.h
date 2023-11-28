//
// Created by nicu on 11/18/23.
//

#ifndef CPP_COMPILER_LEXER_H
#define CPP_COMPILER_LEXER_H

#include <unordered_map>
#include <string>


class Token {
public:
    enum Type
    {  PLUS = '+',
        MINUS = '-',
        SLASH = '/',
        STAR = '*',
        O_PAREN = '(',
        C_PAREN = ')',
        BANG = '!',
        GT = '>',
        LT = '<',
        // If i am to assign ascii values to some enum values, the other ones should be
        // outside the ASCII range if i want to have safe automatic value assignment
        GT_EQ = 128, // >=
        LT_EQ, // <=
        EQ_EQ, // ==
        BANG_EQ, // !=
        NUMBER,
        M_EOF
    };
private:
    static const std::unordered_map<Token::Type,std::string> toStr;
public:
    Type type;
    double value;
    char symbol;

    [[nodiscard]] std::string toString() const;
    [[nodiscard]] static std::string typeToStr(Type aType);
    [[nodiscard]] std::string typeToStr() const;
    friend std::ostream& operator<<(std::ostream& os, const Token& obj);
    Token(Type type, double  value, char symbol);

};


class Lexer{
    std::string text;
    std::string::const_iterator pos;
public:
    explicit Lexer(std::string &text);
    Token next();
    Token peek();
};


#endif //CPP_COMPILER_LEXER_H
