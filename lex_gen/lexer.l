/* scanner for a toy Pascal-like language */

%{
/* need this for the call to atof() below */
#include <math.h>
enum yytokentype{
  T_ID = 0, 
  T_integer = 1, 
  T_float = 2, 
  T_void = 100,
  T_string = 101,
  T_bool = 102,
  T_int = 103,
  T_double = 104,
  T_null = 105,
  T_true = 106,
  T_false = 107,
  T_class = 108,
  T_extends = 109,
  T_interface = 110,
  T_implements = 111,
  T_this = 112,
  T_while = 113,
  T_if = 114,
  T_else = 115,
  T_for = 116,
  T_return = 117,
  T_break = 118,
  T_Print = 119,
  T_ReadInteger = 120,
  T_ReadLine = 121,
  T_NewArray = 122,
  T_New = 123,
  T_add = 124,
  T_minus = 125,
  T_mul = 126,
  T_div = 127,
  T_mod = 128,
  T_less = 129,
  T_less_eq = 130,
  T_greater = 131,
  T_greater_eq = 132,
  T_assign = 133,
  T_eq = 134,
  T_not_eq = 135,
  T_and = 136,
  T_or = 137,
  T_not = 138,
  T_semicolon = 139,
  T_comma = 140,
  T_dot = 141,
  T_square_bra = 142,
  T_square_ket = 143,
  T_round_bra = 144,
  T_round_ket = 145
  };
%}

DIGIT    [0-9]
ID       [A-Za-z_][A-Za-z0-9_]*
%x       C_COMMENT

%%

{DIGIT}+    {
            printf( "An integer: %s (%d)\n", yytext,
                    atoi( yytext ) );
            }

[(-|+)]{DIGIT}+"."{DIGIT}*[(e|E)(-|+){DIGIT}+]        {
            printf( "A float: %s (%g)\n", yytext,
                    atof( yytext ) );
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

{ID}        printf( "An identifier: %s\n", yytext );

"//".*\n    
"/*"            { BEGIN(C_COMMENT); }
<C_COMMENT>"*/" { BEGIN(INITIAL); }
<C_COMMENT>.    { }     

[ \t\n]+          /* eat up whitespace */

.           printf( "Unrecognized character: %s\n", yytext );

%%

int main(int argc, char* argv[] )
    {
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;
    yylex();
    }
