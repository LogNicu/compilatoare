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
%token SEMICOLON
%type <num_val> exp
%left PLUS
%left MINUS
%left MULT
%left DIV

%%

input: /* empty */
    | statement_list
    ;

statement_list: /* empty */
| statement_list statement
              ;
statement: exp SEMICOLON   {std::cout<<"Result: "<<$1<< endl;}


exp: NUMBER {$$ = $1; }
    | exp PLUS exp { $$ = $1 + $3;}
    | exp MULT exp {  $$ = $1 * $3; }
    | exp DIV exp {  $$ = $1 / $3; }
    | exp MINUS exp {  $$ = $1 - $3; }
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
