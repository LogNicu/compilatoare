%option noyywrap

%{
#include <stdio.h>
#include "enum_gen.h"

DEFINE_ENUM(
  TokenType, 
  SEMICOL, 
  COMMA, 
  INT, 
  ACCOL_OPEN, 
  ACCOL_CLOSE, 
  AND,
  OR,
  PLUS, 
  PLUS_PLUS,
  MINUS, 
  MINUS_MINUS,
  DIV, 
  STAR,
  EQUAL,
  EQUAL_EQUAL,
  LESS,
  LESS_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LEFT_PAREN, 
  RIGHT_PAREN, 
  NUMBER,
  STRING_LITERAL,
  CHAR_LITERAL,
  IDENTIFIER, 
  RETURN,
  DATA_TYPE,
  IF,
  ELSE,
  DO,
  WHILE,
  FOR,
  BREAK
)

typedef struct {
  TokenType tokType;
  char* lexemme;
} Token;
static Token arr[1000];
static int idx = 0;

void emitToken(TokenType tType, const char* yytext) {
  Token t;
  t.tokType = tType;
  t.lexemme = strdup(yytext);
  arr[idx++] = t;
}

%}
WHT [ \t\n\r]
COMMENT_LINE \/\/.*\n
COMMENT_BLOCK \/\*(.|{WHT})*\*\/
NUMBER -?[0-9]*\.?[0-9]*
STRING_LITERAL \"[^\"]*\"
CHAR_LITERAL \'.\'
%%
\; emitToken(SEMICOL, yytext);
, emitToken(COMMA,yytext);
\& emitToken(AND, yytext);
\| emitToken(OR, yytext);
\+ emitToken(PLUS,yytext);
- emitToken(MINUS,yytext);
\* emitToken(STAR,yytext);
\\ emitToken(DIV,yytext);
\{ emitToken(ACCOL_OPEN,yytext);
\} emitToken(ACCOL_CLOSE,yytext);
\( emitToken(LEFT_PAREN,yytext);
\) emitToken(RIGHT_PAREN,yytext);
= emitToken(EQUAL,yytext);
\+\+ emitToken(PLUS_PLUS,yytext);
-- emitToken(MINUS_MINUS,yytext);
== emitToken(EQUAL_EQUAL,yytext);
> emitToken(GREATER, yytext);
>= emitToken(GREATER_EQUAL,yytext);
\< emitToken(LESS, yytext);
\<= emitToken(LESS_EQUAL, yytext);
{NUMBER} emitToken(NUMBER,yytext);
{STRING_LITERAL} emitToken(STRING_LITERAL,yytext);
{CHAR_LITERAL} emitToken(CHAR_LITERAL,yytext);
"return" emitToken(RETURN,yytext);
"int" emitToken(INT,yytext);
"if", emitToken(IF,yytext);
"else", emitToken(ELSE,yytext);
"do", emitToken(DO,yytext);
"while", emitToken(WHILE,yytext);
"for"  emitToken(FOR, yytext);
"struct"  emitToken(FOR, yytext);
"enum"  emitToken(FOR, yytext);
"break" emitToken(BREAK, yytext);
"#.*\n" printf("PREPROCESSOR: -> ignore: %s", yytext);
{WHT}|{COMMENT_LINE}|{COMMENT_BLOCK} {}
[a-zA-Z]* emitToken(IDENTIFIER,yytext);
. printf("UNKNOWN: %s\n", yytext);
%%
/*
*/

int main(int argc, char **argv)
{
    while (yylex() != 0);

    // for(int i = 0; i < idx; i++) {
    //   printf("TOKEN: %s | type: %s\n",arr[i].lexemme, TokenTypeToStr(arr[i].tokType));
    // }
    int indentLevel = 0;
    for(int i = 0; i < idx; i++) {
      if(arr[i].tokType == ACCOL_CLOSE) {
        printf("\n");
        for(int i = 0; i < indentLevel-1;i++) {
            printf("    ");
        }
      }
      printf("%s\x1b[36m{\x1b[31m%s\x1b[36m}\x1b[0m ", TokenTypeToStr(arr[i].tokType), arr[i].lexemme);
      if(arr[i].tokType == ACCOL_OPEN || arr[i].tokType == ACCOL_CLOSE  ) {
        printf("\n");
        if(arr[i].tokType == ACCOL_OPEN) {
          indentLevel++;
          for(int i = 0; i < indentLevel;i++) {
            printf("    ");
          }
        }else if(arr[i].tokType == ACCOL_CLOSE) {
          indentLevel--;
          for(int i = 0; i < indentLevel;i++) {
            printf("    ");
          }
        }
      }
    }
    
}

