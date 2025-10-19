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

#ifndef YY_ZASM_ZASM_PARSER_H_INCLUDED
# define YY_ZASM_ZASM_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int zasmdebug;
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
    ZASM_DATA_SECTION = 258,       /* ZASM_DATA_SECTION  */
    ZASM_CCODE_SECTION = 259,      /* ZASM_CCODE_SECTION  */
    ZASM_XCODE_SECTION = 260,      /* ZASM_XCODE_SECTION  */
    ZASM_INSTR = 261,              /* ZASM_INSTR  */
    ZASM_FLOAT_LITERAL = 262,      /* ZASM_FLOAT_LITERAL  */
    ZASM_IDENTIFIER = 263,         /* ZASM_IDENTIFIER  */
    ZASM_STRING_LITERAL = 264,     /* ZASM_STRING_LITERAL  */
    ZASM_INTEGER_LITERAL = 265,    /* ZASM_INTEGER_LITERAL  */
    ZASM_PRAGMA = 266,             /* ZASM_PRAGMA  */
    ZASM_LEXICAL_ERROR = 267       /* ZASM_LEXICAL_ERROR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 29 "zasm.y"

  int64_t  intval;
  double   floatval;
  char    *strval;
  wchar_t *wstrval;

  const struct instr_def_t *instr;
  struct zasm_tree_t *tree;
  box_set_t   list;
  box_t       box;

#line 88 "zasm_parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int zasmparse (yyscan_t yyscanner, zasm_driver_t *driver);


#endif /* !YY_ZASM_ZASM_PARSER_H_INCLUDED  */
