%option noyywrap

%{
#include <stdio.h>
%}

COMMENT @.*
DIRECTIVE \..*
NAME [a-zA-Z_][a-zA-Z_0-9]*
LABEL {NAME}:
INSTNAME [a-z]{2,3}
REG lr|sp|fp|rp[0-9]{1,2}
MEM \[{REG},[ \t]+#-?[0-9]+\]!?
OP1 {REG}
OP2 {REG}|{MEM}
OPS {OP1}(,[{OP2})?
INST {INSTNAME}[ \t]+{OPS}

%%

\t{COMMENT}\n printf("Cmt:%s",yytext);
\t{DIRECTIVE}\n printf("Drv:%s",yytext);
{LABEL}\n printf("Lbl:\t%s",yytext);
\t{INST}\n printf("Ins:%s",yytext);
.*\n printf("??? %s", yytext);

%%


int main(int argc, char **argv)
{
  yylex();
}

