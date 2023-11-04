%option noyywrap

%{
#include <stdio.h>

typedef enum {
  SEMICOL,
  COMMA,
  INT,
  ACCOL_OPEN,
  ACCOL_CLOSE,
  /////////
  PLUS,
  MINUS,
  DIV,
  STAR,
  //////
  LEFT_PAREN,
  RIGHT_PAREN,
  /////
  NUMBER,
  /////
  IDENTIFIER,
  RETURN
} TokenType;


const char* tokenTypeToStr(TokenType type) {
  static const char* tokTypeArr[] ={  "SEMICOL","COMMA","INT","ACCOL_OPEN","ACCOL_CLOSE","PLUS","MINUS","DIV","STAR","LEFT_PAREN","RIGHT_PAREN","NUMBER","IDENTIFIER","RETURN"};
  return tokTypeArr[type];
}
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

COMMENT @.*
NUMBER -?[0-9]*\.?[0-9]*
WHT [ \t\n\r]
%%
\; emitToken(SEMICOL, yytext);
, emitToken(COMMA,yytext);
\+ emitToken(PLUS,yytext);
- emitToken(MINUS,yytext);
\* emitToken(STAR,yytext);
\\ emitToken(DIV,yytext);
\{ emitToken(ACCOL_OPEN,yytext);
\} emitToken(ACCOL_CLOSE,yytext);
\( emitToken(LEFT_PAREN,yytext);
\) emitToken(RIGHT_PAREN,yytext);
{NUMBER} emitToken(NUMBER,yytext);
"return" emitToken(RETURN,yytext);
"int" emitToken(INT,yytext);
{WHT} {}
[a-zA-Z]* emitToken(IDENTIFIER,yytext);
. printf("UNKNOWN: %s\n", yytext);
%%


int main(int argc, char **argv)
{
    while (yylex() != 0);
    printf("MAX IDX: %d\n",idx);
    // for(int i = 0; i < idx; i++) {
    //   printf("TOKEN: %s | type: %s\n",arr[i].lexemme, tokenTypeToStr(arr[i].tokType));
    // }
    for(int i = 0; i < idx; i++) {
      printf("%s{%s} ", tokenTypeToStr(arr[i].tokType), arr[i].lexemme);
      if(arr[i].tokType == ACCOL_OPEN || arr[i].tokType == ACCOL_CLOSE || arr[i].tokType == SEMICOL ) {
        printf("\n");
      }
    }
}

