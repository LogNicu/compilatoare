
%{
#include "common.h"
 
%}
WHT [ \t\n\r]
COMMENT_LINE \/\/.*\n
COMMENT_BLOCK \/\*(.|{WHT})*\*\/
NUMBER -?[0-9]*\.?[0-9]*
STRING_LITERAL \"[^\"]*\"
CHAR_LITERAL \'.\'
%%
\; {yylval.op_val = new std::string(yytext);return SEMICOL;}
, {yylval.op_val = new std::string(yytext);return COMMA;}
\& {yylval.op_val = new std::string(yytext);return AND;}
\| {yylval.op_val = new std::string(yytext);return OR;}
\+ {yylval.op_val = new std::string(yytext);return PLUS;}
- {yylval.op_val = new std::string(yytext);return MINUS;}
\* {yylval.op_val = new std::string(yytext);return STAR;}
\/ {yylval.op_val = new std::string(yytext);return DIV;}
\{ {yylval.op_val = new std::string(yytext);return ACCOL_OPEN;}
\} {yylval.op_val = new std::string(yytext);return ACCOL_CLOSE;}
\( {yylval.op_val = new std::string(yytext);return RIGHT_PAREN;}
\) {yylval.op_val = new std::string(yytext);return LEFT_PAREN;}
=  {yylval.op_val = new std::string(yytext);return EQUAL;}
\+\+ {yylval.op_val = new std::string(yytext);return PLUS_PLUS;}
-- {yylval.op_val = new std::string(yytext);return MINUS_MINUS;}
== {yylval.op_val = new std::string(yytext);return EQUAL_EQUAL;}
> {yylval.op_val = new std::string(yytext);return GREATER;}
>= {yylval.op_val = new std::string(yytext);return GREATER_EQUAL;}
\< {yylval.op_val = new std::string(yytext);return LESS;}
\<= {yylval.op_val = new std::string(yytext);return LESS_EQUAL;}
{NUMBER} {yylval.num_val = atoi(yytext); return NUMBER;}
{STRING_LITERAL} {yylval.op_val = new std::string(yytext);return STRING_LITERAL;}
{CHAR_LITERAL} {yylval.op_val = new std::string(yytext);return CHAR_LITERAL;}
"return" {yylval.op_val = new std::string(yytext);return RETURN;}
"if"  {yylval.op_val = new std::string(yytext);return IF;}
"else" {yylval.op_val = new std::string(yytext);return ELSE;}
"do" {yylval.op_val = new std::string(yytext);return DO;}
"while" {yylval.op_val = new std::string(yytext);return WHILE;}
"for"  {yylval.op_val = new std::string(yytext);return FOR;}
"enum"  {yylval.op_val = new std::string(yytext);return FOR;}
"break" {yylval.op_val = new std::string(yytext);return BREAK;}
"#.*\n" printf("PREPROCESSOR: -> ignore: %s", yytext);
{WHT}|{COMMENT_LINE}|{COMMENT_BLOCK} {}
[a-zA-Z]* {yylval.op_val = new std::string(yytext);return IDENTIFIER;}
. printf("UNKNOWN: %s\n", yytext);
%%

int yywrap() {
    return 1;
}

