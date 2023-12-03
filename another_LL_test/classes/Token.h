//
// Created by nicu on 12/2/23.
//

#ifndef ANOTHER_LL_TEST_TOKEN_H
#define ANOTHER_LL_TEST_TOKEN_H


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
    Token(Type type, double  value = 0, char symbol = 0
            );

};

#endif //ANOTHER_LL_TEST_TOKEN_H