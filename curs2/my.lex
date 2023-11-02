%option noyywrap

%{
#include <stdio.h>
%}

COMMENT @.*
DIRECTIVE \..*
REG lr|sp|fp|r[0-9]{1,2}
MEM \[.*\]!?
OP1 {REG}
OP2 {REG}|{MEM}
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
\t{INST}\n printf("\x1b[31mINSTRUCTION:\x1b[0m %s",yytext);
.*\n printf("\x1b[31m???????????:\x1b[0m %s", yytext);
%%

//OPS {OP1}\s*(,\s*{OP2}\s*){0,2}
//OPS {OP1},{WHT}{OP2}
int main(int argc, char **argv)
{
  yylex();
}

