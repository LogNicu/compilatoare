%option noyywrap

%{
#include <stdio.h>
%}

COMMENT @.*
DIRECTIVE \..*
REG lr|ldr|sp|fp|r[0-9]{1,2}
NUMBER #-?[0-9]{1,2}
MEM \[{WHT}*{REG}{WHT}*,{WHT}*{NUMBER}{WHT}*\]!?
OP1 {REG}
OP2 {REG}|{MEM}|{NUMBER}
NAME [a-zA-Z][a-zA-Z_0-9]*
LABEL {NAME}:
INSTNAME [a-z]{2,3}
WHT [ \t\n\r]


OPS {OP1}{WHT}*(,{WHT}*{OP2}{WHT}*){0,2}
INST {INSTNAME}\t{OPS}
%%

\t{COMMENT}\n printf("\x1b[31mCOMMENT:\x1b[0m %s",yytext);
\t{DIRECTIVE}\n printf("\x1b[31mDIRECTIVE:\x1b[0m %s", yytext);
{LABEL}\n printf("\x1b[31mLABEL:\x1b[0m %s",yytext);
\t{INST}\n printf("\x1b[31mINSTRUCTION:\x1b[36m %s\x1b[0m",yytext);
.*\n printf("\x1b[31m???????????:\x1b[0m %s", yytext);
%%


int main(int argc, char **argv)
{
  yylex();
}

