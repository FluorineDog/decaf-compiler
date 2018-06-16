/* A Bison parser, made by GNU Bison 3.0.5.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_PARSER_HXX_INCLUDED
# define YY_YY_PARSER_HXX_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 9 "parser.yxx" /* yacc.c:1910  */

  #include "external.h"

#line 48 "parser.hxx" /* yacc.c:1910  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    END_OF_FILE = 0,
    NUM_double = 258,
    NUM_int = 259,
    ID = 260,
    TYPE_ID = 261,
    T_or = 262,
    T_and = 263,
    T_less_eq = 264,
    T_greater_eq = 265,
    T_eq = 266,
    T_not_eq = 267,
    NEG = 268,
    T_void = 269,
    T_string = 270,
    T_bool = 271,
    T_int = 272,
    T_double = 273,
    T_null = 274,
    T_true = 275,
    T_false = 276,
    T_class = 277,
    T_extends = 278,
    T_interface = 279,
    T_implements = 280,
    T_this = 281,
    T_while = 282,
    T_if = 283,
    T_else = 284,
    T_for = 285,
    T_return = 286,
    T_break = 287,
    T_Print = 288,
    T_ReadInteger = 289,
    T_ReadLine = 290,
    T_NewArray = 291,
    T_New = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 18 "parser.yxx" /* yacc.c:1910  */

  node_ptr_t unode_ptr_t;
  Integer          *uInteger;
  Double           *uDouble;
  NullPointer      *uNullPointer;
  Call             *uCall;
  Index            *uIndex;
  MemberDot        *uMemberDot;
  NewArray         *uNewArray;
  New              *uNew;
  Read             *uRead;
  UnaryExpr        *uUnaryExpr;
  BinaryExpr       *uBinaryExpr;
  This             *uThis;
  Print            *uPrint;
  List             *uList;
  Break            *uBreak;
  Return           *uReturn;
  For              *uFor;
  While            *uWhile;
  Block            *uBlock;
  If               *uIf;
  Prototype        *uPrototype;
  Interface        *uInterface;
  ClassDecl        *uClassDecl;
  FunctionDecl     *uFunctionDecl;
  TypeArray        *uTypeArray;
  TypeBase         *uTypeBase;
  TypeUser         *uTypeUser;
  Identifier       *uIdentifier;
  Assign           *uAssign;
  TypedVariable    *uTypedVariable;
  Program          *uProgram;
  NoAction         *uNoAction;
  int intval;

#line 136 "parser.hxx" /* yacc.c:1910  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HXX_INCLUDED  */
