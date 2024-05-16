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

#ifndef YY_YY_NALAC_SRC_GEN_PARSER_TAB_H_INCLUDED
# define YY_YY_NALAC_SRC_GEN_PARSER_TAB_H_INCLUDED
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
    T_U8 = 258,                    /* T_U8  */
    T_U16 = 259,                   /* T_U16  */
    T_U32 = 260,                   /* T_U32  */
    T_U64 = 261,                   /* T_U64  */
    T_I8 = 262,                    /* T_I8  */
    T_I16 = 263,                   /* T_I16  */
    T_I32 = 264,                   /* T_I32  */
    T_I64 = 265,                   /* T_I64  */
    T_F32 = 266,                   /* T_F32  */
    T_F64 = 267,                   /* T_F64  */
    T_VOID = 268,                  /* T_VOID  */
    K_RET = 269,                   /* K_RET  */
    K_MAIN = 270,                  /* K_MAIN  */
    EOL = 271,                     /* EOL  */
    COMMA = 272,                   /* COMMA  */
    O_ASS = 273,                   /* O_ASS  */
    O_ADD = 274,                   /* O_ADD  */
    O_SUB = 275,                   /* O_SUB  */
    O_MUL = 276,                   /* O_MUL  */
    O_DIV = 277,                   /* O_DIV  */
    UNARY = 278,                   /* UNARY  */
    OPAREN = 279,                  /* OPAREN  */
    CPAREN = 280,                  /* CPAREN  */
    OBRACE = 281,                  /* OBRACE  */
    CBRACE = 282,                  /* CBRACE  */
    OBRACK = 283,                  /* OBRACK  */
    CBRACK = 284,                  /* CBRACK  */
    L_INT = 285,                   /* L_INT  */
    L_REL = 286,                   /* L_REL  */
    L_CHR = 287,                   /* L_CHR  */
    L_STR = 288,                   /* L_STR  */
    IDENTIFIER = 289               /* IDENTIFIER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
#line 38 "nalac/parser/parser.y"
union value
{
#line 38 "nalac/parser/parser.y"

    int         ival;
    double      rval;
    char        cval;
    char*       sval;

    prog_p      prog;
    decl_p      decl;
    decllist_p  decllist;
    stmt_p      stmt;
    stmtlist_p  stmtlist;
    expr_p      expr;
    exprlist_p  exprlist;
    type_p      type;
    typelist_p  typelist;
    param_p     param;
    paramlist_p paramlist;

#line 118 "nalac/src/gen/parser.tab.h"

};
#line 38 "nalac/parser/parser.y"
typedef union value YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_NALAC_SRC_GEN_PARSER_TAB_H_INCLUDED  */
