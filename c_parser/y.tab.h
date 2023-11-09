/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUMBER = 258,                  /* NUMBER  */
    STRING_LITERAL = 259,          /* STRING_LITERAL  */
    SEMICOL = 260,                 /* SEMICOL  */
    COMMA = 261,                   /* COMMA  */
    INT = 262,                     /* INT  */
    ACCOL_OPEN = 263,              /* ACCOL_OPEN  */
    ACCOL_CLOSE = 264,             /* ACCOL_CLOSE  */
    AND = 265,                     /* AND  */
    OR = 266,                      /* OR  */
    PLUS = 267,                    /* PLUS  */
    PLUS_PLUS = 268,               /* PLUS_PLUS  */
    MINUS = 269,                   /* MINUS  */
    MINUS_MINUS = 270,             /* MINUS_MINUS  */
    DIV = 271,                     /* DIV  */
    STAR = 272,                    /* STAR  */
    EQUAL = 273,                   /* EQUAL  */
    EQUAL_EQUAL = 274,             /* EQUAL_EQUAL  */
    LESS = 275,                    /* LESS  */
    LESS_EQUAL = 276,              /* LESS_EQUAL  */
    GREATER = 277,                 /* GREATER  */
    GREATER_EQUAL = 278,           /* GREATER_EQUAL  */
    LEFT_PAREN = 279,              /* LEFT_PAREN  */
    RIGHT_PAREN = 280,             /* RIGHT_PAREN  */
    CHAR_LITERAL = 281,            /* CHAR_LITERAL  */
    IDENTIFIER = 282,              /* IDENTIFIER  */
    RETURN = 283,                  /* RETURN  */
    DATA_TYPE = 284,               /* DATA_TYPE  */
    IF = 285,                      /* IF  */
    ELSE = 286,                    /* ELSE  */
    DO = 287,                      /* DO  */
    WHILE = 288,                   /* WHILE  */
    FOR = 289,                     /* FOR  */
    BREAK = 290                    /* BREAK  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define NUMBER 258
#define STRING_LITERAL 259
#define SEMICOL 260
#define COMMA 261
#define INT 262
#define ACCOL_OPEN 263
#define ACCOL_CLOSE 264
#define AND 265
#define OR 266
#define PLUS 267
#define PLUS_PLUS 268
#define MINUS 269
#define MINUS_MINUS 270
#define DIV 271
#define STAR 272
#define EQUAL 273
#define EQUAL_EQUAL 274
#define LESS 275
#define LESS_EQUAL 276
#define GREATER 277
#define GREATER_EQUAL 278
#define LEFT_PAREN 279
#define RIGHT_PAREN 280
#define CHAR_LITERAL 281
#define IDENTIFIER 282
#define RETURN 283
#define DATA_TYPE 284
#define IF 285
#define ELSE 286
#define DO 287
#define WHILE 288
#define FOR 289
#define BREAK 290

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 8 "my.y"

    double num_val;
    std::string* op_val;

#line 142 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
