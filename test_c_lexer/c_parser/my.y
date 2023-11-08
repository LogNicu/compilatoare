%{
    #include "common.h"
int yyerror(string s);
int yyerror(char *s);
int yylex(void);
%}

%union{
    double num_val;
    std::string* op_val;
}

%start input
%token <num_val> NUMBER
%token <op_val> STRING_LITERAL
%type <num_val> exp
%type <num_val> literal

////////////
%token  SEMICOL
%token  COMMA
%token  INT
%token  ACCOL_OPEN 
%token  ACCOL_CLOSE 
%left  AND
%left  OR
%left  PLUS 
%left  PLUS_PLUS
%left  MINUS
%left  MINUS_MINUS
%left  DIV
%left  STAR
%left  EQUAL
%left  EQUAL_EQUAL
%left  LESS
%left  LESS_EQUAL
%left  GREATER
%left  GREATER_EQUAL
%token  LEFT_PAREN
%token  RIGHT_PAREN 
%token  CHAR_LITERAL
%token  IDENTIFIER
%token  RETURN
%token  DATA_TYPE
%token  IF
%token  ELSE
%token  DO
%token  WHILE
%token  FOR
%token  BREAK

////////////

%%

input: /* empty */
    | statement_list
    ;

statement_list: /* empty */
| statement_list statement
              ;
statement: exp SEMICOL  {std::cout<<"Result: "<<$1<< endl;} |
    vardecl SEMICOL
    | fundecl



fundecl: IDENTIFIER IDENTIFIER RIGHT_PAREN param_list LEFT_PAREN ACCOL_OPEN statement_list ACCOL_CLOSE {std::cout<<"fundecl: "<< endl;}

param_list: /*empty */ 
	| vardecl
	| vardecl COMMA param_list

vardecl: IDENTIFIER IDENTIFIER 

exp: literal | unary | binary | grouping;

literal: NUMBER {$$ = $1; } | STRING_LITERAL {$$ = 0; }
grouping : RIGHT_PAREN exp LEFT_PAREN
unary: MINUS exp
binary: exp operator exp
operator: EQUAL_EQUAL | LESS | LESS_EQUAL | GREATER | GREATER_EQUAL
	| PLUS | MINUS | STAR | DIV
	;
%%

int yyerror(string s)
{
  extern int yylineno;  // defined and maintained in lex.c
  extern char *yytext;  // defined and maintained in lex.c
  
  cerr << "ERROR: " << s << " at symbol \"" << yytext;
  cerr << "\" on line " << yylineno << endl;
  exit(1);
}

int yyerror(char *s)
{
  return yyerror(string(s));
}

int main() {
    yyparse();
    return 0;
}

/*
exp: NUMBER {$$ = $1; } 
    | exp PLUS exp { $$ = $1 + $3;}
    | exp STAR exp {  $$ = $1 * $3; }
    | exp DIV exp {  $$ = $1 / $3; }
    | exp MINUS exp {  $$ = $1 - $3; }
    | exp EQUAL_EQUAL exp {$$ = $1 == $3;}
    | exp LESS_EQUAL exp {$$ = $1 <= $3;}
    | exp GREATER_EQUAL exp {$$ = $1 >= $3;}
    | exp LESS exp {$$ = $1 < $3;}
    | exp GREATER exp {$$ = $1 > $3;}
   
    ;
*/
