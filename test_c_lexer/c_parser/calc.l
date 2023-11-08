%{
#include "common.h"
%}

NUMBER [0-9]+

%%

{NUMBER} {yylval.num_val = atoi(yytext); return NUMBER;}
\+ { yylval.op_val = new std::string(yytext); return PLUS; }
\* { yylval.op_val = new std::string(yytext); return MULT; }
\/ { yylval.op_val = new std::string(yytext); return DIV; }
- { yylval.op_val = new std::string(yytext); return MINUS; }
; {yylval.op_val = new std::string(yytext); return SEMICOLON;}




%%

int yywrap() {
    return 1;
}

