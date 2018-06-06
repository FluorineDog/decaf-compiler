/* scanner for a toy Pascal-like language */

%{
/* need this for the call to atof() below */
#include <math.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
yyFlexLexer lexer;
#include "parser.hxx"
int yylex (void);
void yyerror (char const *);
// /*
// enum yytokentype{
//   T_ID = 0, 
//   T_integer = 1, 
//   T_real = 2, 
//   END_OF_FILE = 3, 
// };

// */
int yyval_int;
double yyval_real;
%}

%option noyywrap c++
DIGIT    [0-9]
ID       [A-Za-z_][A-Za-z0-9_]*
%x       C_COMMENT
%%
{DIGIT}+    {
                    yyval_real = atoi(yytext) ;
                    return T_int;
            }

[(-|+)]{DIGIT}+"."{DIGIT}*[(e|E)(-|+){DIGIT}+]        {
                    yyval_real = atof(yytext) ;
                    return T_real;
            }

"void"          { return T_void; }
"string"        { return T_string; }
"bool"          { return T_bool; }
"int"           { return T_int; }
"double"        { return T_double; }
"null"          { return T_null; }
"true"          { return T_true; }
"false"         { return T_false; }
"class"         { return T_class; }
"extends"       { return T_extends; }
"interface"     { return T_interface; }
"implements"    { return T_implements; }
"this"          { return T_this; }
"while"         { return T_while; }
"if"            { return T_if; }
"else"          { return T_else; }
"for"           { return T_for; }
"return"        { return T_return; }
"break"         { return T_break; }
"Print"         { return T_Print; }
"ReadInteger"   { return T_ReadInteger; }
"ReadLine"      { return T_ReadLine; }
"NewArray"      { return T_NewArray; }
"New"           { return T_New; }
"+"             { return T_add; }
"-"             { return T_minus; }
"*"             { return T_mul; }
"/"             { return T_div; }
"%"             { return T_mod; }
"<"             { return T_less; }
"<="            { return T_less_eq; }
">"             { return T_greater; }
">="            { return T_greater_eq; }
"="             { return T_assign; }
"=="            { return T_eq; }
"!="            { return T_not_eq; }
"&&"            { return T_and; }
"||"            { return T_or; }
"!"             { return T_not; }
";"             { return T_semicolon; }
","             { return T_comma; }
"."             { return T_dot; }
"["             { return T_square_bra; }
"]"             { return T_square_ket; }
"("             { return T_round_bra; }
")"             { return T_round_ket; }
"{"             { return T_curly_bra; }
"}"             { return T_curly_ket; }

{ID}        { return T_ID; }

"//".*\n    
"/*"            { BEGIN(C_COMMENT); }
<C_COMMENT>"*/" { BEGIN(INITIAL); }
<C_COMMENT>.    { }     

[ \t\n]+          /* eat up whitespace */

<<EOF>>     { return END_OF_FILE; }

.           { cout << "Unrecoginized token" << endl;}

%%

int yylex (void);
void yyerror (char const *);



// int main(int argc, char* argv[] )
// {
//   while(1){
//     int enum_num = lexer.yylex();
//     cout << enum_num << " <=> " << lexer.YYText() << endl;
//     if(enum_num == END_OF_FILE){
//       break;
//     }
//   }
// }
